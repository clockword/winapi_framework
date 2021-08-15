#pragma once

#include <string>
#include <map>
#include <set>
#include <memory>

class Game;
class GameObject;
class Level
{
protected:
	typedef std::map<int, GameObject*> OBJMAP;
	std::string m_name;
	OBJMAP m_obj;
	bool m_isCleared;
	std::set<std::string> m_users;

	Game* m_game;

public:
	bool IsCleared()const { return m_isCleared; }
	std::string GetName()const { return m_name; }

	

};

