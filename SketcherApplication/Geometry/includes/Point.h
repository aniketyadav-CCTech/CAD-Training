#pragma once
#include "IGeometry.h"
#include "Export.h"

class DllExport Point :public IGeometry
{
public:
	Point();
	void input();
	void display();
};