#include "Sketch.h"

Sketch::Sketch()
{
}

void Sketch::add(IGeometry* geom)
{
	vecMenu.push_back(geom);
}

void Sketch::display()
{
	if (vecMenu.empty())
		cout << "Sketcher is Empty, please input any geometry" << endl;
	for (auto iter = vecMenu.begin(); iter != vecMenu.end(); iter++)
	{
		IGeometry* obj = *iter;
		obj->display();
	}
}
