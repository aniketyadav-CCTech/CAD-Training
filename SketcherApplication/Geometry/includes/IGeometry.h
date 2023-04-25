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
	IGeometry() {}
	IGeometry(string name ) {
		this->name = name;
	}
	virtual void input() = 0;
	virtual void display()=0;

};

