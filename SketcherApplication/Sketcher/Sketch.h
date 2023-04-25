#ifndef _SKETCH_H
#define _SKETCH_H

#include "IGeometry.h"
#include <vector>
class Sketch
{
public:
	Sketch();
	void add(IGeometry* geomtery);
	void display();
private:
	vector<IGeometry*> vecMenu;
};

#endif
