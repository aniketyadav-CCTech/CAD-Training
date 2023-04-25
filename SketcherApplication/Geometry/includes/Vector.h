#pragma once
#include "IGeometry.h"
#include "Export.h"

class DllExport Vector : public IGeometry
{
public:
	Vector();
	void input();
	void display();
};