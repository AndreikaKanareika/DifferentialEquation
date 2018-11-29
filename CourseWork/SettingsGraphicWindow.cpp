#include "SettingsGraphicWindow.h"

using namespace std;

LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hColorComboBox;
	static HWND hMargL, hMargR, hMargT, hMargB;
	static HWND hHorMargTxtL, hHorMargTxtB, hVerMargTxtL, hVerMargTxtB;
	static HWND hCountCoord, hCoordLen;
	static HWND hXStart, hXEnd, hStep;
	static HWND hGraphicWnd;
	

	switch (message)
	{
	case WM_CREATE:
		CreateWindowEx(NULL, "static", "Отступ слева:", WS_VISIBLE | WS_CHILD, 10, 10, 100, 20, hWnd, (HMENU)0, NULL, NULL);
		hMargL = CreateWindowEx(NULL, "edit", "left", WS_VISIBLE | WS_CHILD | WS_BORDER, 115, 10, 50, 20, hWnd, (HMENU)ID_SETTING_MARGINLEFT, NULL, NULL);
		CreateWindowEx(NULL, "static", "Отступ сверху:", WS_VISIBLE | WS_CHILD, 10, 40, 100, 20, hWnd, (HMENU)0, NULL, NULL);
		hMargT = CreateWindowEx(NULL, "edit", "top", WS_VISIBLE | WS_CHILD | WS_BORDER, 115, 40, 50, 20, hWnd, (HMENU)ID_SETTING_MARGINTOP, NULL, NULL);
		CreateWindowEx(NULL, "static", "Отступ справа:", WS_VISIBLE | WS_CHILD, 220, 10, 100, 20, hWnd, (HMENU)0, NULL, NULL);
		hMargR = CreateWindowEx(NULL, "edit", "right", WS_VISIBLE | WS_CHILD | WS_BORDER, 325, 10, 50, 20, hWnd, (HMENU)ID_SETTING_MARGINRIGHT, NULL, NULL);
		CreateWindowEx(NULL, "static", "Отступ снизу:", WS_VISIBLE | WS_CHILD, 220, 40, 100, 20, hWnd, (HMENU)0, NULL, NULL);
		hMargB = CreateWindowEx(NULL, "edit", "bottom", WS_VISIBLE | WS_CHILD | WS_BORDER, 325, 40, 50, 20, hWnd, (HMENU)ID_SETTING_MARGINBOTTOM, NULL, NULL);

		CreateWindowEx(NULL, "static", "Кол-во отметок:", WS_VISIBLE | WS_CHILD, 10, 90, 105, 20, hWnd, (HMENU)0, NULL, NULL);
		hCountCoord = CreateWindowEx(NULL, "edit", "countCoord", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 90, 50, 20, hWnd, (HMENU)ID_SETTING_COUNTCOORDLINES, NULL, NULL);
		CreateWindowEx(NULL, "static", "Длина отметок:", WS_VISIBLE | WS_CHILD, 220, 90, 105, 20, hWnd, (HMENU)0, NULL, NULL);
		hCoordLen = CreateWindowEx(NULL, "edit", "coordLen", WS_VISIBLE | WS_CHILD | WS_BORDER, 325, 90, 50, 20, hWnd, (HMENU)ID_SETTING_COORDLINESLENGTH, NULL, NULL);


		CreateWindowEx(NULL, "static", "Координаты (слева)", WS_VISIBLE | WS_CHILD, 10, 140, 150, 20, hWnd, (HMENU)0, NULL, NULL);
		CreateWindowEx(NULL, "static", "Сдвиг сверху-вниз:", WS_VISIBLE | WS_CHILD, 10, 170, 150, 20, hWnd, (HMENU)0, NULL, NULL);
		hVerMargTxtL = CreateWindowEx(NULL, "edit", "leftVerMarginTxt", WS_VISIBLE | WS_CHILD | WS_BORDER, 165, 170, 50, 20, hWnd, (HMENU)ID_SETTING_LEFTHORIZONTALMARGINTEXT, NULL, NULL);
		CreateWindowEx(NULL, "static", "Сдвиг слева-направо:", WS_VISIBLE | WS_CHILD, 10, 200, 150, 20, hWnd, (HMENU)0, NULL, NULL);
		hHorMargTxtL = CreateWindowEx(NULL, "edit", "leftHorMarginTxt", WS_VISIBLE | WS_CHILD | WS_BORDER, 165, 200, 50, 20, hWnd, (HMENU)ID_SETTING_BOTTOMHORIZONTALMARGINTEXT, NULL, NULL);

		CreateWindowEx(NULL, "static", "Координаты (снизу)", WS_VISIBLE | WS_CHILD, 220, 140, 150, 20, hWnd, (HMENU)0, NULL, NULL);
		CreateWindowEx(NULL, "static", "Сдвиг сверху-вниз:", WS_VISIBLE | WS_CHILD, 220, 170, 150, 20, hWnd, (HMENU)0, NULL, NULL);
		hVerMargTxtB = CreateWindowEx(NULL, "edit", "btmVerMarginTxt", WS_VISIBLE | WS_CHILD | WS_BORDER, 365, 170, 50, 20, hWnd, (HMENU)ID_SETTING_LEFTVERTICALMARGINTEXT, NULL, NULL);
		CreateWindowEx(NULL, "static", "Сдвиг слева-направо:", WS_VISIBLE | WS_CHILD, 220, 200, 150, 20, hWnd, (HMENU)0, NULL, NULL);
		hHorMargTxtB = CreateWindowEx(NULL, "edit", "btmVerMarginTxt", WS_VISIBLE | WS_CHILD | WS_BORDER, 365, 200, 50, 20, hWnd, (HMENU)ID_SETTING_BOTTOMVERTICALMARGINTEXT, NULL, NULL);

		CreateWindowEx(NULL, "static", "Х нач.:", WS_VISIBLE | WS_CHILD, 10, 240, 50, 20, hWnd, (HMENU)0, NULL, NULL);
		hXStart = CreateWindowEx(NULL, "edit", "xStart", WS_VISIBLE | WS_CHILD | WS_BORDER, 70, 240, 50, 20, hWnd, (HMENU)ID_SETTING_COUNTCOORDLINES, NULL, NULL);
		CreateWindowEx(NULL, "static", "Х кон.:", WS_VISIBLE | WS_CHILD, 10, 270, 50, 20, hWnd, (HMENU)0, NULL, NULL);
		hXEnd = CreateWindowEx(NULL, "edit", "xEnd", WS_VISIBLE | WS_CHILD | WS_BORDER, 70, 270, 50, 20, hWnd, (HMENU)ID_SETTING_COORDLINESLENGTH, NULL, NULL);
		CreateWindowEx(NULL, "static", "Шаг:", WS_VISIBLE | WS_CHILD, 10, 300, 50, 20, hWnd, (HMENU)0, NULL, NULL);
		hStep = CreateWindowEx(NULL, "edit", "step", WS_VISIBLE | WS_CHILD | WS_BORDER, 70, 300, 50, 20, hWnd, (HMENU)ID_SETTING_COORDLINESLENGTH, NULL, NULL);

		hColorComboBox = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("combobox"), "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, 220, 240, 180, 100, hWnd, (HMENU)ID_SETTING_COLORCOMBOBOX, NULL, NULL);
		AddStringInComboBox(hColorComboBox, (LPARAM)"Красный", (LPARAM)RGB(255, 0, 0));
		AddStringInComboBox(hColorComboBox, (LPARAM)"Зеленый", (LPARAM)RGB(0, 255, 0));
		AddStringInComboBox(hColorComboBox, (LPARAM)"Синий", (LPARAM)RGB(0, 0, 255));

		CreateWindowEx(NULL, "button", "Сохранить", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 350, 180, 50, hWnd, (HMENU)ID_SETTING_BUTTONSAVE, NULL, NULL);
		CreateWindowEx(NULL, "button", "Отмена", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 350, 180, 50, hWnd, (HMENU)ID_SETTING_BUTTONCANCEL, NULL, NULL);

		break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_SETTING_BUTTONSAVE:
			Settings set;
			int pos;

			try
			{
				set.marginLeft = GetIntFromTextBox(hMargL);
				set.marginRight = GetIntFromTextBox(hMargR);
				set.marginTop = GetIntFromTextBox(hMargT);
				set.marginBottom = GetIntFromTextBox(hMargB);

				set.leftHorizontalMarginText = GetIntFromTextBox(hHorMargTxtL);
				set.bottomHorizontalMarginText = GetIntFromTextBox(hHorMargTxtB);
				set.leftVerticalMarginText = GetIntFromTextBox(hVerMargTxtL);
				set.bottomVerticalMarginText = GetIntFromTextBox(hVerMargTxtB);

				set.countCoordLines = GetIntFromTextBox(hCountCoord);
				set.coordLinesLength = GetIntFromTextBox(hCoordLen);

				set.xStart = GetDoubleFromTextBox(hXStart);
				set.xEnd = GetDoubleFromTextBox(hXEnd);

				if (set.xStart > set.xEnd)
				{
					double temp = set.xStart;
					set.xStart = set.xEnd;
					set.xEnd = temp;
				}

				set.step = GetDoubleFromTextBox(hStep);


				pos = SendMessage(hColorComboBox, CB_GETCURSEL, 0, 0);
				if (pos >= 0)
					set.color = SendMessage(hColorComboBox, CB_GETITEMDATA, pos, 0);

				if (hGraphicWnd == NULL) hGraphicWnd = FindWindow("My", "Graphic");
				SendMessage(hGraphicWnd, GRAPHIC_SETTING_MSG, 0, (LPARAM)&set);

				ShowWindow(hWnd, SW_HIDE);
			}
			catch (invalid_argument)
			{
				MessageBox(hWnd, "Проверьте корректность введенных данных", "Error", NULL);
			}

			break;

		case ID_SETTING_BUTTONCANCEL:

			ShowWindow(hWnd, SW_HIDE);
			break;
		}

		break;
	case SETTING_SET_MSG:
		Settings *set;

		set = (Settings*)lParam;

		SetIntToTextBox(hMargL, set->marginLeft);
		SetIntToTextBox(hMargR, set->marginRight);
		SetIntToTextBox(hMargT, set->marginTop);
		SetIntToTextBox(hMargB, set->marginBottom);
		SetIntToTextBox(hHorMargTxtL, set->leftHorizontalMarginText);
		SetIntToTextBox(hHorMargTxtB, set->bottomHorizontalMarginText);
		SetIntToTextBox(hVerMargTxtL, set->leftVerticalMarginText);
		SetIntToTextBox(hVerMargTxtB, set->bottomVerticalMarginText);
		SetIntToTextBox(hCountCoord, set->countCoordLines);
		SetIntToTextBox(hCoordLen, set->coordLinesLength);
		SetDoubleToTextBox(hXStart, set->xStart);
		SetDoubleToTextBox(hXEnd, set->xEnd);
		SetDoubleToTextBox(hStep, set->step);
		SendMessage(hColorComboBox, CB_SETCURSEL, 0, 0);


		break;
	case WM_DESTROY: PostQuitMessage(0); break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



