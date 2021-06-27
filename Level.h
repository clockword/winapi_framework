#pragma once

#include <string>
#include <map>
#include <set>
#include <memory>

#include "Game.h"
#include "GameObject.h"
#include "Text.h"
#include "packet.h"

class Game;
class Level
{
private:
	typedef std::map<int, GameObject*> Objects;
	std::string m_name;
	Objects m_obj;
	bool m_isCleared;
	std::set<std::string> m_users;

	Game* m_game;

private:
	enum class ButtonWork
	{
		DIJKSTRA,
	};

	std::shared_ptr<void> m_variables;

public:
	bool GetIsClear()const { return m_isCleared; }
	std::string GetName()const { return m_name; }

public:
	Level(std::string name);
	virtual ~Level();

	void Init();
	void Update(Graphics* g, DWORD tick);

	void Load();
	void UnLoad();

	void SetThisGame(Game* game) { m_game = game; }
	Game* GetThisGame() { return m_game; }
	void* GetVariables();
	GameObject* GetGameObject(int index) { return m_obj[index]; }

	void (*LevelProcess)(Level* level, DWORD tick);

	void RecievePacket(LPPACKETHEADER packet);

private:
	static void ButtonProcess(void* ctx, int index);
};