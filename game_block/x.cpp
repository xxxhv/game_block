#include "x.h"

int nblock;
int a[nW][nH] = { 0 };
int b[nW][nH] = { 0 };
int bx = -1, by = -1;
int nx = -1, ny = -1;
int score = 0;

//init
void init()
{

}

//dowm 下落行为
void block_down()
{
	by++;
	int i, j;
	for (j = nH -1; j >= 0; j--)
	{
		for (i = 0; i < nW; i++)
		{
			if (a[i][j] == 1)
			{
				a[i][j + 1] = a[i][j];
				a[i][j] = 0;
			}
		}
	}
}

void block_left()
{
	bx--;
	int i, j;
	for (i = 0; i < nW; i++)
	{
		for (j = 0; j < nH; j++)
		{
			if (a[i][j] == 1)
			{
				a[i - 1][j] = a[i][j];
				a[i][j] = 0;
			}
		}
	}
}
void block_right()
{
	bx++;
	int i, j;
	for (i = nW - 1; i >= 0; i--)
	{
		for (j = 0; j < nH; j++)
		{
			if (a[i][j] == 1)
			{
				a[i + 1][j] = a[i][j];
				a[i][j] = 0;
			}
		}
	}
}

void block_spin()
{
	int s[6] = { 0 };
	
	if (nblock == 3)
	{
		

		a[bx - 1][by] = 0; a[bx + 1][by] = 0; a[bx + 2][by] = 0;
		a[bx][by - 1] = 1; a[bx][by + 1] = 1; a[bx][by + 2] = 1;
	}
	else if (nblock == 32)
	{
		a[bx][by - 1] = 0; a[bx][by + 1] = 0; a[bx][by + 2] = 0;
		a[bx - 1][by] = 1; a[bx + 1][by] = 1; a[bx + 2][by] = 1;
	}
	else
	{
		if (nblock == 12)
		{
			s[0] = a[bx][by];     s[1] = a[bx + 1][by];     s[2] = a[bx + 2][by];
			s[3] = a[bx][by + 1]; s[4] = a[bx + 1][by + 1]; s[5] = a[bx + 2][by + 1];

			a[bx][by] = s[3];         a[bx + 1][by] = s[0];
			a[bx][by + 1] = s[4];     a[bx + 1][by + 1] = s[1];
			a[bx][by + 2] = s[5];     a[bx + 1][by + 2] = s[2];
			a[bx + 2][by] = 0; a[bx + 2][by + 1] = 0;
		}
		else
		{
			s[0] = a[bx + 1][by]; s[1] = a[bx + 1][by + 1]; s[2] = a[bx + 1][by + 2];
			s[3] = a[bx][by];     s[4] = a[bx][by + 1];     s[5] = a[bx][by + 2];

			a[bx][by] = s[5];     a[bx + 1][by] = s[4];     a[bx + 2][by] = s[3];
			a[bx][by + 1] = s[2]; a[bx + 1][by + 1] = s[1]; a[bx + 2][by + 1] = s[0];
			a[bx][by + 2] = 0; a[bx + 1][by + 2] = 0;
		}
	}
}


//随机产生方块
void create_block()
{
	nblock = rand() % 6;
	int x = nW / 2;
	bx = x; by = 0;
	switch (nblock)
	{
	case 0:
	{
		a[x][0] = 1; a[x][1] = 1; a[x + 1][0] = 1; a[x + 1][1] = 1;
		break;
	}
	case 1:
	{
		a[x][0] = 1; a[x + 1][1] = 1; a[x + 1][0] = 1; a[x + 2][1] = 1;
		break;
	}
	case 2:
	{
		a[x + 1][0] = 1; a[x + 2][0] = 1; a[x][1] = 1; a[x + 1][1] = 1;
		break;
	}
	case 3:
	{
		by++;
		a[x][0] = 1; a[x][1] = 1; a[x][2] = 1; a[x][3] = 1;
		break;
	}
	case 4:
	{
		a[x + 1][0] = 1; a[x][1] = 1; a[x + 1][1] = 1; a[x + 2][1] = 1;
		break;
	}
	case 5:
	{
		a[x][0] = 1; a[x + 1][0] = 1; a[x + 2][1] = 1; a[x + 2][0] = 1;
		break;
	}
	case 6:
	{
		a[x][0] = 1; a[x + 1][0] = 1; a[x][1] = 1; a[x + 2][0] = 1;
		break;
	}
	default:
		return;

	}
}

//停
void all2()
{
	for (int i = 0; i < nW; i++)
	{
		for (int j = 0; j < nH; j++)
		{
			if (a[i][j] == 1)
			{
				a[i][j] = 2;
			}
		}
	}
}

//碰撞检测
bool impact()
{
	for (int i = 0; i < nW; i++)
	{
		for (int j = 0; j < nH; j++)
		{
			if (a[i][j] == 1 && a[i][j + 1] == 2)
			{
				all2();
				return true;
			}
		}
	}
	return false;
}
bool impact_l()
{
	for (int k = 0; k < nH; k++)
	{
		if (a[0][k] == 1)
		{
			return true;
		}
	}
	for (int i = 1; i < nW; i++)
	{
		for (int j = 0; j < nH; j++)
		{
			if (a[i][j] == 1 && a[i - 1][j] == 2)
			{
				return true;
			}
		}
	}
	return false;
}
bool impact_r()
{
	for (int k = 0; k < nH; k++)
	{
		if (a[nW - 1][k] == 1)
		{
			return true;
		}
	}
	for (int i = 0; i < nW - 1; i++)
	{
		for (int j = 0; j < nH; j++)
		{
			if (a[i][j] == 1 && a[i + 1][j] == 2)
			{
				return true;
			}
		}
	}
	return false;
}


