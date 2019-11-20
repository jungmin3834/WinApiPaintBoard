#include <Windows.h>
#include<tchar.h>
#include<vector>
#include "UI.h"
#include "Handler.h"
#include "resource.h"

using namespace std;

extern vector<SHAPE> g_vector;
extern SHAPE basic;
extern bool bNowDraw;



//==========마우스 포인터
void mousePt(HWND hwnd, LPARAM lParam)
{
	HDC hdc = GetDC(hwnd);
	POINT pt = { LOWORD(lParam), HIWORD(lParam) };
	POINT pt1 = pt;
	ClientToScreen(hwnd, &pt);
	TCHAR temp[256];
	wsprintf(temp, TEXT("%04d  %04d"), pt1.x, pt1.y);
	TextOut(hdc, 10, 10, temp, wcslen(temp));
	ReleaseDC(hwnd, hdc);

}

void Ui_Time(HWND hwnd,LPARAM lParam)
{
	
	
	SYSTEMTIME st;
	GetLocalTime(&st);
	TCHAR buf[20];
	wsprintf(buf, TEXT("현재 시간 : %d:%d:%d"),
			 st.wHour, st.wMinute, st.wSecond);
	SetWindowText(hwnd, buf);
}



void Ui_Creat(HWND hwnd, LPARAM lParam){
	POINTS pt = MAKEPOINTS(lParam);
	basic = { pt, pt, 0, RGB(255, 0, 0), 1};
	SetTimer(hwnd, 1, 1000, NULL);
}

//==========마우스 기본 좌표
void Ui_PointSetting(HWND hwnd, LPARAM lParam)
{
	basic.start = MAKEPOINTS(lParam);
	basic.end = basic.start;
	if (basic.type > 1)SetCapture(hwnd);
	bNowDraw = TRUE;
}

//==========폼 만들기
void Ui_MakeForm(HWND hwnd,HDC hdc, LPARAM lParam)
{
	if (GetCapture() == hwnd){
		POINTS pt = MAKEPOINTS(lParam);

		SetROP2(hdc, R2_NOTXORPEN);
		// 그리기 모드 변경 
		SelectObject(hdc, GetStockObject(NULL_BRUSH));

		if (basic.type == 2)
		{
			Rectangle(hdc, basic.start.x, basic.start.y, basic.end.x, basic.end.y);
			Rectangle(hdc, basic.start.x, basic.start.y, pt.x, pt.y);
		}
		if (basic.type == 3)
		{
			Ellipse(hdc, basic.start.x, basic.start.y, basic.end.x, basic.end.y);
			Ellipse(hdc, basic.start.x, basic.start.y, pt.x, pt.y);
		}

		basic.end = pt; // 현재 점을 Old에 보관 ReleaseDC( hwnd, hdc );
	}
}
void Ui_MoveLine(HDC hdc)
{
	MoveToEx(hdc, basic.start.x, basic.start.y, NULL);
	LineTo(hdc, basic.end.x, basic.end.y);
}
void Ui_UpDraw(HDC hdc)
{
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	if (basic.type ==2)
	Rectangle(hdc, basic.start.x, basic.start.y, basic.end.x, basic.end.y);
	if (basic.type == 3)
	Ellipse(hdc, basic.start.x, basic.start.y, basic.end.x, basic.end.y);

}
//===========무효화=====
void Ui_PaintDraw(HDC hdc, int i)
{
	HPEN en = CreatePen(0, g_vector[i].wight, g_vector[i].color);
	HPEN pen = (HPEN)SelectObject(hdc, en);
	if (g_vector[i].type == 0){
		MoveToEx(hdc, g_vector[i].start.x, g_vector[i].start.y, NULL);
		LineTo(hdc, g_vector[i].end.x, g_vector[i].end.y);
	}
	else if (g_vector[i].type == 1){
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		MoveToEx(hdc, g_vector[i].start.x, g_vector[i].start.y, NULL);
		LineTo(hdc, g_vector[i].end.x, g_vector[i].end.y);

	}
	else if(g_vector[i].type == 2){
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, g_vector[i].start.x, g_vector[i].start.y, g_vector[i].end.x, g_vector[i].end.y);

	}
	else if(g_vector[i].type == 3){
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Ellipse(hdc, g_vector[i].start.x, g_vector[i].start.y, g_vector[i].end.x, g_vector[i].end.y);

	}
	DeleteObject(pen);
}
//===========팬 정보 및 릴리스 등 초기화 반납====
void Ui_GetPen(HWND hwnd,HDC hdc)
{
	HPEN en = CreatePen(0, basic.wight, basic.color);
	HPEN pen = (HPEN)SelectObject(hdc, en);
}

void Ui_Release(HWND hwnd, HDC hdc)
{
	HPEN en = CreatePen(0, basic.wight, basic.color);
	HPEN pen = (HPEN)SelectObject(hdc, en);
	DeleteObject(SelectObject(hdc,pen));
	ReleaseDC(hwnd, hdc);
}

void Ui_Destroy(HWND hwnd)
{
	KillTimer(hwnd, 1);
	PostQuitMessage(0);
}

