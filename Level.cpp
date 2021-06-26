#include "Level.h"
#include "Button.h"
#include "TextBox.h"
#include "Text.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "CollObject.h"

#include <iostream>

Level::Level(std::string name)
{
	m_name = name;
	m_isCleared = false;
	LevelProcess = nullptr;
}

Level::~Level()
{
	std::map<int, GameObject*>::iterator it = m_obj.begin();
	for (;it != m_obj.end();it++)
	{
		delete it->second;
	}
	m_obj.clear();
}

void Level::Init()
{
	Objects::iterator it = m_obj.begin();
	for (; it != m_obj.end(); it++)
	{
		it->second->Init();
	}

	if (m_name == "lvl_title")
	{
		for (int i = 0; i < 5; ++i)
		{
			auto background = m_obj[i];

			background->SetScale(SizeF(2.2f, 2.2f));
		}
		auto title_text = static_cast<Text*>(m_obj[5]);
		auto login_button = static_cast<Button*>(m_obj[6]);
		auto exit_button = static_cast<Button*>(m_obj[7]);

		std::string font = "Comic Sans MS";

		title_text->SetFont(font);
		title_text->SetFontSize(72);
		title_text->SetText("Clicker Forest");
		
		login_button->SetFont(font);
		login_button->SetText("Login");
		login_button->SetSize(1.5f, 1.0f);
		login_button->SetColor(0.0f, 1.0f, 0.0f, 1.0f);
		login_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::LVL_LOGIN));

		exit_button->SetFont(font);
		exit_button->SetText("Exit");
		exit_button->SetSize(1.5f, 1.0f);
		exit_button->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		exit_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::EXIT_GAME));
	}
	else if (m_name == "lvl_login")
	{
		for (int i = 0; i < 7; ++i)
		{
			auto background = m_obj[i];

			background->SetScale(SizeF(2.12f, 2.12f));
		}
		auto title_text = static_cast<Text*>(m_obj[7]);
		auto ip_text = static_cast<Text*>(m_obj[8]);
		auto ip_textbox = static_cast<TextBox*>(m_obj[9]);
		auto port_text = static_cast<Text*>(m_obj[10]);
		auto port_textbox = static_cast<TextBox*>(m_obj[11]);
		auto id_text = static_cast<Text*>(m_obj[12]);
		auto id_textbox = static_cast<TextBox*>(m_obj[13]);
		auto back_button = static_cast<Button*>(m_obj[14]);
		auto login_button = static_cast<Button*>(m_obj[15]);

		std::string font = "Comic Sans MS";

		title_text->SetFont(font);
		title_text->SetFontSize(72);
		title_text->SetText("Login");

		ip_text->SetFont(font);
		ip_text->SetFontSize(48);
		ip_text->SetText("Server IP");

		ip_textbox->SetFont(font);
		ip_textbox->SetFontSize(48);
		ip_textbox->SetText(m_game->GetIp());
		ip_textbox->SetTextType(TextBox::TextType::IP_NUMBER);
		ip_textbox->SetSize(2.5f, 1.0f);

		port_text->SetFont(font);
		port_text->SetFontSize(48);
		port_text->SetText("Server Port");

		port_textbox->SetFont(font);
		port_textbox->SetFontSize(48);
		port_textbox->SetText("30000");
		port_textbox->SetTextType(TextBox::TextType::SHORT_NUMBER);
		port_textbox->SetSize(2.0f, 1.0f);

		id_text->SetFont(font);
		id_text->SetFontSize(48);
		id_text->SetText("Your ID");

		id_textbox->SetFont(font);
		id_textbox->SetFontSize(48);
		id_textbox->SetText("");
		id_textbox->SetTextType(TextBox::TextType::Default);
		id_textbox->SetSize(2.0f, 1.0f);
		id_textbox->SetTextLimit(16);

		back_button->SetFont(font);
		back_button->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		back_button->SetSize(1.5f, 1.0f);
		back_button->SetFontSize(48);
		back_button->SetText("Back");
		back_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::LVL_TITLE));

		login_button->SetFont(font);
		login_button->SetColor(0.0f, 1.0f, 0.0f, 1.0f);
		login_button->SetSize(1.5f, 1.0f);
		login_button->SetFontSize(48);
		login_button->SetText("Connect");
		login_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::LVL_GAME));
	}
	else if (m_name == "lvl_game")
	{
		std::shared_ptr<GAMECLICKER> clicker = std::make_shared<GAMECLICKER>();
		std::string font = "Comic Sans MS";
		for (int i = 0; i < 5; ++i)
		{
			auto background = m_obj[i];
			background->SetScale(SizeF(2.1f, 2.1f));
		}
		for (int i = 0; i < 6; ++i)
		{
			auto panel = m_obj[i + 5];
			panel->SetScale(SizeF(2.0f, 2.0f));
		}
		clicker->isFirst = true;
		for (int i = 0; i < 6; ++i)
		{
			auto character = m_obj[i + 11];
			if (i < 3) character->SetScale(SizeF(-2.0f, 2.0f));
			else character->SetScale(SizeF(2.0f, 2.0f));
			character->SetAniKind(1);
			character->SetActive(false);

			//m_variables.clicker.characters.insert({ i, character });
			clicker->characters.insert({ i, character });
		}
		for (int i = 0; i < 6; ++i)
		{
			auto nickName = static_cast<Text*>(m_obj[i + 17]);
			nickName->SetFont(font);
			nickName->SetFontSize(24);
			nickName->SetActive(false);

			clicker->nicknames.insert({ i, nickName });
		}
		for (int i = 0; i < 6; ++i)
		{
			auto info = static_cast<Text*>(m_obj[i + 23]);
			info->SetFont(font);
			info->SetActive(false);
			info->SetFontSize(32);

			clicker->infos.insert({ i,info });
		}
		auto boss = static_cast<Button*>(m_obj[29]);
		auto healthBack = m_obj[30];
		auto healthFront = m_obj[31];
		auto healthText = static_cast<Text*>(m_obj[32]);
		auto gameClear = static_cast<Text*>(m_obj[33]);
		auto scorePanel = m_obj[34];
		auto scoreText = static_cast<Text*>(m_obj[35]);

		boss->SetSize(3.0f, 3.0f);
		boss->SetText("");
		boss->SetAniKind(2);
		boss->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::HIT_BOSS));

		healthBack->SetSize(0.6f, 0.6f);

		healthFront->SetSize(0.58f, 0.5f);
		healthFront->SetColor(1.0f, 0.0f, 0.0f, 1.0f);

		healthText->SetFont(font);
		healthText->SetFontSize(24);

		gameClear->SetFont(font);
		gameClear->SetFontSize(128);
		gameClear->SetTextColor(Color::BlueViolet);
		gameClear->SetText("Game Cleared");
		gameClear->SetActive(false);

		scorePanel->SetScale(SizeF(2.0f, 2.0f));

		scoreText->SetFont(font);
		scoreText->SetFontSize(48);
		scoreText->SetText("0");

		clicker->bossCurrentHealth = clicker->bossMaxHealth;
		clicker->givenDamage = 0.0f;
		clicker->executeTimeDelay = 0;
		clicker->bossDefeated = false;
		clicker->gameOverTimeCount = 0;
		clicker->damageDealt = 0.0f;

		m_variables = clicker;
		LevelProcess = [](Level* level, DWORD tick) {
			Game* game = level->GetThisGame();
			GAMECLICKER* pVar = static_cast<GAMECLICKER*>(level->GetVariables());

			pVar->executeTimeDelay += tick;
			if (pVar->executeTimeDelay >= pVar->executeTime)
			{
				pVar->executeTimeDelay = 0;

				EXECUTE execution;
				execution.pktID = PKT_EXECUTE;
				execution.userID = game->GetConnectID();
				strcpy(execution.strID, game->GetStringID().c_str());
				execution.deltaDamage = pVar->givenDamage;
				execution.damageDealten = pVar->damageDealt;
				execution.size = sizeof(execution);
				game->Send(&execution);

				pVar->givenDamage = 0.0f;
			}

			game->UpdateSessions(tick);

			/*healthbar*/
			level->GetGameObject(31)->SetScale(SizeF(pVar->bossCurrentHealth / pVar->bossMaxHealth, 1.0f));

			std::string strHealth = std::to_string(pVar->bossCurrentHealth);
			strHealth.erase(strHealth.find_last_not_of('0') + 1, std::string::npos);
			strHealth.erase(strHealth.find_last_not_of('.') + 1, std::string::npos);
			strHealth += " / " + std::to_string(pVar->bossMaxHealth);
			strHealth.erase(strHealth.find_last_not_of('0') + 1, std::string::npos);
			strHealth.erase(strHealth.find_last_not_of('.') + 1, std::string::npos);

			/*healthtext*/
			static_cast<Text*>(level->GetGameObject(32))->SetText(strHealth);

			std::string strDealt = std::to_string(pVar->damageDealt);
			strDealt.erase(strDealt.find_last_not_of('0') + 1, std::string::npos);
			strDealt.erase(strDealt.find_last_not_of('.') + 1, std::string::npos);

			static_cast<Text*>(level->GetGameObject(35))->SetText(strDealt);

			GameObject* character = pVar->characters[game->GetUserInfo(game->GetStringID())->charNumber - 1];
			if (character->GetAnimationNormalizedTime() >= 1.0f && character->GetAniKind() == 0)
			{
				character->ResetAniIndex();
				character->SetAniKind(1);
			}

			Button* boss = static_cast<Button*>(level->GetGameObject(29));
			if (pVar->bossCurrentHealth <= 0.0f && !pVar->bossDefeated)
			{
				pVar->bossDefeated = true;
				boss->SetAniKind(0);
			}
			else if(boss->GetAnimationNormalizedTime() >= 1.0f && boss->GetAniKind() == 1)
			{
				boss->SetAniKind(2);
			}
			else if (pVar->bossDefeated && boss->GetAnimationNormalizedTime() >= 1.0f)
			{
				level->GetGameObject(33)->SetActive(true);
				boss->SetActive(false);
			}

			if (pVar->bossDefeated)
			{
				pVar->gameOverTimeCount += tick;
				if (pVar->gameOverTimeCount >= pVar->gameOverTime)
				{
					game->RunOff();
				}
			}
		};
	}
	
	World::GetInstance()->Init();
}

