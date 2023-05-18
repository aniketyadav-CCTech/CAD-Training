#include "Sketch.h"

Sketch* Sketch::sketchInstance = nullptr;

Sketch::Sketch()
{
}

void Sketch::add(IGraphics* geom)
{
	vecMenu.push_back(geom);
}

void Sketch::display()
{
	if (vecMenu.empty())
		cout << "Sketcher is Empty, please input any geometry" << endl;

	for (auto iter = vecMenu.begin(); iter != vecMenu.end(); iter++)
	{
		IGraphics* obj = *iter;
		obj->display();
		
	}
}

Sketch* Sketch::instance()
{
	if(sketchInstance != nullptr)
		sketchInstance = new Sketch();
	return sketchInstance;
}
