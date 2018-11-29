#include "MainGraphicWindow.h"

using namespace std;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT rect;
	static HWND hSettingWnd;
	static HWND hDY, hYStart;

	static bool initSet = false;
	static Settings settings;

	static string functionStr = "(2*(cos(x))^2*ctg(x)+y)/ctg(x)";
	
	if (!initSet)
	{
		InitSettings(settings);

		initSet = true;
	}

	static double y;
	static double yStart = 0;

	static double yMin;
	static double yMax;
	
	static int method = METHOD_EILER;

	static int width;
	static int height;

	const int minWidth = 470;
	const int minHeight = 430;

	const int coordStrLength = 10;
	static TCHAR coordStr[coordStrLength];

	static int countPoints = (settings.xEnd - settings.xStart) / settings.step;
	double lineLength = (double)width / (countPoints-1);
	static Point *points;

	const int panelElementsHeight = 200;

	GetClientRect(hWnd, &rect);

	static HWND hColorComboBox;

	switch (message)
	{
	case WM_CREATE:
		CreateWindowEx(NULL, "static", "y'=", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 20, 25, 20, hWnd, (HMENU)0, NULL, NULL);
		hDY = CreateWindowEx(NULL, "edit", functionStr.c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 20, 400, 20, hWnd, (HMENU)ID_DY, NULL, NULL);
		CreateWindowEx(NULL, "static", "y0=", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 50, 30, 20, hWnd, (HMENU)0, NULL, NULL);
		hYStart = CreateWindowEx(NULL, "edit", "0", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 50, 45, 20, hWnd, (HMENU)0, NULL, NULL);
	
	
		CreateWindowEx(NULL, "button", "Мод. метод Эйлера", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_BORDER, 10, 80, 160, 20, hWnd, (HMENU)ID_RADIOBTN_EILER, NULL, NULL);
		CreateWindowEx(NULL, "button", "Метод Адамса", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_BORDER, 10, 105, 160, 20, hWnd, (HMENU)ID_RADIOBTN_ADAMS, NULL, NULL);


		CreateWindowEx(NULL, "button", "Построить график", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 130, 160, 30, hWnd, (HMENU)ID_BTN_DRAWGRAPHIC, NULL, NULL);
	
		CreateWindowEx(NULL, "static", " ASM", WS_VISIBLE | WS_CHILD | WS_BORDER, 365, 50, 40, 20, hWnd, (HMENU)0, NULL, NULL);
		CreateWindowEx(NULL, "button", "Мод. метод Эйлера", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 80, 150, 20, hWnd, (HMENU)ID_ASM_EILER, NULL, NULL);
		CreateWindowEx(NULL, "button", "Метод Адамса", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 105, 150, 20, hWnd, (HMENU)ID_ASM_ADAMS, NULL, NULL);


		CreateWindowEx(NULL, "button", "SCILAB", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 130, 150, 30, hWnd, (HMENU)SCILAB, NULL, NULL);


		GetClientSize(rect, width, height, panelElementsHeight, settings.marginLeft, settings.marginRight, settings.marginTop, settings.marginBottom);
		

		try
		{
			yMax = yMin = yStart;
			points = InitPointsArray(functionStr, settings.xStart, yStart, settings.step, countPoints, method);
			FindYMaxMin(points, countPoints, yMax, yMin);
		}
		catch (overflow_error ex)
		{
			MessageBox(hWnd, ex.what(), "Error", NULL);
		}
		catch (invalid_argument ex)
		{
			MessageBox(hWnd, ex.what(), "Error", NULL);
		}
		
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_RADIOBTN_EILER:
			method = METHOD_EILER;
			break;
		case ID_RADIOBTN_ADAMS:
			method = METHOD_ADAMS;
			break;
		case ID_BTN_DRAWGRAPHIC:
			
			functionStr = GetStringFromTextBox(hDY);

			try
			{
				yStart = GetDoubleFromTextBox(hYStart);
					
				countPoints = (settings.xEnd - settings.xStart) / settings.step;;
				yMax = yMin = yStart;
				points = InitPointsArray(functionStr, settings.xStart, yStart, settings.step, countPoints, method);
				FindYMaxMin(points, countPoints, yMax, yMin);
			}
			catch (overflow_error ex)
			{
				points = NULL;
				MessageBox(hWnd, ex.what(), "Error", NULL);
			}
			catch (invalid_argument ex)
			{
				points = NULL;
				MessageBox(hWnd, ex.what(), "Error", NULL);
			}


			InvalidateRect(hWnd, &rect, true);
			break;
		case ID_ASM_EILER:
			
			try
			{				
				settings.xStart = -1;
				settings.xEnd = 2;
				settings.step = 0.1;
				yStart = 0;

				countPoints = (settings.xEnd - settings.xStart) / settings.step;
				yMax = yMin = yStart;
				points = Eiler(settings.xStart, settings.xEnd, settings.step, yStart, settings.xStart);
				FindYMaxMin(points, countPoints, yMax, yMin); 

				TCHAR msg[100];
				snprintf(msg, 100, "Погрешность модифицированного метода Эйлера равна %f", GetDelta(points, countPoints));
				MessageBox(hWnd, msg, "Погрешность мод.метода Эйлера", NULL);

			}
			catch (overflow_error ex)
			{
				MessageBox(hWnd, ex.what(), "Error", NULL);
			}
			catch (invalid_argument ex)
			{
				MessageBox(hWnd, ex.what(), "Error", NULL);
			}
			InvalidateRect(hWnd, &rect, true);
			
			break;
					   
		case ID_ASM_ADAMS:
			
			try
			{
				settings.xStart = -1;
				settings.xEnd = 2;
				settings.step = 0.1;
				yStart = 0;

				countPoints = (settings.xEnd - settings.xStart) / settings.step;
				yMax = yMin = yStart;
				points = Adams(settings.xStart, settings.xEnd, settings.step, yStart, settings.xStart);
				FindYMaxMin(points, countPoints, yMax, yMin);


				TCHAR msg[100];
				snprintf(msg, 100, "Погрешность метода Адамса равна %f", GetDelta(points, countPoints));
				MessageBox(hWnd, msg, "Погрешность метода Адамса", NULL);
			}
			catch (overflow_error ex)
			{
				MessageBox(hWnd, ex.what(), "Error", NULL);
			}
			catch (invalid_argument ex)
			{
				MessageBox(hWnd, ex.what(), "Error", NULL);
			}
			InvalidateRect(hWnd, &rect, true);
			break;			

		case SCILAB:
			
			STARTUPINFO st = { sizeof(STARTUPINFO) };
			PROCESS_INFORMATION pi;
			TCHAR str[100] = TEXT("I:\\Soft\\scilab-6.0.0\\bin\\WScilex -f myFunc.sce");
			CreateProcess(NULL, str, NULL, NULL, false, 0, NULL, NULL, &st, &pi);

			break;
		}

		break;
	case WM_LBUTTONDBLCLK:

		if (hSettingWnd == NULL) hSettingWnd = FindWindow("My2", "Settings");

		SendMessage(hSettingWnd, SETTING_SET_MSG, 0, (LPARAM)&settings);
		ShowWindow(hSettingWnd, SW_SHOW);
		break;

	case WM_SIZE:
		
		GetClientSize(rect, width, height, panelElementsHeight, settings.marginLeft, settings.marginRight, settings.marginTop, settings.marginBottom);
		break;

	case WM_GETMINMAXINFO:

		LPMINMAXINFO lpMinMaxInfo;
		lpMinMaxInfo = (LPMINMAXINFO)lParam;
		lpMinMaxInfo->ptMinTrackSize.x = minWidth;
		lpMinMaxInfo->ptMinTrackSize.y = minHeight;
		break;

	case WM_PAINT:
		
		HDC hDC;
		PAINTSTRUCT ps;
		HPEN hPen;

		int xCoord;
		int yCoord;

		hDC = BeginPaint(hWnd, &ps);

		if (points != NULL)
		{

			// Draw coordinates	
			hPen = CreatePen(0, 1, RGB(0, 0, 0));
			SelectObject(hDC, hPen);
			DrawCoordinates(
				hDC,
				hPen,
				settings.countCoordLines,
				settings.coordLinesLength,
				coordStrLength,
				settings.bottomHorizontalMarginText,
				settings.leftHorizontalMarginText,
				settings.bottomVerticalMarginText,
				settings.leftVerticalMarginText,
				coordStr, //
				settings.marginLeft,
				settings.marginTop,
				panelElementsHeight,
				width,
				height,
				settings.xStart,
				settings.xEnd,
				yMax, yMin);

			// Draw axis
			hPen = CreatePen(0, 3, RGB(0, 0, 0));
			SelectObject(hDC, hPen);
			DrawXYAxis(hDC, settings.marginLeft, settings.marginTop, panelElementsHeight, width, height, settings.xStart, settings.xEnd, yMax, yMin);

			// Draw graphic
			hPen = CreatePen(0, 2, settings.color);
			SelectObject(hDC, hPen);

			xCoord = settings.marginLeft;
			yCoord = height * (yMax - points[0].y) / (yMax - yMin) + settings.marginTop + panelElementsHeight;

			MoveToEx(hDC, xCoord, yCoord, NULL);

			for (int i = 0; i < countPoints; i++)
			{
				xCoord = i * lineLength + settings.marginLeft;
				yCoord = height * (yMax - points[i].y) / (yMax - yMin) + settings.marginTop + panelElementsHeight;

				LineTo(hDC, xCoord, yCoord);
			}

		}
		
		// Draw border
		hPen = CreatePen(0, 1, RGB(0, 0, 0));
		SelectObject(hDC, hPen);
		DrawBorder(hDC, settings.marginLeft, settings.marginTop, panelElementsHeight, width, height);
		
		EndPaint(hWnd, &ps);

		break;

	case GRAPHIC_SETTING_MSG:

		Settings* set;
		set = (Settings*)lParam;

		bool isEqualMainSettings;
		isEqualMainSettings = CopySettings(settings, set);

		if (!isEqualMainSettings)
		{
			if (settings.step > 0)
			{
				countPoints = (settings.xEnd - settings.xStart) / settings.step;
			}
			else
			{
				points = NULL;
				MessageBox(hWnd, "Шаг должен быть > 0", "Error", NULL);
				InvalidateRect(hWnd, &rect, true);
				break;
			}


			try
			{
				yMax = yMin = yStart;
				points = InitPointsArray(functionStr, settings.xStart, yStart, settings.step, countPoints, method);
				FindYMaxMin(points, countPoints, yMax, yMin);
			}
			catch (overflow_error ex)
			{
				points = NULL;
				MessageBox(hWnd, ex.what(), "Error", NULL);
			}
			catch (invalid_argument ex)
			{
				points = NULL;
				MessageBox(hWnd, ex.what(), "Error", NULL);
			}
		}


		GetClientSize(rect, width, height, panelElementsHeight, settings.marginLeft, settings.marginRight, settings.marginTop, settings.marginBottom);

		InvalidateRect(hWnd, &rect, true);
		break;

	case WM_DESTROY: PostQuitMessage(0); break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



