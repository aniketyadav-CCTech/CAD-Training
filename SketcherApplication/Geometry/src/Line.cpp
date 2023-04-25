#include "Line.h"

using namespace std;

Line::Line() :IGeometry("Line")
{
}

void Line::input()
{
	cout << "Enter 3D Points " << endl;
	cin >> x >> y >> z;
}

void Line::display()
{
	cout << name << " : " << x << "  " << y << "  " << z << endl;
}
