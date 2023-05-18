#include "GraphicsPoint.h"

void GraphicsPoint::display()
{
	cout << "POINT " << endl;
	std::vector<float> vertices;
	vertices.push_back(point.x);
	vertices.push_back(point.y);
	vertices.push_back(point.z);
	vertices.push_back(point.x);
	vertices.push_back(point.y);
	vertices.push_back(point.z);
	vertices.push_back(point.x);
	vertices.push_back(point.y);
	vertices.push_back(point.z);
	vertices.push_back(point.x);
	vertices.push_back(point.y);
	vertices.push_back(point.z);
	vertices.push_back(point.x);
	vertices.push_back(point.y);
	vertices.push_back(point.z);
	vertices.push_back(point.x);
	vertices.push_back(point.y);
	vertices.push_back(point.z);
	vertices.push_back(point.x);
	vertices.push_back(point.y);
	vertices.push_back(point.z);
	vertices.push_back(point.x);
	vertices.push_back(point.y);
	vertices.push_back(point.z);
	OpenGLWrapper opengl(vertices);
	opengl.OpenGLmain();

}

void GraphicsPoint::input()
{
	cout << "Enter 3D coordinates" << endl;
	this->point = Point(1,2,3);
	//cin << point.input();
}
