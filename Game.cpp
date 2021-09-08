#define _CRT_SECURE_NO_WARNINGS

#include "Game.h"

#include <iostream>
#include <set>

#include "Level.h"

#include "World.h"
#include "ResourceManager.h"

#include "lvlTitle.h"
#include "lvlDijkstra.h"
#include "lvlAstar.h"
#include "lvlThread.h"

#define MAKELVL(name, type) std::make_shared<type>(this, name)

void Game::AddLevel(LVLPTR level)
{
	if (m_levels.find(level->GetName()) == m_levels.end())
	{
		m_levels.insert({ level->GetName(), level });
	}
}

void Game::err_quit(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(-1);
}

Game::Game()
{
	m_currentLevel = nullptr;

	m_fixedFrame = 0;
	m_fixedCount = 0;
	m_connectID = 0;

	m_run = true;

	m_socketTCP = INVALID_SOCKET;
}

Game::~Game()
{
	m_levels.clear();
	m_currentLevel = nullptr;
}

void Game::ChangeLevel(std::string name)
{
	if (m_currentLevel != nullptr)
	{
		m_currentLevel->Unload();
	}
	m_currentLevel = m_levels[name];
	m_currentLevel->Load();
	m_currentLevel->Init();
}

void Game::Connect(unsigned short portNumber, std::string ip)
{
	SOCKADDR_IN serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(portNumber);
	serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
	if (connect(m_socketTCP, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		closesocket(m_socketTCP);
		err_quit("connect Error.......");
	}

	if (WSAAsyncSelect(m_socketTCP, m_hwnd, m_msgSock, FD_WRITE | FD_READ | FD_CLOSE) != 0)
	{
		closesocket(m_socketTCP);
		err_quit("WSAAsyncSelect Error.......");
	}
}

void Game::Send(LPPACKETHEADER packet)
{
	int retval = send(m_socketTCP, (const char*)packet, packet->size, 0);
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
		}
	}
}

void Game::Recieve(LPPACKETHEADER packet)
{
	m_currentLevel->OnRecievePacket(packet);
}

bool Game::CheckUserID(std::string id)
{
	if (m_users.find(id) != m_users.end()) return true;
	return false;
}

bool Game::LogoutUser(std::string id)
{
	if (CheckUserID(id))
	{
		m_users.erase(id);
		return true;
	}
	return false;
}

bool Game::LoginUser(std::string id)
{
	if (!CheckUserID(id))
	{
		m_users.insert({ id, std::make_unique<UserInfo>() });
		m_users[id]->sessionCount = 0;
		return true;
	}
	return false;
}

Game::UserInfo* Game::GetUserInfo(const std::string& id)
{
	if (CheckUserID(id))
	{
		return m_users[id].get();
	}
	return nullptr;
}

int Game::TotalUser()
{
	return m_users.size();
}

void Game::SetUserNumberByPriority(const std::string& id)
{
	std::set<int> charNums;
	std::map<std::string, std::unique_ptr<UserInfo>>::iterator it;
	for (it = m_users.begin(); it != m_users.end(); it++)
	{
		if(it->second->id != m_users[id]->id)
			charNums.insert(it->second->charNumber);
	}
	int index = 0;
	for (int num : charNums)
	{
		if (++index != num)
		{
			m_users[id]->charNumber = index;
			return;
		}
	}
	m_users[id]->charNumber = ++index;
}

void Game::UpdateSessions(DWORD tick)
{
	std::map<std::string, std::unique_ptr<UserInfo>>::iterator it;
	for (it = m_users.begin(); it != m_users.end(); it++)
	{
		if (it->first == m_strID) continue;
		it->second->sessionCount += tick;
		if (it->second->sessionCount >= it->second->sessionLimit)
		{
			LogoutUser(it->first);
		}
	}
}

void Game::Init()
{
	m_fixedFrame = 15;

	AddLevel(MAKELVL("lvl_title", lvlTitle));
	AddLevel(MAKELVL("lvl_dijkstra", lvlDijkstra));
	AddLevel(MAKELVL("lvl_astar", lvlAstar));
	AddLevel(MAKELVL("lvl_thread", lvlThread));

	ChangeLevel("lvl_title");
}

void Game::Update(Graphics* g, DWORD tick)
{
	m_fixedCount += tick;
	if(m_currentLevel != nullptr) m_currentLevel->Update(g, tick);
	if (m_fixedCount >= m_fixedFrame)
	{
		World::GetInstance()->FixedUpdate(m_fixedCount);
		m_fixedCount = 0;
	}
}

void Game::Delete()
{
	ResourceManager::GetInstance()->DeleteImages();
}