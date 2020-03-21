#include "common.h"

LRESULT CALLBACK SqureProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//init window class
	WNDCLASSEX wc;
	//return value
	int nRe;
	//window handle
	HWND hWnd;
	MSG msg;

	//assignment
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = SqureProc;
	wc.lpszClassName = "RSqure";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	//Register Window class
	if (0 == RegisterClassEx(&wc))
	{
		nRe = GetLastError();
		return 0;
	}
	
	//Create Window
	hWnd = CreateWindowEx(0, "RSqure", "Tetris", WS_OVERLAPPEDWINDOW^WS_THICKFRAME, 100, 30, 500, 600 + 45, NULL, NULL, hInstance, NULL);
	if (0 == hWnd)
	{
		//fail
		nRe = GetLastError();
		return 0;
	}

	//Show Window
	ShowWindow(hWnd, nShowCmd);

	//Message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK SqureProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT pst;

	switch (uMsg)
	{
	case WM_CREATE:
		OnCreate();
		break;

	case WM_TIMER:
		OnTimer(hWnd);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &pst);
		OnPaint(hdc);
		EndPaint(hWnd, &pst);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			OnReturn(hWnd);
			break;
		case VK_UP:
			OnChange(hWnd);
			break;
		case VK_DOWN:
			OnDown(hWnd);
			break;
		case VK_LEFT:
			OnLeft(hWnd);
			break;
		case VK_RIGHT:
			OnRight(hWnd);
			break;
		default:
			break;
		}
		break;


	case WM_DESTROY:
		KillTimer(hWnd, DEFAULT_TIMER);
		PostQuitMessage(0);
		break;

	default:
		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
