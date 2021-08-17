#include "lvlAstar.h"

#include "InputManager.h"
#include "Button.h"
#include "AStarPath.h"
#include "Vector2.h"

lvlAstar::lvlAstar(Game* game, std::string name) : Level(game, name)
{
}

lvlAstar::~lvlAstar()
{
}

void lvlAstar::Init()
{
	Level::Init();

	auto title_button = static_cast<Button*>(m_obj[102]);

	std::string font = "Comic Sans MS";

	title_button->SetFont(font);
	title_button->SetText("Back");
	title_button->SetFontSize(24);
	title_button->SetSize(0.5f, 0.5f);
	title_button->RegisterButton(this, (int)ButtonWork::TITLE);
}

void lvlAstar::Update(Graphics* g, DWORD tick)
{
	ExecuteInputs(tick);

	Level::Update(g, tick);

	AStarPath* path = static_cast<AStarPath*>(m_obj[101]);
	path->Calculate();
}

void lvlAstar::OnRecievePacket(void* packet)
{
}

void lvlAstar::ButtonProcess(int index)
{
	const ButtonWork btnWork = static_cast<ButtonWork>(index);
	switch (btnWork)
	{
	case ButtonWork::TITLE:
	{
		m_game->ChangeLevel("lvl_title");
		InputManager::GetInstance()->ShockOff();
	}break;
	}
}

void lvlAstar::ExecuteInputs(DWORD tick)
{
	const float deltatime = (float)tick / 1000.0f;

	const auto input = InputManager::GetInstance();
	AStarPath* path = static_cast<AStarPath*>(m_obj[101]);
	AStarGraph* graph = path->GetGraph();

	BYTE key[256];
	::GetKeyboardState(key);

	Vector2 endMovement = Vector2::Zero;

	if (key[VK_UP] & 0x80) endMovement.y = -1.0f;
	else if (key[VK_DOWN] & 0x80) endMovement.y = 1.0f;
	if (key[VK_RIGHT] & 0x80) endMovement.x = 1.0f;
	else if (key[VK_LEFT] & 0x80) endMovement.x = -1.0f;
	endMovement.Normalize();
	endMovement *= deltatime * 150.0f;

	path->MoveEnd(endMovement.x, endMovement.y);

	Vector2 beginMovement = Vector2::Zero;

	if (key[0x57] & 0x80) beginMovement.y = -1.0f;
	else if (key[0x53] & 0x80) beginMovement.y = 1.0f;
	if (key[0x44] & 0x80) beginMovement.x = 1.0f;
	else if (key[0x41] & 0x80) beginMovement.x = -1.0f;
	beginMovement.Normalize();
	beginMovement *= deltatime * 150.0f;

	path->MoveBegin(beginMovement.x, beginMovement.y);

	if (input->GetLMouseClick())
	{
		auto point = input->GetMouseMovePos();
		graph->BlockNode((point.first - 4) / 16, (point.second - 4) / 16);
	}
	else if (input->GetRMouseClick())
	{
		auto point = input->GetMouseMovePos();
		graph->OpenNode((point.first - 4) / 16, (point.second - 4) / 16);
	}
}
