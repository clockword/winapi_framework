#pragma once
#include <string>
#include <map>
#include <memory>
#include <cstdio>

#include <WinSock2.h>  
#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;

#include "packet.h"

#define USERINFO Game::UserInfo

class Level;
class Game
{
public:
	typedef struct _userInfo
	{
		unsigned int id;
		int charNumber;
		const DWORD sessionLimit = 3000;
		DWORD sessionCount;
		_userInfo() : id(0), charNumber(-1) {}
	}UserInfo;

	typedef std::shared_ptr<Level> LVLPTR;
	typedef std::map<std::string, LVLPTR> LVLMAP;

private:
	SOCKET m_socketTCP;
	std::string m_ip;

	LVLMAP m_levels;
	LVLPTR m_currentLevel;

	DWORD m_fixedFrame;
	DWORD m_fixedCount;

	bool m_run;

	std::string m_strID;
	unsigned int m_connectID;

	std::map<std::string, std::unique_ptr<UserInfo>> m_users;

	HWND m_hwnd;
	u_int m_msgSock;

private:
	void AddLevel(LVLPTR level);
	
	void err_quit(char* msg);

public:
	Game();
	virtual ~Game();

	void ChangeLevel(std::string name);
	HWND GetWindow() { return m_hwnd; }

	bool Run()const { return m_run; }
	void RunOff() { m_run = false; }

	void SetIp(std::string ip) { m_ip = ip; }
	std::string GetIp()const { return m_ip; }
	void SetSocket(SOCKET sock) { m_socketTCP = sock; }

	void SetStringID(std::string str) { m_strID = str; }
	std::string GetStringID()const { return m_strID; }
	void SetConnectID(unsigned int id) { m_connectID = id; }
	unsigned int GetConnectID()const { return m_connectID; }

	void Connect(unsigned short portNumber, std::string ip);
	void Send(LPPACKETHEADER packet);
	void Recieve(LPPACKETHEADER packet);

	bool CheckUserID(std::string id);
	bool LogoutUser(std::string id);
	bool LoginUser(std::string id);
	UserInfo* GetUserInfo(const std::string& id);
	int TotalUser();
	void SetUserNumberByPriority(const std::string& id);
	void UpdateSessions(DWORD tick);

	void SetWindowMessage(HWND hwnd, u_int msg) { m_hwnd = hwnd; m_msgSock = msg; }

	void Init();
	void Update(Graphics* g, DWORD tick);
	void Delete();
};