Point *InitPointsArray(string functionStr, double xStart, double yStart, double step, int countPoints, int method) 
{
	Point *points = new Point[countPoints];

	double x = xStart;
	double y = yStart;
		
	points[0] = Point{ x,y };
	x += step;
	
	
	switch (method)
	{
	case METHOD_EILER:
		for (int i = 1; i < countPoints; i++)
		{
			y += (FPolishNotation(functionStr, x, y) + FPolishNotation(functionStr, x + step, y + step * FPolishNotation(functionStr, x, y)))* step / 2;

			if (y == INFINITY) throw overflow_error("y = INFINITY");
			if (isnan(y)) throw invalid_argument("y = NaN");

			points[i] = Point{ x,y };
			x += step;
		}
		break;


	case METHOD_ADAMS:
		double y1 = y + step * FPolishNotation(functionStr, x, y);
		double y2 = y1 + step * FPolishNotation(functionStr, x + step, y1);
		double y3 = y2 + step * FPolishNotation(functionStr, x + 2 * step, y2);
		double y4 = y3 + step * FPolishNotation(functionStr, x + 3 * step, y3);

		for (int i = 1; i < countPoints; i++)
		{
			double f1 = FPolishNotation(functionStr, x + 4 * step, y4);
			double f2 = FPolishNotation(functionStr, x + 3 * step, y3);
			double f3 = FPolishNotation(functionStr, x + 2 * step, y2);;
			double f4 = FPolishNotation(functionStr, x + step, y1);

			double y5 = y4 + step / 24 * (55 * f1 - 59 * f2 + 37 * f3 - 9 * f4);

			if (y5 == INFINITY) throw overflow_error("y = INFINITY");
			if (isnan(y5)) throw invalid_argument("y = NaN");

			y1 = y2;
			y2 = y3;
			y3 = y4;
			y4 = y5;
			x += step;

			Point p = Point{ x,y4 };
			points[i] = p;
		}
		break;
	}

	return points;
}


