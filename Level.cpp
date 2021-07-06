#include "Level.h"
#include "Button.h"
#include "TextBox.h"
#include "Text.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "CollObject.h"
#include "DijkstraPath.h"

#include "GraphNode.h"

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
		auto dijkstra_button = static_cast<Button*>(m_obj[1]);

		std::string font = "Comic Sans MS";

		dijkstra_button->SetFont(font);
		dijkstra_button->SetText("Dijkstra");
		dijkstra_button->SetSize(1.5f, 1.0f);
		dijkstra_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA));
	}
	else if (m_name == "lvl_dijkstra")
	{
		auto title_button = static_cast<Button*>(m_obj[1]);
		auto dijkstra_path = static_cast<DijkstraPath*>(m_obj[2]);

		std::string font = "Comic Sans MS";

		title_button->SetFont(font);
		title_button->SetText("Back");
		title_button->SetSize(1.0f, 1.0f);
		title_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::TITLE));

	}

	//if (m_name == "lvl_title")
	//{
	//	for (int i = 0; i < 5; ++i)
	//	{
	//		auto background = m_obj[i];

	//		background->SetScale(SizeF(2.2f, 2.2f));
	//	}
	//	auto title_text = static_cast<Text*>(m_obj[5]);
	//	auto login_button = static_cast<Button*>(m_obj[6]);
	//	auto exit_button = static_cast<Button*>(m_obj[7]);

	//	std::string font = "Comic Sans MS";

	//	title_text->SetFont(font);
	//	title_text->SetFontSize(72);
	//	title_text->SetText("Clicker Forest");
	//	
	//	login_button->SetFont(font);
	//	login_button->SetText("Login");
	//	login_button->SetSize(1.5f, 1.0f);
	//	login_button->SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	//	login_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::LVL_LOGIN));

	//	exit_button->SetFont(font);
	//	exit_button->SetText("Exit");
	//	exit_button->SetSize(1.5f, 1.0f);
	//	exit_button->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	//	exit_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::EXIT_GAME));

	//	LevelProcess = [](Level* level, DWORD tick) {
	//		auto exit_button = static_cast<Button*>(level->m_obj[7]);

	//		exit_button->Rotate(tick * 0.01f);
	//	};
	//}
	//else if (m_name == "lvl_login")
	//{
	//	for (int i = 0; i < 7; ++i)
	//	{
	//		auto background = m_obj[i];

	//		background->SetScale(SizeF(2.12f, 2.12f));
	//	}
	//	auto title_text = static_cast<Text*>(m_obj[7]);
	//	auto ip_text = static_cast<Text*>(m_obj[8]);
	//	auto ip_textbox = static_cast<TextBox*>(m_obj[9]);
	//	auto port_text = static_cast<Text*>(m_obj[10]);
	//	auto port_textbox = static_cast<TextBox*>(m_obj[11]);
	//	auto id_text = static_cast<Text*>(m_obj[12]);
	//	auto id_textbox = static_cast<TextBox*>(m_obj[13]);
	//	auto back_button = static_cast<Button*>(m_obj[14]);
	//	auto login_button = static_cast<Button*>(m_obj[15]);

	//	std::string font = "Comic Sans MS";

	//	title_text->SetFont(font);
	//	title_text->SetFontSize(72);
	//	title_text->SetText("Login");

	//	ip_text->SetFont(font);
	//	ip_text->SetFontSize(48);
	//	ip_text->SetText("Server IP");

	//	ip_textbox->SetFont(font);
	//	ip_textbox->SetFontSize(48);
	//	ip_textbox->SetText(m_game->GetIp());
	//	ip_textbox->SetTextType(TextBox::TextType::IP_NUMBER);
	//	ip_textbox->SetSize(2.5f, 1.0f);

	//	port_text->SetFont(font);
	//	port_text->SetFontSize(48);
	//	port_text->SetText("Server Port");

	//	port_textbox->SetFont(font);
	//	port_textbox->SetFontSize(48);
	//	port_textbox->SetText("30000");
	//	port_textbox->SetTextType(TextBox::TextType::SHORT_NUMBER);
	//	port_textbox->SetSize(2.0f, 1.0f);

	//	id_text->SetFont(font);
	//	id_text->SetFontSize(48);
	//	id_text->SetText("Your ID");

	//	id_textbox->SetFont(font);
	//	id_textbox->SetFontSize(48);
	//	id_textbox->SetText("");
	//	id_textbox->SetTextType(TextBox::TextType::Default);
	//	id_textbox->SetSize(2.0f, 1.0f);
	//	id_textbox->SetTextLimit(16);

	//	back_button->SetFont(font);
	//	back_button->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	//	back_button->SetSize(1.5f, 1.0f);
	//	back_button->SetFontSize(48);
	//	back_button->SetText("Back");
	//	back_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::LVL_TITLE));

	//	login_button->SetFont(font);
	//	login_button->SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	//	login_button->SetSize(1.5f, 1.0f);
	//	login_button->SetFontSize(48);
	//	login_button->SetText("Connect");
	//	login_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::LVL_GAME));
	//}
	//else if (m_name == "lvl_game")
	//{
	//	std::shared_ptr<GAMECLICKER> clicker = std::make_shared<GAMECLICKER>();
	//	std::string font = "Comic Sans MS";
	//	for (int i = 0; i < 5; ++i)
	//	{
	//		auto background = m_obj[i];
	//		background->SetScale(SizeF(2.1f, 2.1f));
	//	}
	//	for (int i = 0; i < 6; ++i)
	//	{
	//		auto panel = m_obj[i + 5];
	//		panel->SetScale(SizeF(2.0f, 2.0f));
	//	}
	//	clicker->isFirst = true;
	//	for (int i = 0; i < 6; ++i)
	//	{
	//		auto character = m_obj[i + 11];
	//		if (i < 3) character->SetScale(SizeF(-2.0f, 2.0f));
	//		else character->SetScale(SizeF(2.0f, 2.0f));
	//		character->SetAniKind(1);
	//		character->SetActive(false);

	//		//m_variables.clicker.characters.insert({ i, character });
	//		clicker->characters.insert({ i, character });
	//	}
	//	for (int i = 0; i < 6; ++i)
	//	{
	//		auto nickName = static_cast<Text*>(m_obj[i + 17]);
	//		nickName->SetFont(font);
	//		nickName->SetFontSize(24);
	//		nickName->SetActive(false);

	//		clicker->nicknames.insert({ i, nickName });
	//	}
	//	for (int i = 0; i < 6; ++i)
	//	{
	//		auto info = static_cast<Text*>(m_obj[i + 23]);
	//		info->SetFont(font);
	//		info->SetActive(false);
	//		info->SetFontSize(32);

	//		clicker->infos.insert({ i,info });
	//	}
	//	auto boss = static_cast<Button*>(m_obj[29]);
	//	auto healthBack = m_obj[30];
	//	auto healthFront = m_obj[31];
	//	auto healthText = static_cast<Text*>(m_obj[32]);
	//	auto gameClear = static_cast<Text*>(m_obj[33]);
	//	auto scorePanel = m_obj[34];
	//	auto scoreText = static_cast<Text*>(m_obj[35]);

	//	boss->SetSize(3.0f, 3.0f);
	//	boss->SetText("");
	//	boss->SetAniKind(2);
	//	boss->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::HIT_BOSS));

	//	healthBack->SetSize(0.6f, 0.6f);

	//	healthFront->SetSize(0.58f, 0.5f);
	//	healthFront->SetColor(1.0f, 0.0f, 0.0f, 1.0f);

	//	healthText->SetFont(font);
	//	healthText->SetFontSize(24);

	//	gameClear->SetFont(font);
	//	gameClear->SetFontSize(128);
	//	gameClear->SetTextColor(Color::BlueViolet);
	//	gameClear->SetText("Game Cleared");
	//	gameClear->SetActive(false);

	//	scorePanel->SetScale(SizeF(2.0f, 2.0f));

	//	scoreText->SetFont(font);
	//	scoreText->SetFontSize(48);
	//	scoreText->SetText("0");

	//	clicker->bossCurrentHealth = clicker->bossMaxHealth;
	//	clicker->givenDamage = 0.0f;
	//	clicker->executeTimeDelay = 0;
	//	clicker->bossDefeated = false;
	//	clicker->gameOverTimeCount = 0;
	//	clicker->damageDealt = 0.0f;

	//	m_variables = clicker;
	//	LevelProcess = [](Level* level, DWORD tick) {
	//		Game* game = level->GetThisGame();
	//		GAMECLICKER* pVar = static_cast<GAMECLICKER*>(level->GetVariables());

	//		pVar->executeTimeDelay += tick;
	//		if (pVar->executeTimeDelay >= pVar->executeTime)
	//		{
	//			pVar->executeTimeDelay = 0;

	//			EXECUTE execution;
	//			execution.pktID = PKT_EXECUTE;
	//			execution.userID = game->GetConnectID();
	//			strcpy(execution.strID, game->GetStringID().c_str());
	//			execution.deltaDamage = pVar->givenDamage;
	//			execution.damageDealten = pVar->damageDealt;
	//			execution.size = sizeof(execution);
	//			game->Send(&execution);

	//			pVar->givenDamage = 0.0f;
	//		}

	//		game->UpdateSessions(tick);

	//		/*healthbar*/
	//		level->GetGameObject(31)->SetScale(SizeF(pVar->bossCurrentHealth / pVar->bossMaxHealth, 1.0f));

	//		std::string strHealth = std::to_string(pVar->bossCurrentHealth);
	//		strHealth.erase(strHealth.find_last_not_of('0') + 1, std::string::npos);
	//		strHealth.erase(strHealth.find_last_not_of('.') + 1, std::string::npos);
	//		strHealth += " / " + std::to_string(pVar->bossMaxHealth);
	//		strHealth.erase(strHealth.find_last_not_of('0') + 1, std::string::npos);
	//		strHealth.erase(strHealth.find_last_not_of('.') + 1, std::string::npos);

	//		/*healthtext*/
	//		static_cast<Text*>(level->GetGameObject(32))->SetText(strHealth);

	//		std::string strDealt = std::to_string(pVar->damageDealt);
	//		strDealt.erase(strDealt.find_last_not_of('0') + 1, std::string::npos);
	//		strDealt.erase(strDealt.find_last_not_of('.') + 1, std::string::npos);

	//		static_cast<Text*>(level->GetGameObject(35))->SetText(strDealt);

	//		GameObject* character = pVar->characters[game->GetUserInfo(game->GetStringID())->charNumber - 1];
	//		if (character->GetAnimationNormalizedTime() >= 1.0f && character->GetAniKind() == 0)
	//		{
	//			character->ResetAniIndex();
	//			character->SetAniKind(1);
	//		}

	//		Button* boss = static_cast<Button*>(level->GetGameObject(29));
	//		if (pVar->bossCurrentHealth <= 0.0f && !pVar->bossDefeated)
	//		{
	//			pVar->bossDefeated = true;
	//			boss->SetAniKind(0);
	//		}
	//		else if(boss->GetAnimationNormalizedTime() >= 1.0f && boss->GetAniKind() == 1)
	//		{
	//			boss->SetAniKind(2);
	//		}
	//		else if (pVar->bossDefeated && boss->GetAnimationNormalizedTime() >= 1.0f)
	//		{
	//			level->GetGameObject(33)->SetActive(true);
	//			boss->SetActive(false);
	//		}

	//		if (pVar->bossDefeated)
	//		{
	//			pVar->gameOverTimeCount += tick;
	//			if (pVar->gameOverTimeCount >= pVar->gameOverTime)
	//			{
	//				game->RunOff();
	//			}
	//		}
	//	};
	//}
	
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
		else if (type == "dp")
		{
			m_obj[key] = new DijkstraPath();
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
	case ButtonWork::TITLE:
	{
		game->ChangeLevel("lvl_title");
		InputManager::GetInstance()->ShockOff();
	}break;
	case ButtonWork::DIJKSTRA:
	{
		game->ChangeLevel("lvl_dijkstra");
		InputManager::GetInstance()->ShockOff();
	}break;
	}
}
