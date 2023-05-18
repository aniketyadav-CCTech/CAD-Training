#pragma once
#include "IGeometry.h"
#include <iostream>
#include "Export.h"
#include <array>
#include "Core.h"

#define X 0
#define Y 1
#define Z 2

class DllExport Vector : public IGeometry
{
	std::array<double, 3> coords = {};

	friend float dotProduct(const Vector& v1, const Vector& v2);
public:
	Vector() :coords({0,0,0}) {}

	Vector(std::array<double, 3> _coords) : coords(_coords) {}

	Vector(double _x, double _y, double _z) : coords({ _x,_y,_z }) {}

	Vector(double _x, double _y) : Vector(_x, _y, 0) {}

	void input();
	void display();

	// Eqality check
	bool operator==(const Vector&) const;

	// Not equal check operator
	bool operator!=(const Vector&) const;

	// Less than operator for comparison
	bool operator<(const Vector&) const;

	// Greater than operator for comparison
	bool operator>(const Vector&) const;

	Vector operator*(double value);

	// Substraction operator. Substract x and y component separately.
	Vector operator-(const Vector&) const;

	// Greater than operator for comparison
	Vector operator+(const Vector&) const;

	//TODO make this to modifiable
	double operator[](const unsigned int) const;
};