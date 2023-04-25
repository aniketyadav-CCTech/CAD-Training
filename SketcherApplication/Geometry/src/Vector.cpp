#include "Vector.h"

Vector::Vector():IGeometry("Vector")
{
}

void Vector::input()
{
	cout << " Enter the Values of Vector(X,Y,Z) " << endl;
	cin >> x >> y >> z;
}

void Vector::display()
{
	cout << this->name << " => " << x << " " << y << " " << z << endl;
}
