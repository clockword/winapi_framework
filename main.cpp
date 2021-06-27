#include <WinSock2.h>
#include <stdlib.h>
#include <ctime>
#include "Game.h"
#include "InputManager.h"
#include "CircleQueue.h"

#pragma comment(lib,"WS2_32.lib")

//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif

#define WM_SOCKET	WM_USER+1
#define BUFSIZE		1024

Graphics *g_BackBuffer;
Graphics *g_MainBuffer;
Bitmap    *g_Bitmap;
Pen		   *g_pPen;

SOCKET g_sock = INVALID_SOCKET;
CircleQueue g_cirQueue;

Game g_game;

void OnUpdate(HWND hWnd, DWORD tick);
void CreateBuffer(HWND hWnd, HDC hDC);
void ReleaseBuffer(HWND hWnd, HDC hDC);

void err_quit(char* msg);

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,     int nCmdShow)
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	// 온리 로컬플레이만
	std::string ip;
	char ucHostName[255];
	if (0 == gethostname(ucHostName, sizeof(ucHostName)))
	{
		PHOSTENT phostInfo = gethostbyname(ucHostName);
		if (NULL != phostInfo)
		{
			in_addr* pAddr = (in_addr*)phostInfo->h_addr_list[0];
			ip += std::to_string(pAddr->S_un.S_un_b.s_b1);
			ip += '.';
			ip += std::to_string(pAddr->S_un.S_un_b.s_b2);
			ip += '.';
			ip += std::to_string(pAddr->S_un.S_un_b.s_b3);
			ip += '.';
			ip += std::to_string(pAddr->S_un.S_un_b.s_b4);
		}
	}
	g_game.SetIp(ip);

	srand(time(NULL));

	WNDCLASS   wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
	wndclass.hIcon = NULL;
    wndclass.hCursor = NULL;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = "WinApi";
	
	if(RegisterClass(&wndclass) == 0)
	{
		WSACleanup();
		return 0;		
	}

	RECT rc = { 0, 0, 1024, 768 };
	::AdjustWindowRect(&rc,
		WS_POPUP | WS_THICKFRAME | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX,
		FALSE);

	HWND hwnd = CreateWindow("WinApi", "WinApiExamples",
		WS_POPUP | WS_THICKFRAME | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX,
		100, 100, rc.right-rc.left, rc.bottom-rc.top, NULL, NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
		WSACleanup();
		return 0;
	}

	HDC hDC = GetDC(hwnd);


	CreateBuffer(hwnd, hDC);

	g_pPen = new Pen(Color(255, 0, 0), 1.0f);

	g_game.Init();

	ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

	MSG msg;
	DWORD tick = GetTickCount();
	while(g_game.Run())
	{	
		//윈도우 메세지가 있을경우 메세지를 처리한다.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else //메세지가 없을 경우 게임 루프를 실행한다.
		{		
			DWORD curTick = GetTickCount();
			OnUpdate(hwnd, curTick - tick);
			tick = curTick;

			
			g_MainBuffer->DrawImage(g_Bitmap, 0, 0);
		}
	}

	g_game.Delete();
	closesocket(g_sock);
	delete g_pPen;
	WSACleanup();
	ReleaseBuffer(hwnd, hDC);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		InputManager::GetInstance()->SetMouseMovePos(x, y);
	}break;
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		InputManager::GetInstance()->SetMouseDownPos(x, y);
		InputManager::GetInstance()->SetMouseClick(true);
	}break;
	case WM_LBUTTONUP:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		InputManager::GetInstance()->SetMouseUpPos(x, y);
		InputManager::GetInstance()->SetMouseClick(false);
	}break;
	case WM_CHAR:
	{
		InputManager::GetInstance()->KeyBoardInput(wParam);
	}break;
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE) g_game.RunOff();
	}break;
	case WM_CREATE:
	{
		g_sock = socket(AF_INET, SOCK_STREAM, 0);
		if (g_sock == INVALID_SOCKET) err_quit("socket()");

		g_game.SetSocket(g_sock);

		g_game.SetWindowMessage(hWnd, WM_SOCKET);

	}break;
	case WM_SOCKET:
	{
		// 오류 발생 여부 확인
		if (WSAGETSELECTERROR(lParam))
		{
			err_quit("WSAGETSELECTERROR(lParam)...");
			break;
		}

		// 메시지 처리
		switch (WSAGETSELECTEVENT(lParam))
		{
		case FD_WRITE:
		{
		}
		break;
		case FD_READ:
		{
			// 데이터 통신에 사용할 변수
			char buf[BUFSIZE];
			int ret = recv(wParam, (char*)buf, BUFSIZE, 0);
			if (ret == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
				}
				break;
			}

			int val = g_cirQueue.Push(buf, ret);
			if (val != 1)
			{
				err_quit("Queue Error!!!");
				break;
			}

			LPPACKETHEADER pHeader = g_cirQueue.GetPacket();
			while (pHeader != (LPPACKETHEADER)NULL)
			{
				g_game.Recieve(pHeader);

				g_cirQueue.Pop(pHeader->size);
				pHeader = g_cirQueue.GetPacket();
			}
		}
		break;
		case FD_CLOSE:
		{
			closesocket(wParam);
		}
		break;
		}
	}break;
	case WM_DESTROY:
		//LOGIN logOut;
		//logOut.pktID = PKT_LOGOUT;
		//strcpy(logOut.strID, g_game.GetStringID().c_str());
		//logOut.size = sizeof(logOut);

		//g_game.Send(&logOut);

		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void CreateBuffer(HWND hWnd, HDC hDC)
{
	GdiplusStartupInput			gdiplusStartupInput;
	ULONG_PTR					gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	RECT rc;
	GetClientRect(hWnd, &rc);

	g_Bitmap = new Bitmap(rc.right - rc.left, rc.bottom - rc.top);
	g_BackBuffer = new Graphics(g_Bitmap);
	g_BackBuffer->SetPageUnit(Gdiplus::Unit::UnitPixel);
	
	g_MainBuffer = new Graphics(hDC);
	g_MainBuffer->SetPageUnit(Gdiplus::Unit::UnitPixel);
}

void ReleaseBuffer(HWND hWnd, HDC hDC)
{
	ReleaseDC(hWnd, hDC);

	delete g_Bitmap;
	delete g_BackBuffer;
	delete g_MainBuffer;
}

void OnUpdate(HWND hWnd, DWORD tick)
{
	if(hWnd == NULL)
		return;

	Color color(255, 255, 255);
	g_BackBuffer->Clear(color);
	
	g_game.Update(g_BackBuffer, tick);
}

void err_quit(char* msg)
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