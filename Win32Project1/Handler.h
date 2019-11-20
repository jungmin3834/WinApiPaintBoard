struct SHAPE{

	POINTS start;
	POINTS end;
	int       type;
	COLORREF color;
	int       wight;
};



LRESULT OnCommend(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT OnCreat(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT OnMouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT OnDestroy(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT OnTimer(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT OnLButtonDown(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT OnLButtonUP(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT OnPaint(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);