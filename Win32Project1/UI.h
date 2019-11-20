#include<Windows.h>
#include<tchar.h>


void Ui_PointSetting(HWND hwnd, LPARAM lParam);
void Ui_Creat(HWND hwnd, LPARAM lParam);
void Ui_GetPen(HWND hwnd,HDC hdc);
void mousePt(HWND hwnd, LPARAM lParam);
void Ui_MoveLine(HDC hdc);
void Ui_Release(HWND hwnd, HDC hdc);
void Ui_MakeForm(HWND hwnd, HDC hdc, LPARAM lParam);
void Ui_UpDraw(HDC hdc);
void Ui_PaintDraw(HDC hdc, int i);
void Ui_Destroy(HWND hwnd);
void Ui_Time(HWND hwnd, LPARAM lParam);