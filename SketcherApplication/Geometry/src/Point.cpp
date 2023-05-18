#include "Point.h"

using namespace std;

Point::Point() :IGeometry("Point")
{
	x = 0; y = 0; z = 0;
}

Point::Point(double _x, double _y, double _z):x(_x),y(_y),z(_z) {

}

//void Point::input()
//{
//	cout << "Enter 3D Points " << endl;
//	cin >> this->x >> this->y >> this->z;
//}
//
//void Point::display()
//{
//	cout << name << " : " << this->x << "  " << this->y << "  " << this->z << endl;
//}

Point Point::operator-(const Point& _other) const
{
	Point temp;
	temp.x = x - _other.x;
	temp.y = y - _other.y;
	temp.z = z - _other.z;

	return temp;
}

void operator>>(istream& in,Point& pt) {
	double x, y, z;
	in >> x >> y >> z;
	Point newpt(x, y, z);
	pt = newpt;
}