void Level::Update(Graphics* g, DWORD tick)
{
	if (LevelProcess != nullptr) LevelProcess(this, tick);
	Objects::iterator it = m_obj.begin();
	for (;it != m_obj.end();it++)
	{
		it->second->Update(g, tick);
	}
}

void Level::Load()
{
	UnLoad();

	FILE* fp = nullptr;

	std::string path = "./Resource/Level/" + m_name + ".txt";
	fp = fopen(path.c_str(), "rt");

	while (true)
	{
		int key, posX, posY;
		std::string name;
		std::string tag;

		char ch_name[255] = { 0, };
		char ch_tag[255] = { 0, };
		fscanf(fp, "%d %s %s %d %d", &key, ch_tag, ch_name, &posX, &posY);
		name = ch_name;
		tag = ch_tag;
		if (name == "End")
			break;
		std::string type = name.substr(0, 2);
		std::string img = name.substr(3);
		if (type == "bg")
		{
			m_obj[key] = new GameObject();
		}
		else if (type == "bt")
		{
			m_obj[key] = new Button();
			InputManager::GetInstance()->RegisterButton(static_cast<Button*>(m_obj[key]));
		}
		else if (type == "co")
		{
			m_obj[key] = new CollObject();
			World::GetInstance()->RegisterCollObject(tag, static_cast<CollObject*>(m_obj[key]));
		}
		else if (type == "tb")
		{
			m_obj[key] = new TextBox();
			InputManager::GetInstance()->RegisterTextBox(static_cast<TextBox*>(m_obj[key]));
		}
		else if (type == "tx")
		{
			m_obj[key] = new Text();
		}

		m_obj[key]->SetFile(img);
		m_obj[key]->SetImage(ResourceManager::GetInstance()->LoadImage_(img));
		m_obj[key]->SetTag(tag);
		m_obj[key]->SetName(img);
		m_obj[key]->SetCollider(img);
		m_obj[key]->SetPosition(posX, posY);
		m_obj[key]->SetLevel(this);
	}

	fclose(fp);
}

