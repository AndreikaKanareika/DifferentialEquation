#pragma once

#include <windows.h> 
#include <iostream>
#include <vector>
#include <string>
#include "Point.h"
#include "Macros.h"
#include "Settings.h"
#include "TextBoxAndComboBoxFunctions.h"
#include "ReversePolishNotation.h"
#include "AsmMethods.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


Point *InitPointsArray(string functionStr, double xStart, double yStart, double step, int countPoints, int method);
void GetClientSize(RECT rect, int& width, int &height, int panelElementsHeight, int marginLeft, int marginRight, int marginTop, int marginBottom);

void DrawCoordinates(HDC hDC, HPEN hPen, int countCoordLines, int coordLinesLength, int coordStrLength,
	int bottomHorizontalMarginText, int leftHorizontalMarginText, int bottomVerticalMarginText, int leftVercticalMarginText,
	TCHAR *coordStr, int marginLeft, int marginTop, int panelElementsHeight, int width, int height, double xStart, double xEnd, double yMax, double yMin);

void DrawBorder(HDC hDC, int marginLeft, int marginTop, int panelElementsHeigh, int width, int height);

void DrawXYAxis(HDC hDC, int marginLeft, int marginTop, int panelElementsHeight, int width, int height, double xStart, double xEnd, double yMax, double yMin);



void FindYMaxMin(Point arr[], int countPoints, double &yMax, double &yMin);

void ClearStr(TCHAR *str, int length);

double FPolishNotation(string str, double x, double y);
double FCpp(double x);
double GetDelta(Point arr[], int countPoints);
