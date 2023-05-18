#include "Circle.h"

using namespace std;

Circle::Circle() :IGeometry("Circle"),centerPoint(0,0,0),radius(0)
{
}

void Circle::input()
{
	cout << "Enter centerPoint" << endl;
	cin >> centerPoint.x >> centerPoint.y >> centerPoint.z;
	cout << "Enter radius" << endl;
	cin >> radius;
}

void Circle::display()
{
	cout << name << " : " << x << "  " << y << "  " << z << endl;
}
