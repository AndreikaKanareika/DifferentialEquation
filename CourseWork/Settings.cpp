#include "Settings.h"

using namespace std;


void InitSettings(Settings &settings)
{
	settings.marginLeft = 50;
	settings.marginTop = 0;
	settings.marginRight = 50;
	settings.marginBottom = 50;

	settings.bottomHorizontalMarginText = -10;
	settings.leftHorizontalMarginText = -30;
	settings.bottomVerticalMarginText = 0;
	settings.leftVerticalMarginText = -10;

	settings.xStart = -1;
	settings.xEnd = 2;
	settings.step = 0.1;

	settings.countCoordLines = 9;
	settings.coordLinesLength = 10;

	settings.color = RGB(255, 0, 0);
}

bool CopySettings(Settings &settings, Settings *set)
{
	bool isEqualMainSettings = true;

	settings.marginLeft = set->marginLeft;
	settings.marginTop = set->marginTop;
	settings.marginRight = set->marginRight;
	settings.marginBottom = set->marginBottom;

	settings.bottomHorizontalMarginText = set->bottomHorizontalMarginText;
	settings.leftHorizontalMarginText = set->leftHorizontalMarginText;
	settings.bottomVerticalMarginText = set->bottomVerticalMarginText;
	settings.leftVerticalMarginText = set->leftVerticalMarginText;


	if (settings.xStart != set->xStart ||
		settings.xEnd != set->xEnd ||
		settings.step != set->step)
		isEqualMainSettings = false;

	settings.xStart = set->xStart;
	settings.xEnd = set->xEnd;
	settings.step = set->step;

	settings.countCoordLines = set->countCoordLines;
	settings.coordLinesLength = set->coordLinesLength;

	settings.color = set->color;

	return isEqualMainSettings;
}