void GetClientSize(RECT rect, int& width, int &height, int panelElementsHeight, int marginLeft, int marginRight, int marginTop, int marginBottom)
{
	width = rect.right - rect.left;
	height = rect.bottom - rect.top - panelElementsHeight;

	if (width > (marginLeft + marginRight)) width -= (marginLeft + marginRight);
	if (height > (marginTop + marginBottom)) height -= (marginTop + marginBottom);
}


void DrawCoordinates(HDC hDC, HPEN hPen, int countCoordLines, int coordLinesLength, int coordStrLength,
	int bottomHorizontalMarginText, int leftHorizontalMarginText, int bottomVerticalMarginText, int leftVercticalMarginText,
	TCHAR *coordStr, int marginLeft, int marginTop, int panelElementsHeight, int width, int height, double xStart, double xEnd, double yMax, double yMin)
{
	int xCoord;
	int yCoord;


	for (int i = 1; i <= countCoordLines; i++)
	{
		// top
		xCoord = marginLeft + width * i / (countCoordLines + 1);
		yCoord = marginTop + panelElementsHeight;

		MoveToEx(hDC, xCoord, yCoord, NULL);
		LineTo(hDC, xCoord, yCoord + coordLinesLength);

		// bottom
		yCoord = marginTop + height + panelElementsHeight;

		ClearStr(coordStr, coordStrLength);
		snprintf(coordStr, coordStrLength, TEXT("%3.2f"), xStart + (xEnd - xStart) / (countCoordLines + 1) * i);
		TextOut(hDC, xCoord + bottomHorizontalMarginText, yCoord + bottomVerticalMarginText, coordStr, coordStrLength);

		MoveToEx(hDC, xCoord, yCoord, NULL);
		LineTo(hDC, xCoord, yCoord - coordLinesLength);

		// left
		xCoord = marginLeft;
		yCoord = marginTop + height * i / (countCoordLines + 1) + panelElementsHeight;

		ClearStr(coordStr, coordStrLength);
		snprintf(coordStr, coordStrLength, TEXT("%3.2f"), yMin + (yMax - yMin) / (countCoordLines + 1) * (countCoordLines - i + 1));
		TextOut(hDC, xCoord + leftHorizontalMarginText, yCoord + leftVercticalMarginText, coordStr, coordStrLength);

		MoveToEx(hDC, xCoord, yCoord, NULL);
		LineTo(hDC, xCoord + coordLinesLength, yCoord);

		// right
		xCoord = marginLeft + width;

		MoveToEx(hDC, xCoord, yCoord, NULL);
		LineTo(hDC, xCoord - coordLinesLength, yCoord);
	}
}


