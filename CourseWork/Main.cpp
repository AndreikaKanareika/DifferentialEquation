#include "Main.h"

using namespace std;


int APIENTRY _tWinMain(HINSTANCE This, HINSTANCE Prev, LPTSTR cmd, int mode)          
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	TCHAR className[] = "My";
	TCHAR className2[] = "My2";
	TCHAR windowName[] = "Graphic";
	TCHAR windowName2[] = "Settings";
	HWND hWnd;
	HWND hWnd2;
	MSG msg;
	
	
	hWnd = CreateAndRegisterWindow(This, className, windowName, WndProc, WS_OVERLAPPEDWINDOW, 500,700);
	hWnd2 = CreateAndRegisterWindow(This, className2, windowName2, WndProc2, WS_OVERLAPPED | WS_CAPTION, 500, 500);
	
	ShowWindow(hWnd, mode);
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}
	return 0;
}

HWND CreateAndRegisterWindow(HINSTANCE This, TCHAR *className, TCHAR *windowName, WNDPROC WndProc, DWORD style, int width, int height)
{
	WNDCLASS wc;

	wc.hInstance = This;
	wc.lpszClassName = className;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0;

	HWND hWnd = CreateWindowA(
		className,
		windowName,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width, // Width 		
		height, // Height 
		HWND_DESKTOP,
		NULL,
		This,
		NULL);

	return hWnd;
}


