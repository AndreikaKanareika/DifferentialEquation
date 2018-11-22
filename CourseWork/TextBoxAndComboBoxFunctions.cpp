#include "TextBoxAndComboBoxFunctions.h"

using namespace std;



void AddStringInComboBox(HWND hBox, LPARAM str, LPARAM value)
{
	int pos = SendMessage(hBox, CB_ADDSTRING, 0, str);
	SendMessage(hBox, CB_SETITEMDATA, pos, value);
}


int GetIntFromTextBox(HWND hTextBox)
{
	const int bufferLength = 10;
	TCHAR buffer[bufferLength];

	GetWindowText(hTextBox, buffer, bufferLength);

	for (int i = 0; i < bufferLength && buffer[i] != '\0'; i++)
	{
		if ((buffer[i] < 0 || buffer[i] > 255) ||
			(!isdigit(buffer[i]) && buffer[i] != '-'))
			throw invalid_argument("Invalid argument");
	}

	return _tstoi(buffer);
}

string GetStringFromTextBox(HWND hTextBox)
{
	const int bufferLength = 100;
	TCHAR buffer[bufferLength];

	GetWindowText(hTextBox, buffer, bufferLength);

	return buffer;
}


void SetIntToTextBox(HWND hTextBox, int number)
{
	const int bufferLength = 10;
	TCHAR buffer[bufferLength];

	snprintf(buffer, bufferLength, TEXT("%d"), number);
	SetWindowText(hTextBox, buffer);
}


void SetDoubleToTextBox(HWND hTextBox, double number)
{
	const int bufferLength = 10;
	TCHAR buffer[bufferLength];

	snprintf(buffer, bufferLength, TEXT("%5.3f"), number);
	SetWindowText(hTextBox, buffer);
}


double GetDoubleFromTextBox(HWND hTextBox)
{
	const int bufferLength = 10;
	TCHAR buffer[bufferLength];


	GetWindowText(hTextBox, buffer, bufferLength);

	for (int i = 0; i < bufferLength; i++)
	{
		if (buffer[i] == ',')
			buffer[i] = '.';
	}

	return stod(buffer, NULL);
}