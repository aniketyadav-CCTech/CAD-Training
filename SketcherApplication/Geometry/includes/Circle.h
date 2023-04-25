#pragma once

#include "IGeometry.h"

class DllExport Circle : public IGeometry
{
public:
	Circle();
	void input();
	void display();
};