#include "ImageManager.h"

ImageManager::ImageManager(HWND hWnd, const char* text)
{
	bmpLoader(text);
}


ImageManager::~ImageManager()
{
	DeleteObject(hBitmap);
	DeleteDC(hCompatibleDC);
}

void ImageManager::bmpLoader(const char* text) {
	hBitmap = LoadImage(NULL, text, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
}

void ImageManager::hndLoader(HWND hWnd, HDC hDC) {
	hCompatibleDC = CreateCompatibleDC(hDC);
	hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
	GetClientRect(hWnd, &Rect);
}

void ImageManager::PrintPic(HDC hDC, int x, int y, int lenght) {
	StretchBlt(hDC, x, y, lenght, lenght, hCompatibleDC, 0, 0, Bitmap.bmWidth,
		Bitmap.bmHeight, SRCCOPY);
	SelectObject(hCompatibleDC, hOldBitmap);
}

void ImageManager::delObj() {
	DeleteObject(hBitmap);
	DeleteDC(hCompatibleDC);
}
