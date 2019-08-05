#pragma warning(disable : 4996)
#include "SClock.h"
#include <math.h>

#define M_PI       3.14

SClock::SClock(int x, int y, int lenght)
{
	OnePoint.x = x;
	OnePoint.y = y;
	Initialize(OnePoint, lenght);
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

	x = ((Center.x) + ((256 / 2) * cos(degs)));
	y = ((Center.y) + ((256 / 2) * sin(degs)));

	if (angle_SEC >= 360) {
		angle_SEC = 0;
	}
}

void SClock::SWork_MIN() {

	degs = (M_PI * angle_MIN) / 180;

	x = ((Center.x) + ((256 / 2) * cos(degs)));
	y = ((Center.y) + ((256 / 2) * sin(degs)));

	if (angle_MIN >= 360) {
		angle_MIN = 0;
	}
}

void SClock::SWork_HOUR() {

	degs = (M_PI * angle_HOUR) / 180;

	x = ((Center.x) + ((256 / 2) * cos(degs)));
	y = ((Center.y) + ((256 / 2) * sin(degs)));

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

	LineTo(hDC, Center.x, Center.y);
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