#pragma once

#pragma pack(push, 1)

typedef struct _tgPACKETHEADER
{
	unsigned int pktID;
	unsigned int size;
	unsigned int userID;
}PACKETHEADER, *LPPACKETHEADER;

#define PKT_MAX_USER 0xdcba0001
#define PKT_SAME_ID 0xaaaaaaaa
#define PKT_LOGOUT 0xbbbbbbbb
#define PKT_SENDOVER_LOGIN 0xbbbb0001
#define PKT_LOGMEIN 0xaaaa0001
typedef struct _tgLogin : public PACKETHEADER
{
	char strID[30];
}LOGIN, *LPLOGIN;

#define PKT_UPDATE_LOGINFO 0xcccc0001
#define PKT_CHARNUM 0xcccccccc
typedef struct _tgCharacter : public LOGIN
{
	int charNumber;
	int totalUser;
	float bossHealth;
}CHARACTER, *LPCHARACTER;

#define PKT_EXECUTE 0xabcd0001
typedef struct _tgExecute : public LOGIN
{
	float deltaDamage;
	float damageDealten;
}EXECUTE, *LPEXECUTE;

//#define PKT_SERVERCHARMOVE	0xa0000100
//typedef struct _tgSERVERCHARMOVE : public PACKETHEADER
//{
//	int curX;
//	int curY;
//	float count;
//	int ballX;
//	int ballY;
//	int serverScore;
//	int clientScore;
//
//	_tgSERVERCHARMOVE() : PACKETHEADER(PKT_SERVERCHARMOVE, sizeof(SERVERCHARMOVE)) {}
//}SERVERCHARMOVE, *LPSERVERCHARMOVE;
//
//#define PKT_CLIENTCHARMOVE 0xc0000010
//typedef struct _tgCLIENTCHARMOVE : public PACKETHEADER
//{
//	int curX;
//	int curY;
//
//	_tgCLIENTCHARMOVE() : PACKETHEADER(PKT_CLIENTCHARMOVE, sizeof(CLIENTCHARMOVE)) {}
//}CLIENTCHARMOVE, * LPCLIENTCHARMOVE;
//
//#define PKT_LOGIN		0xb0000001
//typedef struct _tgLOGIN : public PACKETHEADER
//{
//	bool active;
//	_tgLOGIN() : PACKETHEADER(PKT_LOGIN, sizeof(LOGIN)) {}
//}LOGIN, *LPLOGIN;

#pragma pack(pop)