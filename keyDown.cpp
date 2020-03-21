#include "common.h"

extern int g_nLine;
extern int g_nCol;
extern int g_nSquare;

void OnReturn(HWND hWnd)
{
	SetTimer(hWnd, DEFAULT_TIMER, 500, NULL);
}

void OnChange(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	switch (g_nSquare)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		if (TRUE == SquareRotatable())
		{
			RotateSquare();
		}
		else
		{
			return;
		}
		break;
	case 5:
		//No action
		return;
	case 6:
		RotateBar();
		break;
	}
	OnPaint(hdc);
	ReleaseDC(hWnd, hdc);
}


void OnDown(HWND hWnd)
{
	OnTimer(hWnd);
}

void OnLeft(HWND hWnd)
{
	if (FALSE == ReachLeftBorder() && FALSE == ReachSquareOnLeft())
	{
		HDC hDc = GetDC(hWnd);
		SquareLeft();
		g_nCol--;
		OnPaint(hDc);
		ReleaseDC(hWnd, hDc);
	}
}

void OnRight(HWND hWnd)
{
	if (FALSE == ReachRightBorder() && FALSE == ReachSquareOnRight())
	{
		HDC hdc = GetDC(hWnd);
		SquareRight();
		g_nCol++;
		OnPaint(hdc);
		ReleaseDC(hWnd, hdc);
	}
}
