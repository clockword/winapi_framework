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
		dijkstra_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA_SCENE));
	}
	else if (m_name == "lvl_dijkstra")
	{
		auto title_button = static_cast<Button*>(m_obj[101]);
		auto dijkstra_path = static_cast<DijkstraPath*>(m_obj[102]);
		auto edit_button = static_cast<Button*>(m_obj[103]);
		auto execute_button = static_cast<Button*>(m_obj[104]);
		auto from_text = static_cast<Text*>(m_obj[105]);
		auto from_textbox = static_cast<TextBox*>(m_obj[106]);
		auto to_text = static_cast<Text*>(m_obj[107]);
		auto to_textbox = static_cast<TextBox*>(m_obj[108]);
		auto addEdge_button = static_cast<Button*>(m_obj[109]);

		std::string font = "Comic Sans MS";

		std::shared_ptr<DIJKSTRAVAL> value = std::make_shared<DIJKSTRAVAL>();
		value->editMode = true;
		value->isClickable = true;
		value->newObjNum = 0;

		title_button->SetFont(font);
		title_button->SetText("Back");
		title_button->SetFontSize(24);
		title_button->SetSize(0.5f, 0.5f);
		title_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::TITLE_SCENE));

		edit_button->SetFont(font);
		edit_button->SetText("Edit");
		edit_button->SetFontSize(24);
		edit_button->SetSize(0.5f, 0.5f);
		edit_button->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		edit_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA_EDIT));

		execute_button->SetFont(font);
		execute_button->SetText("Execute");
		execute_button->SetFontSize(16);
		execute_button->SetSize(0.5f, 0.5f);
		execute_button->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		execute_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA_EXECUTE));

		from_text->SetFont(font);
		from_text->SetText("From :");
		from_text->SetFontSize(16);

		from_textbox->SetFont(font);
		from_textbox->SetText("");
		from_textbox->SetTextType(TextBox::TextType::ONLY_NUMBER);
		from_textbox->SetTextLimit(2);
		from_textbox->SetFontSize(16);
		from_textbox->SetSize(0.5f, 0.5f);

		to_text->SetFont(font);
		to_text->SetText("to :");
		to_text->SetFontSize(16);

		to_textbox->SetFont(font);
		to_textbox->SetText("");
		to_textbox->SetTextType(TextBox::TextType::ONLY_NUMBER);
		to_textbox->SetTextLimit(2);
		to_textbox->SetFontSize(16);
		to_textbox->SetSize(0.5f, 0.5f);

		addEdge_button->SetFont(font);
		addEdge_button->SetText("Add");
		addEdge_button->SetFontSize(16);
		addEdge_button->SetSize(0.5f, 0.5f);
		addEdge_button->RegisterButtonFunc(Level::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA_ADDEDGE));

		m_variables = value;

		LevelProcess = [](Level* level, DWORD tick) {
			const auto input = InputManager::GetInstance();
			DijkstraPath* path = static_cast<DijkstraPath*>(level->m_obj[102]);
			DijkstraGraph* graph = path->GetGraph();
			LPDIJKSTRAVAL value = static_cast<LPDIJKSTRAVAL>(level->GetVariables());

			if (input->GetMouseClick())
			{
				if (value->isClickable && value->editMode)
				{
					value->isClickable = false;
					const int x = input->GetMouseDownPos().first;
					const int y = input->GetMouseDownPos().second;

					if (y > 100)
					{
						graph->InsertNode(x, y);
					}
				}
			}
			else
			{
				value->isClickable = true;
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
		const GameObject* obj = it->second;
		if(obj->GetActive())
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

		m_obj[key]->LoadExtra();
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

template<class T>
T Level::AddGameObject(int index)
{
	GameObject* obj = dynamic_cast<GameObject*>(new T());
	if(obj) m_obj.insert({ index, obj });
	return obj;
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
	case ButtonWork::TITLE_SCENE:
	{
		game->ChangeLevel("lvl_title");
		InputManager::GetInstance()->ShockOff();
	}break;
	case ButtonWork::DIJKSTRA_SCENE:
	{
		game->ChangeLevel("lvl_dijkstra");
		InputManager::GetInstance()->ShockOff();
	}break;
	case ButtonWork::DIJKSTRA_EDIT:
	{
		LPDIJKSTRAVAL value = static_cast<LPDIJKSTRAVAL>(level->GetVariables());
		auto edit_button = static_cast<Button*>(level->m_obj[103]);
		auto execute_button = static_cast<Button*>(level->m_obj[104]);

		edit_button->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		execute_button->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

		for (int i = 105; i <= 109; i++)
		{
			level->m_obj[i]->SetActive(true);
		}

		value->editMode = true;

	}break;
	case ButtonWork::DIJKSTRA_EXECUTE:
	{
		LPDIJKSTRAVAL value = static_cast<LPDIJKSTRAVAL>(level->GetVariables());
		auto edit_button = static_cast<Button*>(level->m_obj[103]);
		auto execute_button = static_cast<Button*>(level->m_obj[104]);

		edit_button->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		execute_button->SetColor(1.0f, 0.0f, 0.0f, 1.0f);

		for (int i = 105; i <= 109; i++)
		{
			level->m_obj[i]->SetActive(false);
		}

		value->editMode = false;

	}break;
	case ButtonWork::DIJKSTRA_ADDEDGE:
	{
		auto dijkstra_path = static_cast<DijkstraPath*>(level->m_obj[102]);
		DijkstraGraph* graph = dijkstra_path->GetGraph();
		auto from_textbox = static_cast<TextBox*>(level->m_obj[106]);
		auto to_textbox = static_cast<TextBox*>(level->m_obj[108]);

		if (from_textbox->GetText() == "" || to_textbox->GetText() == "")
			break;

		unsigned int from = std::stoul(from_textbox->GetText());
		unsigned int to = std::stoul(to_textbox->GetText());

		GraphNode* fromNode = graph->GetNode(from);
		GraphNode* toNode = graph->GetNode(to);

		if (fromNode && toNode)
		{
			fromNode->InsertEdge(toNode);
		}

	}break;
	}
}
