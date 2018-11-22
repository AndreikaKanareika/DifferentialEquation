#pragma once

#include <windows.h> 
#include <tchar.h> 
#include <iostream>
#include <string>
#include <vector>
#include "Macros.h"
#include "TextBoxAndComboBoxFunctions.h"
#include "Point.h"
#include "MainGraphicWindow.h"
#include "SettingsGraphicWindow.h"


HWND CreateAndRegisterWindow(HINSTANCE This, TCHAR *className, TCHAR *windowName, WNDPROC WndProc, DWORD style, int width, int height);