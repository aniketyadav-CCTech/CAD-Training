#pragma once
#include<math.h>

#define TOLERANCE 0.0000000001
#define ZERO 0.0

static bool isEqualD(double x, double y)
{
	return fabs(x - y) < TOLERANCE;
}