void DrawBorder(HDC hDC, int marginLeft, int marginTop, int panelElementsHeigh, int width, int height)
{
	MoveToEx(hDC, marginLeft, marginTop + panelElementsHeigh, NULL);
	LineTo(hDC, marginLeft + width, marginTop + panelElementsHeigh);
	LineTo(hDC, marginLeft + width, marginTop + height + panelElementsHeigh);
	LineTo(hDC, marginLeft, marginTop + height + panelElementsHeigh);
	LineTo(hDC, marginLeft, marginTop + panelElementsHeigh);
}


void DrawXYAxis(HDC hDC, int marginLeft, int marginTop, int panelElementsHeight, int width, int height, double xStart, double xEnd, double yMax, double yMin)
{
	if (yMax*yMin < 0)
	{
		double xCoord = marginLeft;
		double yCoord = height * yMax / (yMax - yMin) + marginTop + panelElementsHeight;

		MoveToEx(hDC, xCoord, yCoord, NULL);
		LineTo(hDC, xCoord+width, yCoord);
	}
	if (xStart*xEnd < 0)
	{
		double xCoord = marginLeft + width - width * xEnd / (xEnd - xStart);
		double yCoord = marginTop + panelElementsHeight;

		MoveToEx(hDC, xCoord, yCoord, NULL);
		LineTo(hDC, xCoord , yCoord+height);
	}
}


double FPolishNotation(string str, double x, double y)
{
	static string prevStr = "";
	static vector<string> reversePolishStr;
	

	if (prevStr != str)
	{
		regex regexFunc("x|y|(\\d+(\\.\\d+)?)|[\\+\\-\\^\\*\\/\\(\\)]|sin\\(|cos\\(|tg\\(|ctg\\(|asin\\(|acos\\(|atan\\(|sinh\\(|cosh\\(|tanh\\(|exp\\(|log\\(|log10\\(|sqrt\\(");
		vector<string> splitedString;


		if (!PrepareStr(str, splitedString, regexFunc))
		{
			throw invalid_argument("Invalid function");
		}

		reversePolishStr = FormPolishStr(splitedString);		
		prevStr = str;
	}
	


	return Calculate(reversePolishStr, x,y);
}


	
void FindYMaxMin(Point arr[], int countPoints, double &yMax, double &yMin)
{
	for (int i = 0; i < countPoints; i++)
	{
		double y = arr[i].y;
		if (arr[i].y > yMax) yMax = arr[i].y;
		else
			if (arr[i].y < yMin) yMin = arr[i].y;
	}

	if (yMax == yMin)
	{
		if (yMax == 0)
		{
			yMax = 1;
			yMin = -1;
		}
		else
		{
			yMax += yMax / 10;
			yMin -= yMin / 10;
		}		
	}
}


void ClearStr(TCHAR *str, int length)
{
	for (int i = 0; i < length; i++)
	{
		str[i] = '\0';
	}
}


double FCpp(double x)
{
	return (6 * sin(x) - 2 * pow(sin(x), 3)) / (3 * cos(x));
}


double GetDelta(Point arr[], int countPoints)
{
	double delta = 0;
	for (int i = 0; i < countPoints; i++)
	{
		delta += fabs(arr[i].y - FCpp(arr[i].x));
	}
	delta /= countPoints;

	return delta;	
}

