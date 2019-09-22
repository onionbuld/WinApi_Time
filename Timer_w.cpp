#pragma warning(disable : 4996)
#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "KWnd.h"
#include "SClock.h"


#define ID_MYBUTTON 1
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
	static char str_Debug[80] = "";
	static int xMouse = 1, yMouse = 1;
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

		CreateWindow("button", "Кнопка", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 700, 5, 100, 20, hWnd, (HMENU)ID_MYBUTTON, NULL, NULL);

		ReleaseDC(hWnd, hDC);
		break;
		
	case WM_MOUSEMOVE:
		
		hDC = GetDC(hWnd);

		if (wParam == MK_CONTROL) {
			xMouse = LOWORD(lParam);
			yMouse = HIWORD(lParam);

			clock.SetPosClock(xMouse, yMouse);
		}

		ReleaseDC(hWnd, hDC);
		break;
		
	case WM_RBUTTONDOWN:

		hDC = GetDC(hWnd);

		xMouse = LOWORD(lParam);
		yMouse = HIWORD(lParam);

		clock.SetPosClock(xMouse, yMouse);

		ReleaseDC(hWnd, hDC);
		break;

	case WM_LBUTTONDOWN:

		hDC = GetDC(hWnd);

		//xMouse = LOWORD(lParam);
		//yMouse = HIWORD(lParam);

		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:

		hDC = BeginPaint(hWnd, &ps);

		TextOut(hDC, 1, 1, str, strlen(str));
		// -------------------------------------------
		clock.PrintBox(hDC);
		clock.PrintDial(hDC);
		clock.PrintNum(hDC);
		// -------------------------------------------
		
		// -------------------------------------------
		// debug
		// -------------------------------------------
		TextOut(hDC, 430, 1, "Debug", 5);

		TextOut(hDC, 400, 80, "Angle:", 6);
		_itoa_s(clock.angle_SEC + 90, str_Debug, 10);
		TextOut(hDC, 440, 80, str_Debug, strlen(str_Debug));

		TextOut(hDC, 520, 80, "X:", 2);
		_itoa_s(xMouse, str_Debug, 10);
		TextOut(hDC, 540, 80, str_Debug, strlen(str_Debug));

		TextOut(hDC, 580, 80, "Y:", 2);
		_itoa_s(yMouse, str_Debug, 10);
		TextOut(hDC, 600, 80, str_Debug, strlen(str_Debug));

		// -------------------------------------------
		EndPaint(hWnd, &ps);
		break;

	case WM_TIMER:

		t = time(NULL);
		newtime = localtime(&t);
		// -------------------------------------------
		clock.STimSec(newtime->tm_sec);
		clock.STimMin(newtime->tm_min);
		clock.STimHour(newtime->tm_hour);
		// -------------------------------------------
		strcpy_s(str, asctime(newtime));
		str[strlen(str) - 1] = '\0';
		InvalidateRect(hWnd, NULL, 1);
		break;

	case WM_COMMAND:
		if ((HIWORD(wParam) == 0) && (LOWORD(wParam) == ID_MYBUTTON)) {
			MessageBox(hWnd, "Ты нажал на кнопку!", "Сообщение!", MB_OK | MB_ICONWARNING);
		}
		if (HIWORD(wParam) == 0) {
			char buf[256];
			switch (LOWORD(wParam)) {
			case 40001: 
				wsprintf(buf, "Это пункт меню? Шутите?");
				MessageBox(hWnd, buf, "Сообщение!", MB_OK | MB_ICONINFORMATION);
				break;
			default:
				wsprintf(buf, "Код: %d", LOWORD(wParam));
				MessageBox(hWnd, buf, "Сообщение!", MB_OK | MB_ICONINFORMATION);
			}
		}
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break; 

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}
