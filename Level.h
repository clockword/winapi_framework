#pragma once

#include <string>
#include <map>
#include <set>
#include <memory>

#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

class Game;
class GameObject;
class Level
{
protected:
	typedef std::map<int, GameObject*> OBJMAP;
	std::string m_name;
	OBJMAP m_obj;
	std::set<std::string> m_users;

	Game* m_game;

public:
	Level() = delete;
	Level(Game* game, std::string name);
	virtual ~Level();

	virtual void Init();
	virtual void Update(Graphics* g, DWORD tick);

	void Load();
	void Unload();

	std::string GetName()const { return m_name; }
	Game* GetGame()const { return m_game; }
	GameObject* GetGameobject(int index) { return m_obj[index]; }

	template<class T>
	T AddGameobject(int index);

	virtual void OnRecievePacket(void* packet) = 0;

	virtual void ButtonProcess(int index) = 0;

};

