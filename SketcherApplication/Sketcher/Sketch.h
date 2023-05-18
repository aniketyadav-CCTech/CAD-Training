#ifndef _SKETCH_H
#define _SKETCH_H
#include <iostream>
#include "IGraphics.h"
#include <vector>
using namespace std;
class Sketch
{
public:
	void add(IGraphics* geomtery);
	void display();
	static Sketch* instance();

private:
	Sketch();

private:
	vector<IGraphics*> vecMenu;
	static Sketch* sketchInstance;
};

#endif