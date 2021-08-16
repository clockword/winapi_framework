#include "lvlTitle.h"

#include "Button.h"
#include "InputManager.h"

lvlTitle::lvlTitle(Game* game, std::string name) : Level(game, name)
{
}

lvlTitle::~lvlTitle()
{
}

void lvlTitle::Init()
{
	Level::Init();

	auto dijkstra_button = static_cast<Button*>(m_obj[1]);
	auto astar_button = static_cast<Button*>(m_obj[2]);

	std::string font = "Comic Sans MS";

	dijkstra_button->SetFont(font);
	dijkstra_button->SetText("Dijkstra");
	dijkstra_button->SetSize(1.5f, 1.0f);
	dijkstra_button->RegisterButton(this, (int)ButtonWork::DIJKSTRA_BASE);

	astar_button->SetFont(font);
	astar_button->SetText("A*");
	astar_button->SetSize(1.0f, 1.0f);
	astar_button->RegisterButton(this, (int)ButtonWork::ASTAR_BASE);
}

void lvlTitle::Update(Graphics* g, DWORD tick)
{
	Level::Update(g, tick);
}

void lvlTitle::OnRecievePacket(void* packet)
{
}

void lvlTitle::ButtonProcess(int index)
{
	const ButtonWork btnWork = static_cast<ButtonWork>(index);
	switch (btnWork)
	{
	case ButtonWork::DIJKSTRA_BASE:
	{
		m_game->ChangeLevel("lvl_dijkstra");
		InputManager::GetInstance()->ShockOff();
	}break;
	case ButtonWork::ASTAR_BASE:
	{
		m_game->ChangeLevel("lvl_astar");
		InputManager::GetInstance()->ShockOff();
	}break;
	}
}
