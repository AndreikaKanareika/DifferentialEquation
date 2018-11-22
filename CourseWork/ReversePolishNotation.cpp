#include "ReversePolishNotation.h"

using namespace std;







// Ошибки:

// Не закрытая скобка
// cos(x
// FIXED

// Отсутствие знака между операндами
// cos(x)x
// cos(x)sin(x)
// FIXED

double ReversePolishNotation(string s, double x, double y) 
{
	regex regexFunc("(\\d+(\\.\\d+)?)|[\\+\\-\\^\\*\\/\\(\\)]|sin\\(|cos\\(|tg\\(|ctg\\(|asin\\(|acos\\(|atan\\(|sinh\\(|cosh\\(|tanh\\(|exp\\(|log\\(|log10\\(|sqrt\\(");
	vector<string> splitedString;
	vector<string> reversePolishStr;

	if (!PrepareStr(s, x, y, splitedString, regexFunc))
	{	
		throw invalid_argument("Invalid function");
	}
	
	reversePolishStr = FormPolishStr(splitedString);
	
	return Calculate(reversePolishStr, x,y);
}


bool PrepareStr(string s, double x, double y, vector<string> &splitedString, regex regexFunc)
{
	smatch m;

	if (regex_search(s, m, regex("[\\+\\-\\^\\*\\/]{2,}")))
		return false;

	s = regex_replace(s, regex("\\(-"), "(0-");

	if (!ValidateCountOperatorsAndOperands(s))
		return false;

	if (!ValidateCountBrackets(s))
		return false;
	
	
	string ch(1, s[s.size() - 1]);
	if (IsOperator(ch))
		return false;
	

	s = regex_replace(s, regex("x"), "(x)");
	s = regex_replace(s, regex("y"), "(y)");
//	s = regex_replace(s, regex("x"), to_string(x));
//	s = regex_replace(s, regex("y"), to_string(y));
	s = regex_replace(s, regex(","), ".");
	s = regex_replace(s, regex(" "), "");


	s.insert(0, "(");
	s = s.append(")");


	int startLength = s.length();
	int length = 0;

	
	while (regex_search(s, m, regexFunc)) {

		splitedString.push_back(m[0]);
		length += m[0].length();
		s = m.suffix();
	}
	if (length != startLength)
		return false;
	return true;
}

bool ValidateCountOperatorsAndOperands(string s)
{
	string tempStr = s;
	smatch m;
	int countOperators = 0;
	int countOperands = 0;

	while (regex_search(tempStr, m, regex("[\\+\\-\\^\\*\\/]")))
	{
		countOperators++;
		tempStr = m.suffix();
	}
	tempStr = s;
	while (regex_search(tempStr, m, regex("x|y|(\\d+(\\.\\d+)?)")))
	{
		countOperands++;
		tempStr = m.suffix();
	}

	if (countOperators + 1 != countOperands)
		return false;
	return true;
}

bool ValidateCountBrackets(string s)
{
	string tempStr = s;
	smatch m;
	int countLeftBrakets = 0;
	int countRightBrakets = 0;

	tempStr = s;
	while (regex_search(tempStr, m, regex("\\(")))
	{
		countLeftBrakets++;
		tempStr = m.suffix();
	}
	tempStr = s;
	while (regex_search(tempStr, m, regex("\\)")))
	{
		countRightBrakets++;
		tempStr = m.suffix();
	}

	if (countLeftBrakets != countRightBrakets)
		return false;
	return true;
}


vector<string> FormPolishStr(vector<string> splitedString)
{
	stack<string> stackStr;
	vector<string> reversePolishStr;


	for (int i = 0; i < splitedString.size(); i++)
	{
		if (i == 29)
		{
			int a = 1;
		}

		// Функция
		if (IsFunc(splitedString[i]))
		{
			stackStr.push(splitedString[i]);
			continue;
		}

		// Скобка
		if (IsBracket(splitedString[i]))
		{
			if (splitedString[i] == ")")
			{
				GoBackByBrakets(reversePolishStr, stackStr);
			}
			else stackStr.push(splitedString[i]);

			continue;
		}


		// Знак
		if (IsOperator(splitedString[i]))
		{
			if (stackStr.size() == 0)
				throw invalid_argument("Invalid function.\nInformation: Error in FormPolishNotation in IsOperator block. Stack size = 0");

			if (GetPriority(splitedString[i].c_str()[0]) < GetPriority(stackStr.top().c_str()[0]))
			{
				GoBackByOperator(reversePolishStr, stackStr, GetPriority(splitedString[i].c_str()[0]));
			}

			stackStr.push(splitedString[i]);
			continue;
		}

		// число
		reversePolishStr.push_back(splitedString[i]);
	}

	return reversePolishStr;
}


