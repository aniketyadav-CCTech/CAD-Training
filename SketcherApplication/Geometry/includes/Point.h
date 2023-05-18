#pragma once
#include "IGeometry.h"
#include "Export.h"
#include "Vector.h"

//class DllExport Point :public IGeometry
//{
//public:
//	double x, y, z;
//	Point();
//	Point(double _x, double _y, double _z);
//	void input();
//	void display();
//	Point operator-(const Point&) const;
//};


struct DllExport Point : public IGeometry {
	double x, y, z;
	Point();
	Point(double x, double y, double z);
	Point operator-(const Point& _other) const;
};
DllExport void operator>>(istream& in, Point& pt);