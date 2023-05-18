#include "Vector.h"


void Vector::input()
{
	cout << " Enter the Values of Vector(X,Y,Z) " << endl;
	cin >> coords[X] >> coords[Y] >> coords[Z];

}

void Vector::display()
{
	cout << this->name << " => " << coords[X] << " " << coords[Y] << " " << coords[Z] << endl;
}

inline bool Vector::operator==(const Vector& _other) const
{
	for (int i = 0; i < 3; i++)
	{
		if (!isEqualD(coords[i], _other.coords[i]))
			return false;
	}
	return true;
}


inline bool Vector::operator!=(const Vector& _other) const
{
	return !(*this == _other);
}


inline bool Vector::operator<(const Vector& _other) const
{
	for (size_t i = 0; i < 3; i++)
	{
		if (this->coords[i] < _other.coords[i])
			return true;
		else if (this->coords[i] > _other.coords[i])
			return false;
	}

	return false;
}


inline bool Vector::operator>(const Vector& _other) const
{
	if (*this == _other)
		return false;
	return !(*this < _other);
}

inline Vector Vector::operator*(double value)
{
	std::array<double, 3> temp_array;

	for (int i = 0; i < 3; i++)
		temp_array[i] = coords[i] * value;

	return Vector(temp_array);
}


inline Vector Vector::operator-(const Vector& _other) const
{
	std::array<double, 3> temp_array;

	for (int i = 0; i < 3; i++)
		temp_array[i] = coords[i] - _other.coords[i];

	return Vector(temp_array);
}


inline Vector Vector::operator+(const Vector& _other) const
{
	std::array<double, 3> temp_array;

	for (int i = 0; i < 3; i++)
		temp_array[i] = coords[i] + _other.coords[i];

	return Vector(temp_array);
}


inline double Vector::operator[](const unsigned int _index) const
{
	if (_index >= coords.size()) {
		std::cout << "Index out of bounds";
		return double();
	}

	return coords[_index];
}

float dotProduct(const Vector& v1, const Vector& v2)
{
	if (v1.coords.size() != v2.coords.size())
		return FLT_MIN;

	float product = 0;
	for (size_t i = 0; i < v1.coords.size(); i++)
		product = product + v1[i] * v2[i];
	return product;
}

