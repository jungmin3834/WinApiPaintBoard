#include <iostream>
#include<Windows.h>
#include<tchar.h>
#include<vector>
#include "resource.h"
#include "Handler.h"
#include "UI.h"
using namespace std;

extern vector<SHAPE> g_vector;
extern SHAPE basic;

bool bNowDraw;
bool blockPoint;
LRESULT OnCreat(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	Ui_Creat(hwnd, lParam);	
	blockPoint = true;
	return 0;
}

LRESULT OnLButtonDown(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	Ui_PointSetting(hwnd, lParam);

	return 0;
}
LRESULT OnMouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (blockPoint == true){
		mousePt(hwnd, lParam);
	}
	if (bNowDraw == true){
		

	if (basic.type == 0)
	{
		basic.start = MAKEPOINTS(lParam);

		HDC hdc = GetDC(hwnd);
		Ui_GetPen(hwnd,hdc);

		SetROP2(hdc, R2_COPYPEN);
		
		Ui_MoveLine(hdc);

		g_vector.push_back(basic);
		basic.end = MAKEPOINTS(lParam);

		Ui_MoveLine(hdc);

		g_vector.push_back(basic);
		ReleaseDC(hwnd, hdc);
		
		return 0;
	}

	HDC hdc = GetDC(hwnd);
	basic.end = MAKEPOINTS(lParam);
	Ui_GetPen(hwnd, hdc);

		
		if (basic.type == 1)
		{
			
			SetROP2(hdc, R2_NOT); 
			Ui_MoveLine(hdc);
			basic.end = MAKEPOINTS(lParam);
			Ui_MoveLine(hdc);

		}
		else
			Ui_MakeForm(hwnd, hdc, lParam);
		
		Ui_Release(hwnd, hdc);
	}
	return 0;
}

LRESULT OnLButtonUP(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	bNowDraw = FALSE;
	HDC hdc = GetDC(hwnd);
	Ui_GetPen(hwnd, hdc);

	
	if (basic.type == 0 )
	{

		Ui_MoveLine(hdc);
		basic.type = 10;
		g_vector.push_back(basic);
		basic.type = 0;

		
		

	}
	else if (basic.type == 1)
	{
		Ui_MoveLine(hdc);
		g_vector.push_back(basic);
	}
	else{
		if (GetCapture() == hwnd) {
			ReleaseCapture();
			HDC hdc = GetDC(hwnd);
			Ui_GetPen(hwnd, hdc);

			Ui_UpDraw(hdc);

			// 디폴트 그리기 모드가 R2_COPYPEN 이다. 

			Ui_Release(hwnd, hdc);
			g_vector.push_back(basic);
		}
	}


		

		Ui_Release(hwnd, hdc);



		
	
	return 0;
}

LRESULT OnPaint(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	PAINTSTRUCT ps; 
	HDC hdc = BeginPaint(hwnd, &ps);

	//=====================================
	for (unsigned int i = 0; i < g_vector.size(); i++)
	{
		Ui_PaintDraw(hdc, i);
	}
	//=====================================

	EndPaint(hwnd, &ps);
	return 0;
}


LRESULT OnDestroy(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Ui_Destroy(hwnd);

	return 0;
}

LRESULT OnTimer(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (wParam == 1)
	{
		Ui_Time(hwnd,lParam);	
	}
	return 0;
}

LRESULT OnCommend(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (wParam)
	{
		case ID_40001:   //새파일
		{
							 g_vector.clear();
							 InvalidateRect(hwnd, 0, true);
		} break;
		case ID_40002:  //종료
		{
							SendMessage(hwnd, WM_DESTROY, wParam, lParam);
		} break;
		case    ID_40008:
		{

							if (g_vector.size() <= 0)
								return 0;
							if (g_vector[g_vector.size() - 1].type == 10)
											g_vector.pop_back();
						

							if (g_vector[g_vector.size() - 1].type == 0)
							{
								do{
								
									if(g_vector[g_vector.size() - 1].type == 0)
									{
										if (g_vector[g_vector.size() - 1].type == 10)
										{
											g_vector.pop_back();
											return 0;
										}
										g_vector.pop_back();
										InvalidateRect(hwnd, 0, true);

									}

									if (g_vector.size() == 0)
									{
										InvalidateRect(hwnd, 0, true);
										return 0;
									}
									else if (g_vector.size() == 1)
									{
										if (g_vector[g_vector.size() - 1].type == 0)
										{
											g_vector.pop_back();
											InvalidateRect(hwnd, 0, true);
											return 0;
										}
										else{

											return 0;
										}
									}

								} while (g_vector[g_vector.size() - 2].type == 0);
							}
							
		

							g_vector.pop_back();
							InvalidateRect(hwnd, 0, true);
		
		}break;
		case   ID_40023: //그리기
		{
							 basic.type = 0;
		}break;
		case   ID_40004: //선
		{
							 basic.type = 1;

		} break;
		case   ID_40005: //사각형
		{
							 basic.type = 2;

		} break;
		case   ID_40006: //원
		{
							 basic.type = 3;

		} break;
		case ID_40012:   //MENUITEM "빨간색(&R)",  
		{
							 basic.color = RGB(255, 0, 0);
		} break;
		case ID_40013:	//MENUITEM "녹색(&G)",     
		{
							basic.color = RGB(0, 255, 0);
		} break;
		case ID_40014:	//MENUITEM "파랑색(&B
		{
							basic.color = RGB(0, 0, 255);
		} break;
		case  ID_40016:	//MENUITEM "검은색(&K)",  
		{
							basic.color = RGB(0, 0, 0);
		} break;

		case ID_40018:	//MENUITEM "가늘게(1)",   
		{
							basic.wight = 1;
		} break;
		case ID_40019:	//MENUITEM "보통(3)",       
		{
							basic.wight = 3;
		} break;
		case ID_40020:	//MENUITEM "두껍게(5)",    
		{
							basic.wight = 5;
		} break;
		case    ID_40022:
		{
							MessageBox(hwnd, TEXT("201510571/손병준"), TEXT("API 과제 1"), MB_OK);
		}break;
		case   ID_40010:
		{
						   blockPoint == true? blockPoint = false : blockPoint = true;
						   InvalidateRect(hwnd, 0, true);
		}
	}


	return 0;
}
