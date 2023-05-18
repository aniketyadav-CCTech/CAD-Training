#pragma once

#include "IGeometry.h"
#include "Point.h"

class DllExport Circle : public IGeometry
{
public:
	Point centerPoint;
	double radius;
	Circle();
	void input();
	void display();
};