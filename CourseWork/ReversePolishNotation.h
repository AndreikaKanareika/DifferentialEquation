#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <regex>
#include <stack>

using namespace std;

double ReversePolishNotation(string s, double x, double y);
bool PrepareStr(string s, double x, double y, vector<string> &splitedString, regex regexFunc);

bool ValidateCountOperatorsAndOperands(string s);
bool ValidateCountBrackets(string s);

vector<string> FormPolishStr(vector<string> splitedString);

double Calculate(vector<string> reversePolishStr, double x, double y);
double CalculateFunc(double value, string s);
double CalculateOperation(double a, double b, string s);


bool IsFunc(string s);
bool IsBracket(string s);
bool IsOperator(string s);
void GoBackByBrakets(vector<string> &reversePolishStr, stack<string> &st);
void GoBackByOperator(vector<string> &reversePolishStr, stack<string> &st, int priority);
int GetPriority(char ch);