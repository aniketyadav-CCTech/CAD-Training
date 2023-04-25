#pragma once
#include "IGeometry.h"
#include "Export.h"

class DllExport Line : public IGeometry
{
public:
	Line();
	void input();
	void display();
};