bool s1()
{
	
	if (a[bx][by + 2] == 0 && a[bx + 1][by + 2] == 0)
	{
		nblock = 12;
		return false;
	}
	return true;
}
bool s2()
{
	if (bx >= nW - 2)
	{
		return true;
	}
	
	if (a[bx + 2][by] == 0 && a[bx + 2][by + 1] == 0)
	{
		nblock = 1;
		return false;
	}
	return true;
}
bool impact_s()
{
	
	switch (nblock)
	{
	case 0:
	{
		return true;
	}
	case 1:
	{
		return s1();
	}
	case 12:
	{
		return s2();
	}
	case 2:
	{
		return s1();
	}
	case 3:
	{
		if (bx >= 1 && bx <= nW - 3)
		{
			
			if (a[bx - 1][by] == 0 && a[bx + 1][by] == 0 && a[bx + 2][by] == 0)
			{
				nblock = 32;
				return false;
			}
		}
		return true;
	}
	case 32:
	{
		if (by >= 1 && by <= nH - 3)
		{
			if (a[bx][by - 1] == 0 && a[bx][by + 1] == 0 && a[bx][by + 2] == 0)
			{
				nblock = 3;
				return false;
			}
		}
		return true;
	}
	case 4:
	{
		return s1();
	}
	case 5:
	{
		return s1();
	}
	case 6:
	{
		return s1();
	}
	default:
		break;
	}
	return false;
}



//底部检测
bool islow()
{
	for (int i = 0; i < nW; i++)
	{
		if (a[i][nH - 1] == 1)
		{
			all2();
			return true;
		}
	}
	return false;
}

//is full ?
bool isfull()
{
	int sum = 0;
	for (int i = nH - 1; i >= 1; i--)
	{
		sum = 0;
		for (int j = 0; j <= nW; j++)
		{
			sum += a[j][i];
		}
		if (sum == nW * 2)
		{
			score++;
			
			for (int k = i; k >= 1; k--)
			{
				for (int l = 0; l <= nW; l++)
				{
					a[l][k] = a[l][k - 1];
				}
			}
			isfull();
			return false;//返回第几排满了
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////

//显示方块
void paintblock(HDC gdc)
{
	Rectangle(gdc, 0, 0, main_W, main_H);//方块
	for (int i = 0; i < nW; i++)
	{
		for (int j = 0; j < nH; j++)
		{
			if (a[i][j] == 1 || a[i][j] == 2)
			{
				Rectangle(gdc, i * 20, j * 20, i * 20 + 20, j * 20 + 20);
				
			}
		}
	}
}



void paint(HDC gdc)
{
	int red = 85;
	int gre = 85;
	int blu = 85;

	HANDLE hNBrush = CreateSolidBrush(GetNearestColor(gdc, RGB(red, gre, blu)));
	HANDLE hbrOld = SelectBrush(gdc, hNBrush);

	for (int i = 0; i < nW; i++)
	{
		for (int j = 0; j < nH; j++)
		{
			if (a[i][j] == 2)
			{
				Rectangle(gdc, i * 20, j * 20, i * 20 + 20, j * 20 + 20);
			}
		}
	}

	DeleteBrush(SelectBrush(gdc, hbrOld));
}

//定时器生成
void onTimer(HWND hwnd)
{
	SetTimer(hwnd, DEFTIMER1, 500, NULL);
}
//定时器消除
void killTime(HWND hwnd)
{
	KillTimer(hwnd, DEFTIMER1);
}

//定时器响应
void ontime(HWND h)
{
	HDC gdc = GetDC(h);
	
	OnPrint(gdc);
	//paint(gdc);//染色
	if (isfull() == true)
	{
		
		if (islow() == true || impact() == true)
		{
			isfull();
			create_block();
		}
		else
		{
			block_down();
		}
	}
	

	ReleaseDC(h, gdc);
}

//响应
void OnPrint(HDC hdc)
{
	LPTSTR szBuffer = new TCHAR[15];//定义并申请输入缓冲区空间


	HDC ncDC;//设备环境句柄  设备环境（Device Context，简称 DC）
	ncDC = CreateCompatibleDC(hdc);//内存DC和窗口DC兼容
	HBITMAP HMenDC = CreateCompatibleBitmap(hdc, main_W, main_H);//创建一张纸
	SelectObject(ncDC, HMenDC);//位图给内存DC
	
	wsprintf(szBuffer, "分数: %d ", score);//拼接
	TextOut(hdc, main_W, 20, szBuffer, strlen("szBuffer"));
	paintblock(ncDC);

	BitBlt(hdc, 0, 0, main_W, main_H, ncDC, 0, 0, SRCCOPY);
	DeleteObject(HMenDC);
	DeleteDC(ncDC);
}




