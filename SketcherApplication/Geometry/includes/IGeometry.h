#pragma once
#include<iostream>
#include<string>
#include "Export.h"

using namespace std;
class  IGeometry
{
private:	
	
public:
	double x, y, z;
	string name;
	IGeometry() :x(0), y(0), z(0) {};
	IGeometry(string name ) {
		this->name = name;
	}
	//virtual void input() = 0;
	//virtual void display()=0;

};

