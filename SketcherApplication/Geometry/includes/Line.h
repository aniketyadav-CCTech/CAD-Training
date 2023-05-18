#pragma once
#include "IGeometry.h"
#include "Export.h"
#include "Point.h"
#include "Vector.h"


class DllExport Line : public IGeometry
{
	Vector dir;				// Normalized direction vector. 
	Point point_in_line;
	Point endpoint1, endpoint2;

public:

	Line():IGeometry("Line") {}

	Line(Point& endpoint1, Point& endpoint2)
	{
		point_in_line = endpoint1;
		setDirection(endpoint1, endpoint2);
	}

	void input();
	void display();

	void setDirection(Vector&);
	void setDirection(Point &p1,Point &p2);

	void setPoint(Point&);

	Vector direction() const;

	Point point() const;
};