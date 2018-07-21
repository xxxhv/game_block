#pragma once
#include <windows.h>
#define W 900
#define H 640

#define nw 80
#define nh 60

bool a[nw][nh] = { 0 };


void init()
{
	for (int i = 0; i < nw; i++)
	{
		for (int j = 0; j < nh; j++)
		{
			if (rand()%5==1)
			{
				a[i][j] = true;
			}
			else
			{
				a[i][j] = false;
			}
		}
	}
}

void theLife()
{
	bool b[nw][nh];
	int n = 0;

	for (int i = 0; i < nw; i++)
	{
		for (int j = 0; j < nh; j++)
		{
			b[i][j] = a[i][j];
		}
	}
	
	for (int i = 0; i < nw; i++)
	{
		for (int j = 0; j < nh; j++)
		{
			if (a[i - 1][j - 1] == true)
			{
				n++;
			}
			if (a[i - 1][j] == true)
			{
				n++;
			}
			if (a[i - 1][j + 1] == true)
			{
				n++;
			}

			if (a[i + 1][j - 1] == true)
			{
				n++;
			}
			if (a[i + 1][j] == true)
			{
				n++;
			}
			if (a[i + 1][j + 1] == true)
			{
				n++;
			}

			if (a[i][j - 1] == true)
			{
				n++;
			}
			if (a[i][j + 1] == true)
			{
				n++;
			}
			if (n < 2 || n>3)
			{
				b[i][j] = false;
			}
			if (n == 3)
			{
				b[i][j] = true;
			}
			n = 0;
		}
	}

	for (int i = 0; i < nw; i++)
	{
		for (int j = 0; j < nh; j++)
		{
			a[i][j] = b[i][j];
		}
	}
}










//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////

void p(HDC dc)
{
	for (int i = 0; i < nw; i++) 
	{
		for (int j = 0; j < nh; j++)
		{
			if (a[i][j] == true)
			{
				Rectangle(dc, i * 10, j * 10, i * 10 + 11, j * 10 + 11);
			}
		}
	}
}


void OnPrint(HDC hdc)
{

	HDC ncDC;//设备环境句柄  设备环境（Device Context，简称 DC）
	ncDC = CreateCompatibleDC(hdc);//内存DC和窗口DC兼容
	HBITMAP HMenDC = CreateCompatibleBitmap(hdc, W, H);//创建一张纸
	SelectObject(ncDC, HMenDC);//位图给内存DC


	Rectangle(ncDC, 0, 0, W, H);
	p(ncDC);

	BitBlt(hdc, 0, 0, W, H, ncDC, 0, 0, SRCCOPY);
	DeleteObject(HMenDC);
	DeleteDC(ncDC);
}
