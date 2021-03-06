#include "x.h"



//申明窗口过程原型
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);




//WINAPI宏 调用约定意味着栈的清理工作由被调用函数完成 程序当前实例的句柄 
//应用程序上的一个实例句柄 应用程序命令行 如何显示窗口
int WINAPI WinMain(HINSTANCE hThis, HINSTANCE hPrev, LPSTR szCmdLine, int iCmdShow)
{
	//不实用某些参数 UNREFERENCED_PARAMETER宏
	UNREFERENCED_PARAMETER(hPrev);
	//实例化 WNDCLASSEX 窗口结构
	WNDCLASSEX wcx = { 0 };
	wcx.cbSize = sizeof(wcx);                           //窗口结构大小
	wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);     //背景画刷句柄
	wcx.style = CS_HREDRAW | CS_VREDRAW;                //长宽发生变化重绘
	wcx.lpfnWndProc = WndProc;                          //指向窗口过程指针
	wcx.cbClsExtra = 0;                                 //实例化窗口 类   后分配额外字节
	wcx.cbWndExtra = 0;                                 //实例化窗口 实例 后分配额外字节
	wcx.hInstance = hThis;                              //包含窗口过程的实例句柄
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);        //图标句柄
	wcx.hIconSm = (HICON)LoadImage(hThis, MAKEINTRESOURCE(5), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CXSMICON), LR_DEFAULTCOLOR);
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);          //光标句柄
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = TEXT("MainWclass");
	if (!RegisterClassEx(&wcx))
	{
		return -1;
	}
	HWND hwnd = CreateWindow(wcx.lpszClassName, TEXT("hello"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 600, (HWND)NULL, (HMENU)NULL, hThis, (LPVOID)NULL);
	if (!hwnd)
	{
		return 111;
	}
	UpdateWindow(hwnd);
	ShowWindow(hwnd, iCmdShow);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	DestroyWindow(hwnd);
	UnregisterClass(wcx.lpszClassName, hThis);

	return (int)msg.wParam;
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;


	switch (uMsg)
	{
	case WM_CREATE:
	{
		onTimer(hWnd);
		break;
	}
	case WM_TIMER:
	{
		//由定时器创建的消息
		ontime(hWnd);
		
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_RETURN:
		{
			create_block();
			break;
		}
		case VK_LEFT:
		{
			if (impact_l() == false)
			{
				block_left();
			}
			OnPrint(GetDC(hWnd));
			break;
		}
		case VK_RIGHT:
		{
			if (impact_r() == false)
			{
				block_right();
			}
			OnPrint(GetDC(hWnd));
			break;
		}
		case VK_DOWN:
		{

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
			
			OnPrint(GetDC(hWnd));
			break;
		}
		case VK_UP:
		{
			if (impact_s() == false)
			{
				block_spin();
				OnPrint(GetDC(hWnd));
			}
			break;
		}
		case VK_F1:
		{

			break;
		}
		case VK_F2:
		{
			
			break;
		}
		default:
			break;
		}
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);//窗口DC
		OnPrint(hdc);
		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY:
		killTime(hWnd);
		PostQuitMessage(0);

		return 0;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);//不需要的消息转给windows
	}
	return 0;
}

