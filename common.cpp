#include "common.h"
#include <queue>

//background array
char g_arrBackgroud[20][10] = { 0 };
//square array
char g_arrSquare[2][4] = { 0 };
//square type
int g_nSquare = -1;
//square posiont x, y
int g_nLine = -1;
int g_nCol = -1;
//score
int g_nScore = 0;

std::queue<SquareInfo> qSquareType;


//call from WM_CREATE
void OnCreate()
{
	SquareInfo si;

	srand((unsigned int)time(NULL));

	si = CreatRandomSquare();
	qSquareType.push(si);
	CopySquareToBackground();

	//Create next square, for tips
	si = CreatRandomSquare();
	qSquareType.push(si);

	//get current square type
	g_nSquare = qSquareType.front().SquareType;
	g_nLine = qSquareType.front().PositionX;
	g_nCol = qSquareType.front().PositionY;
}


//call from WM_TIMER
void OnTimer(HWND hWnd)
{
	HDC hDc = GetDC(hWnd);

	if (FALSE == ReachBottom() && FALSE == ReachSquareOnBottom())
	{
		SquareDown();
		g_nLine++;
	}
	else
	{
		FixBottomSquare();
		EliminateOneLine();
		if (TRUE == IsGameOver())
		{
			int nRe = MessageBox(NULL, "Game Over, play again?", "", MB_YESNO);
			if (IDYES == nRe)
			{
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						g_arrBackgroud[i][j] = { 0 };
					}
				}
				OnCreate();
				g_nScore = 0;
				
			}
			else if(IDNO == nRe)
			{
				KillTimer(hWnd, DEFAULT_TIMER);
				PostQuitMessage(0);
			}
			return;
		}

		CopySquareToBackground();

		qSquareType.pop();
		SquareInfo si = CreatRandomSquare();
		qSquareType.push(si);
		
		g_nSquare = qSquareType.front().SquareType;
		g_nLine = qSquareType.front().PositionX;
		g_nCol = qSquareType.front().PositionY;

	}

	OnPaint(hDc);
	//kernel object, always release manually
	ReleaseDC(hWnd, hDc);
}


//call from WM_PAINT & OnTimer
void OnPaint(HDC hdc)
{
	//Create compatible DC, push to front directly
	HDC hBgDc = CreateCompatibleDC(hdc);
	HBITMAP hBgBitmap = CreateCompatibleBitmap(hdc, 500, 600);
	SelectObject(hBgDc, hBgBitmap);

	//Paint on compatible DC
	PaintBottomSqure(hBgDc);
	PaintSqure(hBgDc);
	ShowScore(hBgDc);
	PaintSquareToTips(hBgDc);
	//bring to front
	BitBlt(hdc, 0, 0, 500, 600, hBgDc, 0, 0, SRCCOPY);
	
	//release handle
	DeleteObject(hBgBitmap);
	DeleteDC(hBgDc);
}


