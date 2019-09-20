#pragma warning(disable : 4996)
#include "SClock.h"
#include <math.h>

#define M_PI       3.14

SClock::SClock(int x, int y, int lenght)
{
	OnePoint.x = x;
	OnePoint.y = y;
	Initialize(OnePoint, lenght);

	SetPosHour();
}

// Получаю x, y координат мыши.
void SClock::SetPosClock(int x, int y) {
	// Перемещение центра циферблата
	Center.x = x + (lenght / 2);
	Center.y = y + (lenght / 2);
	// Перемещение рамки
	Box.HLeft.x = x;
	Box.HLeft.y = y;
	// HRight
	Box.HRight.x = x + lenght;
	Box.HRight.y = y;
	// LRight
	Box.LRight.x = x + lenght;
	Box.LRight.y = y + lenght;
	// LLeft
	Box.LLeft.x = x;
	Box.LLeft.y = y + lenght;
	// Перемещение цифер
	hn = true;
	SetPosHour();
	hn = false;
}


SClock::~SClock(){}

void SClock::Initialize(SPoint hLeft, int lenght) {
	// Initialize Box
	this->lenght = lenght;
	Box.HLeft = hLeft;
	// HRight
	Box.HRight.x = Box.HLeft.x + lenght;
	Box.HRight.y = Box.HLeft.y;
	// LRight
	Box.LRight.x = Box.HLeft.x + lenght;
	Box.LRight.y = Box.HLeft.y + lenght;
	// LLeft
	Box.LLeft.x = Box.HLeft.x;
	Box.LLeft.y = Box.HLeft.y + lenght;

	Center.x = Box.HLeft.x + (lenght / 2);
	Center.y = Box.HLeft.y + (lenght / 2);

	
	hn = true;
}

SBox SClock::GetBox() {
	return this->Box;
}

SPoint SClock::GetCenter() {
	return this->Center;
}

void SClock::STimSec(int time) {
	angle_SEC = (time * 6) - 90;
}

void SClock::STimMin(int time) {
	angle_MIN = (time * 6) - 90;
}

void SClock::STimHour(int time) {
	angle_HOUR = (time * 30) - 90;
}

void SClock::SWork_SEC() {
	
	degs = (M_PI * angle_SEC) / 180;

	x = ((Center.x) + ((lenght / 2) * cos(degs)));
	y = ((Center.y) + ((lenght / 2) * sin(degs)));

	if (angle_SEC >= 360) {
		angle_SEC = 0;
	}
}

void SClock::SWork_MIN() {

	degs = (M_PI * angle_MIN) / 180;

	x = ((Center.x) + ((lenght / 2) * cos(degs)));
	y = ((Center.y) + ((lenght / 2) * sin(degs)));

	if (angle_MIN >= 360) {
		angle_MIN = 0;
	}
}

void SClock::SWork_HOUR() {

	degs = (M_PI * angle_HOUR) / 180;

	x = ((Center.x) + ((lenght / 2) * cos(degs)));
	y = ((Center.y) + ((lenght / 2) * sin(degs)));

	if (angle_HOUR >= 360) {
		angle_HOUR = 0;
	}
}

void SClock::PrintBox(HDC hDC) {
	MoveToEx(hDC, Box.HLeft.x, Box.HLeft.y, NULL);

	LineTo(hDC, Box.HRight.x, Box.HRight.y);
	LineTo(hDC, Box.LRight.x, Box.LRight.y);
	LineTo(hDC, Box.LLeft.x, Box.LLeft.y);
	LineTo(hDC, Box.HLeft.x, Box.HLeft.y);

	//LineTo(hDC, Center.x, Center.y);
}

void SClock::PrintDial(HDC hDC) {
	
	// minute
	MoveToEx(hDC, Center.x, Center.y, NULL);

	SWork_MIN();

	if (angle_MIN >= 360) {
		angle_MIN = 0;
	}

	LineTo(hDC, x, y);
	// hour
	MoveToEx(hDC, Center.x, Center.y, NULL);

	SWork_HOUR();

	if (angle_HOUR >= 360) {
		angle_HOUR = 0;
	}

	LineTo(hDC, x, y);

	MoveToEx(hDC, Center.x, Center.y, NULL);
	// sec
	SWork_SEC();

	if (angle_SEC >= 360) {
		angle_SEC = 0;
	}

	LineTo(hDC, x, y);
}

// ASKII
// Настройка чисел
void SClock::PrintNum(HDC hDC) {
	
	GetTextExtentPoint32(hDC, str_text, sizeof(str_text), &SX);

	for (int i = 0; i <= 12; i++) {

		if (i == 0) {
			str_text[0] = (const char)49;
			TextOut(hDC, HN[i].x - (SX.cx / 2), HN[i].y - (SX.cy / 2), str_text, sizeof(str_text));
			str_text[0] = (const char)50;
			TextOut(hDC, (HN[i].x - SX.cx) + SX.cx, HN[i].y - (SX.cy / 2), str_text, sizeof(str_text));
		}
		else if (i >= 1 && i <= 9) {
			str_text[0] = (const char)num++;
			TextOut(hDC, HN[i].x - (SX.cx / 2), HN[i].y - (SX.cy / 2), str_text, sizeof(str_text));
		}
		else if (i == 10) {
			str_text[0] = (const char)49;
			TextOut(hDC, HN[i].x - (SX.cx / 2), HN[i].y - (SX.cy / 2), str_text, sizeof(str_text));
			str_text[0] = (const char)48;
			TextOut(hDC, (HN[i].x - SX.cx) + SX.cx, HN[i].y - (SX.cy / 2), str_text, sizeof(str_text));
		}
		else if (i == 11) {
			str_text[0] = (const char)49;
			TextOut(hDC, HN[i].x - (SX.cx / 2), HN[i].y - (SX.cy / 2), str_text, sizeof(str_text));
			str_text[0] = (const char)49;
			TextOut(hDC, (HN[i].x - SX.cx) + SX.cx, HN[i].y - (SX.cy / 2), str_text, sizeof(str_text));
		}
	}
	num = 49;
}

void SClock::SetPosHour() {
	while (hn) {
		SPoint Hour_Num;
		double degs1;
		int angle1;
		for (int time = 0; time <= 12; time++) {
			angle1 = (time * 30) - 90;
			degs1 = (M_PI * angle1) / 180;
			Hour_Num.x = ((Center.x) + ((lenght / 2) * cos(degs1)));
			Hour_Num.y = ((Center.y) + ((lenght / 2) * sin(degs1)));
			HN[time] = Hour_Num;
		}
		hn = false;
	}
}