double Calculate(vector<string> reversePolishStr, double x, double y)
{
	stack<double> stackDouble;

	for (int i = 0; i < reversePolishStr.size(); i++)
	{
		if (IsFunc(reversePolishStr[i]))
		{
			double value = stackDouble.top();
			stackDouble.pop();

			stackDouble.push(CalculateFunc(value, reversePolishStr[i]));

			continue;
		}

		if (IsOperator(reversePolishStr[i]))
		{
			double b = stackDouble.top();
			stackDouble.pop();
			double a = stackDouble.top();
			stackDouble.pop();

			stackDouble.push(CalculateOperation(a, b, reversePolishStr[i]));

			continue;
		}

		if (reversePolishStr[i] == "x") stackDouble.push(x);
		else
		if (reversePolishStr[i] == "y") stackDouble.push(y);
		else stackDouble.push(atof(reversePolishStr[i].c_str()));
	}

	//
	//
	//
	if (stackDouble.size() > 1)
		throw invalid_argument("Invalid function.\nInformation: Error in Calculate. Stack size > 1");
	//
	//
	//

	return stackDouble.top();
}

double CalculateFunc(double value, string s)
{
	if (s == "sin(") return sin(value);
	if (s == "cos(") return cos(value);
	if (s == "tg(") return tan(value);
	if (s == "ctg(") return (1 / tan(value));
	if (s == "acos(") return acos(value);
	if (s == "asin(") return asin(value);
	if (s == "atan(") return atan(value);
	if (s == "sinh(") return sinh(value);
	if (s == "cosh(") return cosh(value);
	if (s == "tanh(") return tanh(value);
	if (s == "exp(") return exp(value);
	if (s == "log(") return log(value);
	if (s == "log10(") return log10(value);
	if (s == "sqrt(") return sqrt(value);

	throw invalid_argument("Unknown function: " + s);
}

double CalculateOperation(double a, double b, string s)
{
	if (s == "*") return (a*b);
	if (s == "/") return (a / b);
	if (s == "+") return (a + b);
	if (s == "-") return (a - b);
	if (s == "^") return pow(a, b);

	throw invalid_argument("Unknown operator: " + s);
}


bool IsFunc(string s)
{
	if (s == "sin(" || s == "cos(" || s == "tg(" || s == "ctg(" ||
		s == "acos(" || s == "asin(" || s == "atan(" ||
		s == "sinh(" || s == "cosh(" || s == "tanh(" ||
		s == "exp(" || s == "log(" || s == "log10(" || s == "sqrt(")
		return true;
	return false;
}
bool IsBracket(string s)
{
	if (s == "(" || s == ")")
		return true;

	return false;
}
bool IsOperator(string s)
{
	if (s == "*" || s == "/" || s == "+" || s == "-" || s == "^")
		return true;
	return false;
}


void GoBackByBrakets(vector<string> &reversePolishStr, stack<string> &st)
{
	int pos = st.top().find('(', 0);
	while (pos < 0)		
	{
		// Может быть исключение

		reversePolishStr.push_back(st.top());
		st.pop();

		pos = st.top().find('(', 0);
	}

	if (IsFunc(st.top())) reversePolishStr.push_back(st.top());

	if (st.size() == 0)
		throw invalid_argument("Invalidate function.\nInformation: not founded '(' in GoBackByBrakets function.");
	else st.pop();
}

void GoBackByOperator(vector<string> &reversePolishStr, stack<string> &st, int priority)
{
	while (GetPriority(st.top().c_str()[0]) > priority)
	{
		reversePolishStr.push_back(st.top());
		st.pop();

		if (st.size() == 0)
			throw invalid_argument("Invalidate function.\nInformation: Error in GoBackByOperator function.");
	}
}

int GetPriority(char ch)
{
	switch (ch)
	{
	case '(':
	case ')': return 0;
	case '+': return 1;
	case '-': return 2;
	case '*':
	case '/': return 3;
	case '^': return 4;
	default:	//Functions		
		return 0;
	}
}

