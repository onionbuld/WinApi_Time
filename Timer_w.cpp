#pragma warning(disable : 4996)
#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "KWnd.h"
#include "SClock.h"


#define M_PI       3.14

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//==================================================================== 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG msg;

	KWnd mainWnd("Timer", hInstance, nCmdShow, WndProc);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
//==================================================================== 
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hDC;
	PAINTSTRUCT ps;
	static tm *newtime;
	time_t t;
	static SClock clock(15, 35, 256);
	static SBox box;
	static SPoint center;
	static char str[80] = "";
	static char str_text[] = "";
	static char str_Debug[80] = "";
	SIZE SX;
	// --------------------------
	// Debug
	// --------------------------

	switch (uMsg)
	{
	case WM_CREATE:
		hDC = GetDC(hWnd);
		SetTimer(hWnd, 1, 1000, NULL);
		box = clock.GetBox();
		center = clock.GetCenter();
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		TextOut(hDC, 1, 1, str, strlen(str));
		// -------------------------------------------
		clock.PrintBox(hDC);
		clock.PrintDial(hDC);

		//GetTextExtentPoint32(hDC, str_text, sizeof(str_text), &SX);
		//TextOut(hDC, clock.x - (SX.cx / 2), clock.y - (SX.cy / 2), str_text, sizeof(str_text));

		// debug

		TextOut(hDC, 430, 1, "Debug", 5);

		TextOut(hDC, 400, 80, "Angle:", 6);
		_itoa_s(clock.angle_SEC + 90, str_Debug, 10);
		TextOut(hDC, 440, 80, str_Debug, strlen(str_Debug));

		//TextOut(hDC, 400, 100, "TEXT CX:", 8);
		//_itoa_s(SX.cx, str_Debug, 10);
		//TextOut(hDC, 465, 100, str_Debug, strlen(str_Debug));

		//TextOut(hDC, 400, 120, "TEXT CY:", 8);
		//_itoa_s(SX.cy, str_Debug, 10);
		//TextOut(hDC, 465, 120, str_Debug, strlen(str_Debug));

		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		t = time(NULL);
		newtime = localtime(&t);

		clock.STimSec(newtime->tm_sec);
		clock.STimMin(newtime->tm_min);
		clock.STimHour(newtime->tm_hour);

		strcpy_s(str, asctime(newtime));
		str[strlen(str) - 1] = '\0';
		InvalidateRect(hWnd, NULL, 1);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}