SquareInfo CreatRandomSquare()
{
	int n = rand() % 7;
	SquareInfo si;

	switch (n)
	{
	case 0:
		g_arrSquare[0][0] = 1, g_arrSquare[0][1] = 1, g_arrSquare[0][2] = 0, g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 0, g_arrSquare[1][1] = 1, g_arrSquare[1][2] = 1, g_arrSquare[1][3] = 0;
		si.PositionX = 0;
		si.PositionY = 3;
		//g_nLine = 0;
		//g_nCol = 3;
		break;
	case 1:
		g_arrSquare[0][0] = 0, g_arrSquare[0][1] = 1, g_arrSquare[0][2] = 1, g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 1, g_arrSquare[1][1] = 1, g_arrSquare[1][2] = 0, g_arrSquare[1][3] = 0;
		si.PositionX = 0;
		si.PositionY = 3;
		//g_nLine = 0;
		//g_nCol = 3;
		break;
	case 2:
		g_arrSquare[0][0] = 1, g_arrSquare[0][1] = 1, g_arrSquare[0][2] = 1, g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 0, g_arrSquare[1][1] = 0, g_arrSquare[1][2] = 1, g_arrSquare[1][3] = 0;
		si.PositionX = 0;
		si.PositionY = 3;
		//g_nLine = 0;
		//g_nCol = 3;
		break;
	case 3:
		g_arrSquare[0][0] = 1, g_arrSquare[0][1] = 1, g_arrSquare[0][2] = 1, g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 1, g_arrSquare[1][1] = 0, g_arrSquare[1][2] = 0, g_arrSquare[1][3] = 0;
		si.PositionX = 0;
		si.PositionY = 3;
		//g_nLine = 0;
		//g_nCol = 3;
		break;

	case 4:
		g_arrSquare[0][0] = 0, g_arrSquare[0][1] = 1, g_arrSquare[0][2] = 0, g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 1, g_arrSquare[1][1] = 1, g_arrSquare[1][2] = 1, g_arrSquare[1][3] = 0;
		si.PositionX = 0;
		si.PositionY = 3;
		//g_nLine = 0;
		//g_nCol = 3;
		break;

	case 5:
		g_arrSquare[0][0] = 0, g_arrSquare[0][1] = 1, g_arrSquare[0][2] = 1, g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 0, g_arrSquare[1][1] = 1, g_arrSquare[1][2] = 1, g_arrSquare[1][3] = 0;
		break;
	case 6:
		g_arrSquare[0][0] = 1, g_arrSquare[0][1] = 1, g_arrSquare[0][2] = 1, g_arrSquare[0][3] = 1;
		g_arrSquare[1][0] = 0, g_arrSquare[1][1] = 0, g_arrSquare[1][2] = 0, g_arrSquare[1][3] = 0;
		si.PositionX = 0;
		si.PositionY = 4;
		//g_nLine = 0;
		//g_nCol = 4;
		break;

	default:
		break;
	}
	//g_nSquare = n;
	si.SquareType = n;
	return si;
}


void CopySquareToBackground()
{
	int i = 0, j = 0;
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 4; j++)
		{
			g_arrBackgroud[i][j + 3] = g_arrSquare[i][j];
		}
	}
}

void PaintSquareToTips(HDC hdc)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (1 == g_arrSquare[i][j])
			{
				Rectangle(hdc, 330 + j*30, 240+i*30, 360+j*30, 270+i*30);
			}
			
		}
	}

}


void FixBottomSquare()
{
	int i = 0, j = 0;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (1 == g_arrBackgroud[i][j])
			{
				g_arrBackgroud[i][j] = 2;
			}
		}
	}
}


//show bottom and running square in different color
void PaintBottomSqure(HDC hdc)
{
	//draw backgroud
	Rectangle(hdc, 0, 0, 300, 600);

	//show bottom square in green
	HBRUSH hOldBrush;
	HBRUSH hNewBrush = CreateSolidBrush(RGB(0, 64, 0));
	hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);
	//draw bottom square
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (2 == g_arrBackgroud[i][j])
			{
				Rectangle(hdc, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
		}
	}
	hNewBrush = (HBRUSH)SelectObject(hdc, hOldBrush);
	DeleteObject(hNewBrush);
}


void PaintSqure(HDC hdc)
{
	//draw squre
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (1 == g_arrBackgroud[i][j])
			{
				Rectangle(hdc, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
		}
	}
}


void SquareRight()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 9; j >= 0; j--)
		{
			if (1 == g_arrBackgroud[i][j])
			{
				g_arrBackgroud[i][j + 1] = 1;
				g_arrBackgroud[i][j] = 0;
			}
		}
	}
}

