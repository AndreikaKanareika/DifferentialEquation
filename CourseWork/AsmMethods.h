#pragma once

#include <iostream>
#include "Point.h"

using namespace std;

Point* Eiler(double a, double b, double h, double y, double x);
Point* Adams(double a, double b, double h, double y, double x);
double F(double x, double y);