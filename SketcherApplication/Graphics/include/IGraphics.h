#pragma once
#include <iostream>
#include "Export.h"
#include "Line.h"
#include "Point.h"
#include "Circle.h"
class DllExport IGraphics
{
public:
	virtual void display() = 0;
	virtual void input() = 0;
};

