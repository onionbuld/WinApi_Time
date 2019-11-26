#pragma once
#include <Windows.h>
#include <string>

class ImageManager
{
public:
	ImageManager(HWND hWnd, const char* text);
	~ImageManager();

	HDC hCompatibleDC;
	PAINTSTRUCT PaintStruct;
	HANDLE hBitmap, hOldBitmap;
	RECT Rect;
	BITMAP Bitmap;

	void PrintPic(HDC hDC, int x, int y, int lenght);
	void bmpLoader(const char* text);
	void hndLoader(HWND hWnd, HDC hDC);
	void delObj();
};

