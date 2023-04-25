#include "Point.h"

using namespace std;

Point::Point() :IGeometry("Point")
{
}
void Point::input()
{
	cout << "Enter 3D Points " << endl;
	cin >> x >> y >> z;
}

void Point::display()
{
	cout << name << " : " << x << "  " << y << "  " << z << endl;
}