BOOL ReachRightBorder()
{
	for (int i = 0; i < 20; i++)
	{
		if (1 == g_arrBackgroud[i][9])
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL ReachSquareOnRight()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 9; j >= 0; j--)
		{
			if (1 == g_arrBackgroud[i][j])
			{
				if (2 == g_arrBackgroud[i][j + 1])
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

void SquareDown()
{
	int i = 0, j = 0;
	for (i = 19; i >= 0; i--)
	{
		for (j = 0; j < 10; j++)
		{
			if (1 == g_arrBackgroud[i][j])
			{
				g_arrBackgroud[i + 1][j] = 1;
				g_arrBackgroud[i][j] = 0;
			}
		}
	}
}


BOOL ReachBottom()
{
	for (int i = 0; i < 10; i++)
	{
		if (1 == g_arrBackgroud[19][i])
		{
			return TRUE;
		}
	}
	//Square can still move down
	return FALSE;
}


BOOL ReachSquareOnBottom()
{
	int i = 0, j = 0;
	for (i = 19; i >= 0; i--)
	{
		for (j = 0; j < 10; j++)
		{
			if (1 == g_arrBackgroud[i][j])
			{
				if (2 == g_arrBackgroud[i + 1][j])
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

void SquareLeft()
{
	int i = 0, j = 0;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (1 == g_arrBackgroud[i][j])
			{
				g_arrBackgroud[i][j - 1] = 1;
				g_arrBackgroud[i][j] = 0;
			}
		}
	}
}

BOOL ReachLeftBorder()
{
	for (int i = 0; i < 20; i++)
	{
		if (1 == g_arrBackgroud[i][0])
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL ReachSquareOnLeft()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (1 == g_arrBackgroud[i][j])
			{
				if (2 == g_arrBackgroud[i][j - 1])
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}


void RotateSquare()
{
	char arrSquare[3][3] = { 0 };

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arrSquare[i][j] = g_arrBackgroud[g_nLine + i][g_nCol + j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			g_arrBackgroud[g_nLine + i][g_nCol + j] = arrSquare[2 - j][i];
		}
	}
}

//cope square borders and neighbours
BOOL SquareRotatable()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (2 == g_arrBackgroud[g_nLine + i][g_nCol + j])
			{
				return FALSE;
			}
		}
	}
	if (g_nCol < 0)
	{
		g_nCol = 0;
	}
	if (g_nCol + 2 > 9)
	{
		g_nCol = 7;
	}
	if (g_nLine + 2 > 19)
	{
		g_nLine = 17;
	}
	return TRUE;
}

//refill square array directly
void RotateBar()
{
	if (1 == g_arrBackgroud[g_nLine][g_nCol - 1])
	{
		//rotation not allowed in if conditon
		if (2 == g_arrBackgroud[g_nLine + 2][g_nCol] || 2 == g_arrBackgroud[g_nLine + 1][g_nCol])
		{
			return;
		}
		//clear array
		g_arrBackgroud[g_nLine][g_nCol - 1] = 0;
		g_arrBackgroud[g_nLine][g_nCol + 1] = 0;
		g_arrBackgroud[g_nLine][g_nCol + 2] = 0;

		//refill
		g_arrBackgroud[g_nLine - 1][g_nCol] = 1;
		g_arrBackgroud[g_nLine + 1][g_nCol] = 1;
		g_arrBackgroud[g_nLine + 2][g_nCol] = 1;
	}
	else
	{
		//rotation not allowed in if conditon
		if (g_nCol == 0 || g_nCol == 8 || g_nCol == 9)
		{
			return;
		}
		else if (2 == g_arrBackgroud[g_nLine][g_nCol - 1] || 2 == g_arrBackgroud[g_nLine][g_nCol + 2])
		{
			return;
		}
		g_arrBackgroud[g_nLine - 1][g_nCol] = 0;
		g_arrBackgroud[g_nLine + 1][g_nCol] = 0;
		g_arrBackgroud[g_nLine + 2][g_nCol] = 0;

		g_arrBackgroud[g_nLine][g_nCol - 1] = 1;
		g_arrBackgroud[g_nLine][g_nCol + 1] = 1;
		g_arrBackgroud[g_nLine][g_nCol + 2] = 1;

	}
}


void EliminateOneLine()
{
	//sum marker of line array, 20 means full of square, which should be eliminated 
	int nSum;
	for (int i = 19; i >= 0; i--)
	{
		nSum = 0;
		for (int j = 0; j < 10; j++)
		{
			nSum += g_arrBackgroud[i][j];
		}
		if (20 == nSum)
		{
			for (int n = i; n >= 0; n--)
			{
				for (int m = 0; m < 10; m++)
				{
					g_arrBackgroud[n][m] = g_arrBackgroud[n-1][m];
				}
			}
			i += 1;
			g_nScore += 1;
		}

	}
}

void ShowScore(HDC hdc)
{
	char strScore[10] = { 0 };
	Rectangle(hdc, 300, 0, 500, 600);
	_itoa(g_nScore, strScore, 10);
	TextOut(hdc, 375, 20, "Score", strlen("Score"));
	TextOut(hdc, 390, 40, strScore, strlen(strScore));
}

BOOL IsGameOver()
{
	for (int i = 0; i < 10; i++)
	{
		if (2 == g_arrBackgroud[0][i])
		{
			return TRUE;
		}
	}
	return FALSE;
}
