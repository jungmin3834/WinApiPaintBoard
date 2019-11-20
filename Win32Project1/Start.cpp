#include <windows.h>
#include <tchar.h>
#include<wchar.h>
#include <vector>
#include "handler.h"
#include "resource.h"
using namespace std;


vector<SHAPE> g_vector;
SHAPE basic;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_LBUTTONDOWN:  OnLButtonDown(hwnd, msg, wParam, lParam);   break;
		case WM_LBUTTONUP:        OnLButtonUP(hwnd, msg, wParam, lParam);		    break;
		case WM_COMMAND:        OnCommend(hwnd, msg, wParam, lParam); 	 break;
		case WM_MOUSEMOVE:         OnMouseMove(hwnd, msg, wParam, lParam);   break;
		case WM_TIMER:               OnTimer(hwnd, msg, wParam, lParam);		   break;
		case WM_CREATE:	              OnCreat(hwnd, msg, wParam, lParam);			 break;
		case WM_DESTROY:	        OnDestroy(hwnd, msg, wParam, lParam);      break;
		case WM_PAINT:              OnPaint(hwnd, msg, wParam, lParam);			 break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 LPTSTR lpCmdLine, int nShowCmd)
{
	// 1. 윈도우 클래스 만들기 
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;			// DefWindowProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = 0;
	wc.hIconSm = LoadIcon(0, IDI_APPLICATION);

	// 2. 등록(레지스트리에)
	RegisterClassEx(&wc);

	// 3. 윈도우 창 만들기 
	HWND hwnd = CreateWindowEx(0,					// WS_EX_TOPMOST
							   TEXT("first"),				// 클래스 명
							   TEXT("Hello"),				// 캡션바 내용
							   WS_OVERLAPPEDWINDOW,
							   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	// 초기 위치 
							   0, 0,			// 부모 윈도우 핸들, 메뉴 핸들
							   hInstance,		// WinMain의 1번째 파라미터 (exe 주소)
							   0);			// 생성 인자



	// 4. 윈도우 보여주기
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);


	// 5. Message 
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}