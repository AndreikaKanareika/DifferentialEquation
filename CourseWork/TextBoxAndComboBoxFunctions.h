#pragma once

#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <string>

using namespace std;

void AddStringInComboBox(HWND hBox, LPARAM str, LPARAM value);
int GetIntFromTextBox(HWND hTextBox);
double GetDoubleFromTextBox(HWND hTextBox);
string GetStringFromTextBox(HWND hTextBox);
void SetIntToTextBox(HWND hTextBox, int number);
void SetDoubleToTextBox(HWND hTextBox, double number);

