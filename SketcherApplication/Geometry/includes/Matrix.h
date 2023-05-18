#pragma once

#include<vector>
#include "IGeometry.h"
#include "Export.h"

class DllExport Matrix :public IGeometry
{
public :
	int row, column;
	vector<vector<double>> matElement;
	Matrix();
	Matrix(int row, int column);
	void input();
	void display();
};