#pragma once

#include <windows.h>

struct Settings
{
	int marginLeft;
	int marginRight;
	int marginTop;
	int marginBottom;

	int leftHorizontalMarginText;
	int bottomHorizontalMarginText;
	int leftVerticalMarginText;
	int bottomVerticalMarginText;

	int countCoordLines;
	int coordLinesLength;

	double xStart;
	double xEnd;
	double step;

	int color;
};

void InitSettings(Settings &settings);
bool CopySettings(Settings &settings, Settings *set);

