#include "AsmMethods.h"


Point* Eiler(double a, double b, double h, double y, double x)
{
	int countPoints = (b - a) / h;
	Point* points = new Point[countPoints];
	
	
	for (int i=0; i<countPoints; i++)
	{
		double f1 = F(x, y);
		double f2 = F(x + h, y + h * F(x, y));

		_asm
		{
			FLD y;

			FLD f1;
			FLD f2;

			FADD;

			FLD h;
			FMUL;

			FLD1;
			FLD1;
			FADD;
			FDIV;

			FADD;

			FSTP y;

			FLD x;
			FLD h;
			FADD;
			FSTP x;

		}
		//	y += (F(x, y) + F(x + h, y + h * F(x,y)))* h / 2;
		//	x = x + h;

		Point p = Point{ x, y };
		points[i] = p;		
	}

	return points;
}

Point* Adams(double a, double b, double h, double y, double x)
{
	int countPoints = (b - a) / h;
	Point* points = new Point[countPoints];
		
	points[0] = Point{ x,y };		
	x += h;	

	double y1 = y + h * F(x, y);
	double y2 = y1 + h * F(x + h, y1);
	double y3 = y2 + h * F(x + 2 * h, y2);
	double y4 = y3 + h * F(x + 3 * h, y3);
	double y5;
		
	for (int i=1; i<countPoints; i++)
	{
		double f1 = F(x + 4 * h, y4);
		double f2 = F(x + 3 * h, y3);
		double f3 = F(x + 2 * h, y2);;
		double f4 = F(x + h, y1);

		int fiftyFive = 55;
		int fiftyNine = 59;
		int thirtySeven = 37;
		int nine = 9;
		int twentyFour = 24;

		_asm
		{
			FLD y4;
			FLD h;
			FLD  twentyFour;

			FDIV;

			FLD fiftyFive;
			FLD f1;
			FMUL;

			FLD fiftyNine;
			FLD f2;
			FMUL;

			FSUB;

			FLD thirtySeven;
			FLD f3;
			FMUL;

			FADD;

			FLD nine;
			FLD f4;
			FMUL;

			FSUB;

			FMUL;

			FADD;

			FSTP y5;

			//y5 = y4 + h/24 * (55 * f1 - 59 * f2 + 37 * f3 - 9 * f4);	


			FLD y5;
			FLD y4;
			FLD y3;
			FLD y2;

			FSTP y1;
			FSTP y2;
			FSTP y3;
			FSTP y4;

			FLD x;
			FLD h;
			FADD;
			FSTP x;
		}

		/*y1 = y2;
		y2 = y3;
		y3 = y4;
		y4 = y5;
		x += h;*/

		Point p = Point{ x, y4 };
		points[i] = p;	
	}
	
	return points;
}


double F(double x, double y)
{
	double res;

	_asm
	{
		FLD1
		FLD1
		FADD

		FLD x
		FCOS

		FLD x
		FCOS

		FMUL

		FLD x
		FCOS

		FLD x
		FSIN

		FDIV

		FMUL
		FMUL

		FLD y
		FADD

		FLD x
		FCOS

		FLD x
		FSIN

		FDIV
		FDIV

		FSTP res
	}

	return res;

	//return (2 * pow(cos(x), 2)*(cos(x) / sin(x)) + y) / (cos(x) / sin(x));
}
