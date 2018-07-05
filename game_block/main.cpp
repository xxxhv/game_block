#include "x.h"


#include <windows.h> 
#include <tchar.h>  

//�������ڹ���ԭ��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);




//WINAPI�� ����Լ����ζ��ջ���������ɱ����ú������ ����ǰʵ���ľ�� 
//Ӧ�ó����ϵ�һ��ʵ����� Ӧ�ó��������� �����ʾ����
int WINAPI WinMain(HINSTANCE hThis, HINSTANCE hPrev, LPSTR szCmdLine, int iCmdShow)
{
	//��ʵ��ĳЩ���� UNREFERENCED_PARAMETER��
	UNREFERENCED_PARAMETER(hPrev);
	//ʵ���� WNDCLASSEX ���ڽṹ
	WNDCLASSEX wcx = { 0 };
	wcx.cbSize = sizeof(wcx);                           //���ڽṹ��С
	wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);     //������ˢ���
	wcx.style = CS_HREDRAW | CS_VREDRAW;                //�������仯�ػ�
	wcx.lpfnWndProc = WndProc;                          //ָ�򴰿ڹ���ָ��
	wcx.cbClsExtra = 0;                                 //ʵ�������� ��   ���������ֽ�
	wcx.cbWndExtra = 0;                                 //ʵ�������� ʵ�� ���������ֽ�
	wcx.hInstance = hThis;                              //�������ڹ��̵�ʵ�����
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);        //ͼ����
	wcx.hIconSm = (HICON)LoadImage(hThis, MAKEINTRESOURCE(5), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CXSMICON), LR_DEFAULTCOLOR);
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);          //�����
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = TEXT("MainWclass");
	if (!RegisterClassEx(&wcx))
	{
		return -1;
	}
	HWND hwnd = CreateWindow(wcx.lpszClassName, TEXT("hello"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, (HWND)NULL, (HMENU)NULL, hThis, (LPVOID)NULL);
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

	PAINTSTRUCT ps;//�ýṹ�������ĳӦ�ó���������������ӵ�еĴ��ڿͻ�������Ҫ����Ϣ


	switch (uMsg)
	{
	case WM_CREATE:
	{
		break;
	}

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_RETURN:
		{
			break;
		}
		case VK_F1:
		{
			MessageBox(NULL, "0.0", "F1", MB_OK);
			break;
		}
		case VK_F2:
		{
			MessageBox(NULL, "0.0", "F2", MB_OK);
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
		HDC gdc;
		gdc = BeginPaint(hWnd, &ps);//����DC
		HDC ncDC;//�豸�������  �豸������Device Context����� DC��
		ncDC = CreateCompatibleDC(gdc);//�ڴ�DC�ʹ���DC����
		HBITMAP HMenDC = CreateCompatibleBitmap(gdc, 200, 200);//����һ��ֽ
		SelectObject(ncDC, HMenDC);//λͼ���ڴ�DC

		Rectangle(gdc, 300, 300, 400, 400);//����
		TextOut(gdc, 200, 200, "hello", strlen("hello"));//��

		Rectangle(ncDC, 0, 0, 200, 200);//����
		TextOut(ncDC, 20, 20, "ncdc", strlen("ncdc"));//��ncDC

		BitBlt(gdc, 0, 0, 200, 200, ncDC, 0, 0, SRCCOPY);
		DeleteObject(HMenDC);
		DeleteDC(ncDC);


		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY:
		
		PostQuitMessage(0);

		return 0;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);//����Ҫ����Ϣת��windows
	}
	return 0;
}