void Level::UnLoad()
{
	World::GetInstance()->ClearRegistered();
	InputManager::GetInstance()->ClearRegistered();
	Objects::iterator it = m_obj.begin();
	for (;it != m_obj.end();it++)
	{
		delete it->second;
	}
	m_obj.clear();
}

void* Level::GetVariables()
{
	return m_variables.get();
}

void Level::RecievePacket(LPPACKETHEADER packet)
{
	std::string myStrID = m_game->GetStringID();
	unsigned int myConnectID = m_game->GetConnectID();

	switch (packet->pktID)
	{
	case PKT_LOGMEIN:
	{
		LPLOGIN pLoginInfo = (LPLOGIN)packet;
		std::string strID = pLoginInfo->strID;

		if (strcmp(myStrID.c_str(), pLoginInfo->strID) == 0)
		{
			//m_variables.clicker.isFirst = true;
			GAMECLICKER* pVar = static_cast<GAMECLICKER*>(m_variables.get());
			pVar->isFirst = true;

			m_game->LoginUser(strID);
			m_game->GetUserInfo(strID)->id = pLoginInfo->userID;
			m_game->GetUserInfo(strID)->charNumber = 1;

			m_game->SetConnectID(pLoginInfo->userID);
			
			pLoginInfo->pktID = PKT_SENDOVER_LOGIN;
			m_game->Send(pLoginInfo);
		}

	}break;
	case PKT_SENDOVER_LOGIN:
	{
		LPLOGIN pLoginInfo = (LPLOGIN)packet;
		std::string strID = pLoginInfo->strID;

		if (strcmp(myStrID.c_str(), pLoginInfo->strID) != 0)
		{
			if (m_game->TotalUser() > 6)
			{
				pLoginInfo->pktID = PKT_MAX_USER;
				m_game->Send(pLoginInfo);
			}
			else if (m_game->LoginUser(strID))
			{
				m_game->GetUserInfo(strID)->id = pLoginInfo->userID;
				m_game->SetUserNumberByPriority(strID);
				//m_game->GetUserInfo(strID)->charNumber = m_game->TotalUser();
				//m_game->GetUserInfo(strID)->active = true;

				//m_variables.clicker.characters[m_game->GetUserInfo(strID)->charNumber]->SetActive(true);
				GAMECLICKER* pVar = static_cast<GAMECLICKER*>(m_variables.get());
				int charNum = m_game->GetUserInfo(strID)->charNumber - 1;
				pVar->characters[charNum]->SetActive(true);
				pVar->nicknames[charNum]->SetActive(true);
				pVar->nicknames[charNum]->SetText(strID);
				pVar->infos[charNum]->SetActive(true);
				//pVar->infos[charNum]->SetText()
				pVar->infos[charNum]->SetTextColor(Color::AliceBlue);

				CHARACTER myInfo;
				myInfo.pktID = PKT_UPDATE_LOGINFO;
				myInfo.charNumber = m_game->GetUserInfo(myStrID)->charNumber;
				myInfo.totalUser = m_game->TotalUser();
				myInfo.bossHealth = pVar->bossCurrentHealth;
				strcpy(myInfo.strID, myStrID.c_str());
				myInfo.size = sizeof(myInfo);

				m_game->Send(&myInfo);
			}
		}
		else
		{
			if (pLoginInfo->userID != myConnectID)
			{
				pLoginInfo->pktID = PKT_SAME_ID;

				m_game->Send(pLoginInfo);
			}
			else
			{
				GAMECLICKER* pVar = static_cast<GAMECLICKER*>(m_variables.get());
				if (pVar->isFirst)
				{
					pVar->isFirst = false;

					//m_game->GetUserInfo(myStrID)->active = true;
					int charNum = m_game->GetUserInfo(myStrID)->charNumber - 1;
					pVar->characters[charNum]->SetActive(true);
					pVar->nicknames[charNum]->SetActive(true);
					pVar->nicknames[charNum]->SetText(myStrID);
					pVar->infos[charNum]->SetActive(true);
					pVar->infos[charNum]->SetText("YOU");
					pVar->infos[charNum]->SetTextColor(Color::GreenYellow);
				}
			}

		}

	}break;
	case PKT_UPDATE_LOGINFO:
	{
		LPCHARACTER pLoginInfo = (LPCHARACTER)packet;
		std::string strID = pLoginInfo->strID;
		GAMECLICKER* pVar = static_cast<GAMECLICKER*>(m_variables.get());

		if (m_game->LoginUser(strID))
		{
			m_game->GetUserInfo(strID)->id = pLoginInfo->userID;
			m_game->GetUserInfo(strID)->charNumber = pLoginInfo->charNumber;
			//m_game->GetUserInfo(strID)->active = true;
			int otherNum = m_game->GetUserInfo(strID)->charNumber - 1;
			pVar->characters[otherNum]->SetActive(true);
			pVar->nicknames[otherNum]->SetActive(true);
			pVar->nicknames[otherNum]->SetText(strID);
			pVar->infos[otherNum]->SetActive(true);
			//pVar->infos[otherNum]->SetText();
			pVar->infos[otherNum]->SetTextColor(Color::AliceBlue);
			//m_game->GetUserInfo(myStrID)->charNumber++;

			if (pLoginInfo->totalUser == m_game->TotalUser())
			{
				//m_game->GetUserInfo(myStrID)->active = true;
				m_game->SetUserNumberByPriority(myStrID);

				pVar->bossCurrentHealth = pLoginInfo->bossHealth;
				int charNum = m_game->GetUserInfo(myStrID)->charNumber - 1;
				pVar->characters[charNum]->SetActive(true);
				pVar->nicknames[charNum]->SetActive(true);
				pVar->nicknames[charNum]->SetText(myStrID);
				pVar->infos[charNum]->SetActive(true);
				pVar->infos[charNum]->SetText("YOU");
				pVar->infos[charNum]->SetTextColor(Color::GreenYellow);
			}
		}

	}break;
	case PKT_LOGOUT:
	{
		LPLOGIN pLoginInfo = (LPLOGIN)packet;
		std::string strID = pLoginInfo->strID;
		GAMECLICKER* pVar = static_cast<GAMECLICKER*>(m_variables.get());
		int erased = m_game->GetUserInfo(strID)->charNumber - 1;

		pVar->characters[erased]->SetActive(false);
		pVar->nicknames[erased]->SetActive(false);
		pVar->infos[erased]->SetActive(false);

		m_game->LogoutUser(strID);

	}break;
	case PKT_SAME_ID:
	{
		LPLOGIN pLoginInfo = (LPLOGIN)packet;
		std::string strID = pLoginInfo->strID;

		if (strID.compare(myStrID) == 0 &&
			pLoginInfo->userID != m_game->GetConnectID())
		{
			m_game->RunOff();
		}

	}break;
	case PKT_MAX_USER:
	{
		LPLOGIN pLoginInfo = (LPLOGIN)packet;
		std::string strID = pLoginInfo->strID;

		if (strID.compare(myStrID) == 0)
		{
			m_game->RunOff();
		}

	}break;
	case PKT_EXECUTE:
	{
		LPEXECUTE pExecution = (LPEXECUTE)packet;
		std::string strID = pExecution->strID;
		GAMECLICKER* pVar = static_cast<GAMECLICKER*>(m_variables.get());

		if (!m_game->CheckUserID(strID)) break;

		GameObject* character = pVar->characters[m_game->GetUserInfo(strID)->charNumber - 1];

		if (strID.compare(myStrID) != 0)
		{
			pVar->bossCurrentHealth -= pExecution->deltaDamage;

			m_game->GetUserInfo(strID)->sessionCount = 0;

			std::string strDealt = std::to_string(pExecution->damageDealten);
			strDealt.erase(strDealt.find_last_not_of('0') + 1, std::string::npos);
			strDealt.erase(strDealt.find_last_not_of('.') + 1, std::string::npos);
			pVar->infos[m_game->GetUserInfo(strID)->charNumber - 1]->SetText(strDealt);

			if (pVar->bossCurrentHealth < 0.0f)
				pVar->bossCurrentHealth = 0.0f;
			if (pExecution->deltaDamage == 0.0f)
			{
				if (character->GetAnimationNormalizedTime() >= 1.0f)
				{
					character->ResetAniIndex();
					character->SetAniKind(1);
				}
			}
			else
			{
				character->SetAniKind(0);
			}
		}

	}break;
	default:
		break;
	}
}

