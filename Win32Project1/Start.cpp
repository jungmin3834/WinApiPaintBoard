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
	// 1. ������ Ŭ���� ����� 
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

	// 2. ���(������Ʈ����)
	RegisterClassEx(&wc);

	// 3. ������ â ����� 
	HWND hwnd = CreateWindowEx(0,					// WS_EX_TOPMOST
							   TEXT("first"),				// Ŭ���� ��
							   TEXT("Hello"),				// ĸ�ǹ� ����
							   WS_OVERLAPPEDWINDOW,
							   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	// �ʱ� ��ġ 
							   0, 0,			// �θ� ������ �ڵ�, �޴� �ڵ�
							   hInstance,		// WinMain�� 1��° �Ķ���� (exe �ּ�)
							   0);			// ���� ����



	// 4. ������ �����ֱ�
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