#include "Line.h"

using namespace std;


void Line::input()
{
	cout << "Enter point endpoint1" << endl;
	cin >> endpoint1.x >> endpoint1.y >> endpoint1.z;
	cout << "Enter point endpoint2" << endl;
	cin >> endpoint2.x >> endpoint2.y >> endpoint2.z;
}

void Line::display()
{
	cout << name << "\tPoint 1 : " << endpoint1.x << "  " << endpoint1.y << "  " << endpoint1.z << endl;
	cout << "\t" << "Point 2 : " << endpoint2.x << "  " << endpoint2.y << "  " << endpoint2.z << endl;
}

void Line::setDirection(Vector& _dir)
{
	dir = _dir;
}

void Line::setDirection(Point &p1, Point &p2)
{
	Point p = endpoint2 - endpoint1;
	dir = Vector(array<double, 3>{ p.x, p.y, p.z });
}

void Line::setPoint(Point& _point)
{
	point_in_line = _point;
}
