#include "oLevel.h"
#include "Button.h"
#include "TextBox.h"
#include "Text.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "CollObject.h"
#include "DijkstraPath.h"

#include "DijkstraNode.h"

#include <iostream>

oLevel::oLevel(std::string name)
{
	m_name = name;
	m_isCleared = false;
	LevelProcess = nullptr;
}

oLevel::~oLevel()
{
	std::map<int, GameObject*>::iterator it = m_obj.begin();
	for (;it != m_obj.end();it++)
	{
		delete it->second;
	}
	m_obj.clear();
}

void oLevel::Init()
{
	Objects::iterator it = m_obj.begin();
	for (; it != m_obj.end(); it++)
	{
		it->second->Init();
	}

	if (m_name == "lvl_title")
	{
		auto dijkstra_button = static_cast<Button*>(m_obj[1]);
		auto astar_button = static_cast<Button*>(m_obj[2]);

		std::string font = "Comic Sans MS";

		dijkstra_button->SetFont(font);
		dijkstra_button->SetText("Dijkstra");
		dijkstra_button->SetSize(1.5f, 1.0f);
		dijkstra_button->RegisterButtonFunc(oLevel::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA_SCENE));

		astar_button->SetFont(font);
		astar_button->SetText("A*");
		astar_button->SetSize(1.0f, 1.0f);
		astar_button->RegisterButtonFunc(oLevel::ButtonProcess, this, static_cast<int>(ButtonWork::ASTAR_SCENE));
	}
	else if (m_name == "lvl_dijkstra")
	{
		for (int i = 114; i <= 118; i++)
		{
			m_obj[i]->SetActive(false);
		}

		auto title_button = static_cast<Button*>(m_obj[101]);
		const auto dijkstra_path = static_cast<DijkstraPath*>(m_obj[102]);
		auto edit_button = static_cast<Button*>(m_obj[103]);
		auto execute_button = static_cast<Button*>(m_obj[104]);
		auto from_text = static_cast<Text*>(m_obj[105]);
		auto from_textbox = static_cast<TextBox*>(m_obj[106]);
		auto to_text = static_cast<Text*>(m_obj[107]);
		auto to_textbox = static_cast<TextBox*>(m_obj[108]);
		auto addEdge_button = static_cast<Button*>(m_obj[109]);
		auto delEdge_button = static_cast<Button*>(m_obj[110]);
		auto node_text = static_cast<Text*>(m_obj[111]);
		auto node_textbox = static_cast<TextBox*>(m_obj[112]);
		auto delNode_button = static_cast<Button*>(m_obj[113]);
		auto piece_text = static_cast<Text*>(m_obj[114]);
		auto piece_textbox = static_cast<TextBox*>(m_obj[115]);
		auto begin_button = static_cast<Button*>(m_obj[116]);
		auto end_button = static_cast<Button*>(m_obj[117]);
		auto calculate_button = static_cast<Button*>(m_obj[118]);

		std::string font = "Comic Sans MS";

		std::shared_ptr<DIJKSTRAVAL> value = std::make_shared<DIJKSTRAVAL>();
		value->editMode = true;
		value->isClickable = true;
		value->newObjNum = 0;

		title_button->SetFont(font);
		title_button->SetText("Back");
		title_button->SetFontSize(24);
		title_button->SetSize(0.5f, 0.5f);
		title_button->RegisterButtonFunc(oLevel::ButtonProcess, this, static_cast<int>(ButtonWork::TITLE_SCENE));

		edit_button->SetFont(font);
		edit_button->SetText("Edit");
		edit_button->SetFontSize(24);
		edit_button->SetSize(0.5f, 0.5f);
		edit_button->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		edit_button->RegisterButtonFunc(oLevel::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA_EDIT));

		execute_button->SetFont(font);
		execute_button->SetText("Execute");
		execute_button->SetFontSize(16);
		execute_button->SetSize(0.5f, 0.5f);
		execute_button->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		execute_button->RegisterButtonFunc(oLevel::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA_EXECUTE));

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
		to_text->SetText("To :");
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
		addEdge_button->RegisterButtonFunc(oLevel::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA_ADDEDGE));

		delEdge_button->SetFont(font);
		delEdge_button->SetText("Delete");
		delEdge_button->SetFontSize(16);
		delEdge_button->SetSize(0.5f, 0.5f);
		delEdge_button->RegisterButtonFunc(oLevel::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA_REMOVEEDGE));

		node_text->SetFont(font);
		node_text->SetText("Node :");
		node_text->SetFontSize(16);

		node_textbox->SetFont(font);
		node_textbox->SetText("");
		node_textbox->SetTextType(TextBox::TextType::ONLY_NUMBER);
		node_textbox->SetTextLimit(2);
		node_textbox->SetFontSize(16);
		node_textbox->SetSize(0.5f, 0.5f);

		delNode_button->SetFont(font);
		delNode_button->SetText("Delete");
		delNode_button->SetFontSize(16);
		delNode_button->SetSize(0.5f, 0.5f);
		delNode_button->RegisterButtonFunc(oLevel::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA_REMOVENODE));

		piece_text->SetFont(font);
		piece_text->SetText("Piece :");
		piece_text->SetFontSize(16);

		piece_textbox->SetFont(font);
		piece_textbox->SetText("");
		piece_textbox->SetTextType(TextBox::TextType::ONLY_NUMBER);
		piece_textbox->SetTextLimit(2);
		piece_textbox->SetFontSize(16);
		piece_textbox->SetSize(0.5f, 0.5f);

		begin_button->SetFont(font);
		begin_button->SetText("Begin");
		begin_button->SetFontSize(24);
		begin_button->SetSize(0.5f, 0.5f);
		begin_button->RegisterButtonFunc(oLevel::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA_BEGIN));

		end_button->SetFont(font);
		end_button->SetText("End");
		end_button->SetFontSize(24);
		end_button->SetSize(0.5f, 0.5f);
		end_button->RegisterButtonFunc(oLevel::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA_END));

		calculate_button->SetFont(font);
		calculate_button->SetText("Calculate");
		calculate_button->SetFontSize(16);
		calculate_button->SetSize(0.5f, 0.5f);
		calculate_button->RegisterButtonFunc(oLevel::ButtonProcess, this, static_cast<int>(ButtonWork::DIJKSTRA_CALCULATE));

		m_variables = value;

		LevelProcess = [](oLevel* level, DWORD tick) {
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

					if (y > 100 && y < 700)
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
	else if (m_name == "lvl_astar")
	{

	}

	World::GetInstance()->Init();
}

