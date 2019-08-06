#pragma once
#include <Windows.h>

struct SPoint {
	long x;
	long y;
};

struct SBox {
	SPoint HLeft;
	SPoint HRight;
	SPoint LLeft;
	SPoint LRight;
};

class SClock
{
public:
	SClock(int x, int y, int lenght);
	~SClock();
	void Initialize(SPoint hLeft, int lenght);
	SBox GetBox();
	SPoint GetCenter();

	void STimSec(int time);
	void STimMin(int time);
	void STimHour(int time);

	void SWork_SEC();
	void SWork_MIN();
	void SWork_HOUR();

	double angle_SEC;
	double angle_MIN;
	double angle_HOUR;

	int x, y;
	double degs;
	int lenght;

	void PrintBox(HDC hDC);
	void PrintDial(HDC hDC);
	void PrintNum(HDC hDC);
private:
	SBox Box;
	SPoint OnePoint;
	SPoint Center;
	SIZE SZ;
	int num = 49;
	char str_text[2];
	SPoint HN[12];
	boolean hn;
	SIZE SX;

	void SetPosHour();
};

