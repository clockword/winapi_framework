#pragma once
#include <string>
#include <map>
#include <memory>

#include "Level.h"
#include "World.h"
#include "Text.h"

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

private:
	SOCKET m_socketTCP;
	std::string m_ip;

	typedef std::map<std::string, Level*> Levels;
	Levels m_levels;
	Level* m_currentLevel;

	DWORD m_fixedFrame;
	DWORD m_fixedCount;

	bool m_run;

	std::string m_strID;
	unsigned int m_connectID;

	std::map<std::string, std::unique_ptr<UserInfo>> m_users;

	HWND m_hwnd;
	u_int m_msgSock;

private:
	void AddLevel(std::string name);
	
	void err_quit(char* msg);

public:
	Game();
	virtual ~Game();

	Level* GetCurrentLevel() { return m_currentLevel; }
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

