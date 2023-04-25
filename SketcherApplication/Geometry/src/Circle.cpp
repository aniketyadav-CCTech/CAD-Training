#include "Circle.h"

using namespace std;

Circle::Circle() :IGeometry("Circle")
{
}

void Circle::input()
{
	cout << "Enter 3D Points " << endl;
	cin >> x >> y >> z;
}

void Circle::display()
{
	cout << name << " : " << x << "  " << y << "  " << z << endl;
}