void oLevel::Update(Graphics* g, DWORD tick)
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

void oLevel::Load()
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

void oLevel::UnLoad()
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
T oLevel::AddGameObject(int index)
{
	GameObject* obj = dynamic_cast<GameObject*>(new T());
	if(obj) m_obj.insert({ index, obj });
	return obj;
}

void* oLevel::GetVariables()
{
	return m_variables.get();
}

void oLevel::RecievePacket(LPPACKETHEADER packet)
{
	std::string myStrID = m_game->GetStringID();
	unsigned int myConnectID = m_game->GetConnectID();

	switch (packet->pktID)
	{
	default:
		break;
	}
}

void oLevel::ButtonProcess(void* ctx, int index)
{
	oLevel* level = static_cast<oLevel*>(ctx);
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

		for (int i = 105; i <= 113; i++)
		{
			level->m_obj[i]->SetActive(true);
		}
		for (int i = 114; i <= 118; i++)
		{
			level->m_obj[i]->SetActive(false);
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

		for (int i = 105; i <= 113; i++)
		{
			level->m_obj[i]->SetActive(false);
		}
		for (int i = 114; i <= 118; i++)
		{
			level->m_obj[i]->SetActive(true);
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

		DijkstraNode* fromNode = graph->GetNode(from);
		DijkstraNode* toNode = graph->GetNode(to);

		if (fromNode && toNode)
		{
			fromNode->InsertEdge(toNode);
		}

		from_textbox->SetText("");
		to_textbox->SetText("");

	}break;
	case ButtonWork::DIJKSTRA_REMOVEEDGE:
	{
		auto dijkstra_path = static_cast<DijkstraPath*>(level->m_obj[102]);
		DijkstraGraph* graph = dijkstra_path->GetGraph();
		auto from_textbox = static_cast<TextBox*>(level->m_obj[106]);
		auto to_textbox = static_cast<TextBox*>(level->m_obj[108]);

		if (from_textbox->GetText() == "" || to_textbox->GetText() == "")
			break;

		unsigned int from = std::stoul(from_textbox->GetText());
		unsigned int to = std::stoul(to_textbox->GetText());

		DijkstraNode* fromNode = graph->GetNode(from);
		DijkstraNode* toNode = graph->GetNode(to);

		if (fromNode && toNode)
		{
			fromNode->DeleteEdge(toNode);
		}

		from_textbox->SetText("");
		to_textbox->SetText("");

	}break;
	case ButtonWork::DIJKSTRA_REMOVENODE:
	{
		auto dijkstra_path = static_cast<DijkstraPath*>(level->m_obj[102]);
		DijkstraGraph* graph = dijkstra_path->GetGraph();
		auto node_textbox = static_cast<TextBox*>(level->m_obj[112]);

		if (node_textbox->GetText() == "")
			break;

		unsigned int del = std::stoul(node_textbox->GetText());
		dijkstra_path->CheckIsReset(del);
		graph->DeleteNode(del);

		node_textbox->SetText("");

	}break;
	case ButtonWork::DIJKSTRA_BEGIN:
	{
		auto dijkstra_path = static_cast<DijkstraPath*>(level->m_obj[102]);
		auto piece_textbox = static_cast<TextBox*>(level->m_obj[115]);

		if (piece_textbox->GetText() == "")
			break;

		unsigned int begin = std::stoul(piece_textbox->GetText());
		dijkstra_path->SetBeginID(begin);

		piece_textbox->SetText("");

	}break;
	case ButtonWork::DIJKSTRA_END:
	{
		auto dijkstra_path = static_cast<DijkstraPath*>(level->m_obj[102]);
		auto piece_textbox = static_cast<TextBox*>(level->m_obj[115]);

		if (piece_textbox->GetText() == "")
			break;

		unsigned int end = std::stoul(piece_textbox->GetText());
		dijkstra_path->SetEndID(end);

		piece_textbox->SetText("");

	}break;
	case ButtonWork::DIJKSTRA_CALCULATE:
	{
		auto dijkstra_path = static_cast<DijkstraPath*>(level->m_obj[102]);

		const DWORD time = dijkstra_path->Calculate();

	}break;
	case ButtonWork::ASTAR_SCENE:
	{
		game->ChangeLevel("lvl_astar");
		InputManager::GetInstance()->ShockOff();
	}break;
	}
}