void Level::ButtonProcess(void* ctx, int index)
{
	Level* level = static_cast<Level*>(ctx);
	Game* game = level->GetThisGame();
	std::string myStrID = game->GetStringID();
	unsigned int id = game->GetConnectID();

	switch (static_cast<ButtonWork>(index))
	{
	case ButtonWork::LVL_LOGIN:
	{
		game->ChangeLevel("lvl_login");
		InputManager::GetInstance()->ShockOff();
	}break;
	case ButtonWork::EXIT_GAME:
	{
		level->UnLoad();
		game->RunOff();
		InputManager::GetInstance()->ShockOff();
	}break;
	case ButtonWork::LVL_TITLE:
	{
		game->ChangeLevel("lvl_title");
		InputManager::GetInstance()->ShockOff();
	}break;
	case ButtonWork::LVL_GAME:
	{
		unsigned short port = std::stoi(static_cast<TextBox*>(level->m_obj[11])->GetText().c_str());
		std::string ip = static_cast<TextBox*>(level->m_obj[9])->GetText();
		std::string id = static_cast<TextBox*>(level->m_obj[13])->GetText();

		game->SetStringID(id);

		game->Connect(port, ip);

		LOGIN login;
		login.pktID = PKT_LOGMEIN;
		login.size = sizeof(login);
		strcpy(login.strID, id.c_str());
		
		game->Send(&login);

		game->ChangeLevel("lvl_game");
		InputManager::GetInstance()->ShockOff();
	}break;
	case ButtonWork::HIT_BOSS:
	{
		GAMECLICKER* pVar = static_cast<GAMECLICKER*>(level->GetVariables());
		if (pVar->bossCurrentHealth <= 0.0f) break;
		GameObject* character = pVar->characters[game->GetUserInfo(myStrID)->charNumber - 1];
		Button* boss = static_cast<Button*>(level->m_obj[29]);

		float damage = pVar->damage + rand() % 100;
		pVar->givenDamage += damage;
		pVar->damageDealt += damage;
		pVar->bossCurrentHealth -= damage;
		if (pVar->bossCurrentHealth < 0.0f)
			pVar->bossCurrentHealth = 0.0f;

		character->SetAniKind(0);
		boss->SetAniKind(1);

	}break;
	}
}
