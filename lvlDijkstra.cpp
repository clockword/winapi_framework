#include "lvlDijkstra.h"

#include "DijkstraNode.h"
#include "DijkstraPath.h"
#include "InputManager.h"

lvlDijkstra::lvlDijkstra(Game* game, std::string name) : Level(game, name)
{
}

lvlDijkstra::~lvlDijkstra()
{
}

void lvlDijkstra::Init()
{
	Level::Init();

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

	editMode = true;
	isClickable = true;
	newObjNum = 0;

	title_button->SetFont(font);
	title_button->SetText("Back");
	title_button->SetFontSize(24);
	title_button->SetSize(0.5f, 0.5f);
	title_button->RegisterButton(this, (int)ButtonWork::TITLE);

	edit_button->SetFont(font);
	edit_button->SetText("Edit");
	edit_button->SetFontSize(24);
	edit_button->SetSize(0.5f, 0.5f);
	edit_button->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	edit_button->RegisterButton(this, (int)ButtonWork::EDIT);

	execute_button->SetFont(font);
	execute_button->SetText("Execute");
	execute_button->SetFontSize(16);
	execute_button->SetSize(0.5f, 0.5f);
	execute_button->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	execute_button->RegisterButton(this, (int)ButtonWork::EXECUTE);

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
	addEdge_button->RegisterButton(this, (int)ButtonWork::ADDEDGE);

	delEdge_button->SetFont(font);
	delEdge_button->SetText("Delete");
	delEdge_button->SetFontSize(16);
	delEdge_button->SetSize(0.5f, 0.5f);
	delEdge_button->RegisterButton(this, (int)ButtonWork::REMOVEEDGE);

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
	delNode_button->RegisterButton(this, (int)ButtonWork::REMOVENODE);

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
	begin_button->RegisterButton(this, (int)ButtonWork::BEGIN);

	end_button->SetFont(font);
	end_button->SetText("End");
	end_button->SetFontSize(24);
	end_button->SetSize(0.5f, 0.5f);
	end_button->RegisterButton(this, (int)ButtonWork::END);

	calculate_button->SetFont(font);
	calculate_button->SetText("Calculate");
	calculate_button->SetFontSize(16);
	calculate_button->SetSize(0.5f, 0.5f);
	calculate_button->RegisterButton(this, (int)ButtonWork::CALCULATE);
}

void lvlDijkstra::Update(Graphics* g, DWORD tick)
{
	const auto input = InputManager::GetInstance();
	DijkstraPath* path = static_cast<DijkstraPath*>(m_obj[102]);
	DijkstraGraph* graph = path->GetGraph();

	if (input->GetLMouseClick())
	{
		if (isClickable && editMode)
		{
			isClickable = false;
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
		isClickable = true;
	}

	Level::Update(g, tick);
}

void lvlDijkstra::OnRecievePacket(void* packet)
{
}

void lvlDijkstra::ButtonProcess(int index)
{
	const ButtonWork btnWork = static_cast<ButtonWork>(index);
	switch (btnWork)
	{
	case ButtonWork::TITLE:
	{
		m_game->ChangeLevel("lvl_title");
		InputManager::GetInstance()->ShockOff();
	}break;
	case ButtonWork::EDIT:
	{
		auto edit_button = static_cast<Button*>(m_obj[103]);
		auto execute_button = static_cast<Button*>(m_obj[104]);

		edit_button->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		execute_button->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

		for (int i = 105; i <= 113; i++)
		{
			m_obj[i]->SetActive(true);
		}
		for (int i = 114; i <= 118; i++)
		{
			m_obj[i]->SetActive(false);
		}

		editMode = true;

	}break;
	case ButtonWork::EXECUTE:
	{
		auto edit_button = static_cast<Button*>(m_obj[103]);
		auto execute_button = static_cast<Button*>(m_obj[104]);

		edit_button->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		execute_button->SetColor(1.0f, 0.0f, 0.0f, 1.0f);

		for (int i = 105; i <= 113; i++)
		{
			m_obj[i]->SetActive(false);
		}
		for (int i = 114; i <= 118; i++)
		{
			m_obj[i]->SetActive(true);
		}

		editMode = false;

	}break;
	case ButtonWork::ADDEDGE:
	{
		auto dijkstra_path = static_cast<DijkstraPath*>(m_obj[102]);
		DijkstraGraph* graph = dijkstra_path->GetGraph();
		auto from_textbox = static_cast<TextBox*>(m_obj[106]);
		auto to_textbox = static_cast<TextBox*>(m_obj[108]);

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
	case ButtonWork::REMOVEEDGE:
	{
		auto dijkstra_path = static_cast<DijkstraPath*>(m_obj[102]);
		DijkstraGraph* graph = dijkstra_path->GetGraph();
		auto from_textbox = static_cast<TextBox*>(m_obj[106]);
		auto to_textbox = static_cast<TextBox*>(m_obj[108]);

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
	case ButtonWork::REMOVENODE:
	{
		auto dijkstra_path = static_cast<DijkstraPath*>(m_obj[102]);
		DijkstraGraph* graph = dijkstra_path->GetGraph();
		auto node_textbox = static_cast<TextBox*>(m_obj[112]);

		if (node_textbox->GetText() == "")
			break;

		unsigned int del = std::stoul(node_textbox->GetText());
		dijkstra_path->CheckIsReset(del);
		graph->DeleteNode(del);

		node_textbox->SetText("");

	}break;
	case ButtonWork::BEGIN:
	{
		auto dijkstra_path = static_cast<DijkstraPath*>(m_obj[102]);
		auto piece_textbox = static_cast<TextBox*>(m_obj[115]);

		if (piece_textbox->GetText() == "")
			break;

		unsigned int begin = std::stoul(piece_textbox->GetText());
		dijkstra_path->SetBeginID(begin);

		piece_textbox->SetText("");

	}break;
	case ButtonWork::END:
	{
		auto dijkstra_path = static_cast<DijkstraPath*>(m_obj[102]);
		auto piece_textbox = static_cast<TextBox*>(m_obj[115]);

		if (piece_textbox->GetText() == "")
			break;

		unsigned int end = std::stoul(piece_textbox->GetText());
		dijkstra_path->SetEndID(end);

		piece_textbox->SetText("");

	}break;
	case ButtonWork::CALCULATE:
	{
		auto dijkstra_path = static_cast<DijkstraPath*>(m_obj[102]);

		const DWORD time = dijkstra_path->Calculate();

	}break;
	}
}
