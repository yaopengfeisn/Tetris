#ifndef common
#define common

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <time.h>

#define DEFAULT_TIMER 1

//winEvent
void OnCreate();
void OnTimer(HWND hWnd);
void OnPaint(HDC hdc);

//paintSquare
int CreatRandomSquare();
void CopySquareToBackground();
void FixBottomSquare();
void PaintSqure(HDC hdc);
void PaintBottomSqure(HDC hdc);

//keyDown
void OnReturn(HWND hWnd);
void OnChange(HWND hWnd);//VK_UP
void OnDown(HWND hWnd);
void OnLeft(HWND hWnd);
void OnRight(HWND hWnd);

//moveSquare
void SquareDown();
BOOL ReachBottom();
BOOL ReachSquareOnBottom();
void SquareLeft();
BOOL ReachLeftBorder();
BOOL ReachSquareOnLeft();
void SquareRight();
BOOL ReachRightBorder();
BOOL ReachSquareOnRight();

//rotateSquare
void RotateSquare();
BOOL SquareRotatable();
void RotateBar();

//score
void EliminateOneLine();
void ShowScore(HDC hdc);

//end
BOOL IsGameOver();

#endif // !common
