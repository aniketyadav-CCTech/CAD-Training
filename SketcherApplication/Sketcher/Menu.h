#pragma once
#include<iostream>

#include "Point.h"
#include "Line.h"
#include "Menu.h"
#include "Circle.h"
#include "Vector.h"
#include "Matrix.h"
#include "Sketch.h"

using namespace std;

int showMenu(Sketch& sketch) {
	int choice;
	cout << "!----- Welcome To Sketcher -----!" << endl;
	cout << "1. Point " << endl;
	cout << "2. Circle " << endl;
	cout << "3. Line " << endl;
	cout << "4. Vector " << endl;
	cout << "5. Matrix " << endl;
	cout << "6. Display " << endl;
	cout << " Press 0 to Exit " << endl;
	cout << " Enter Your choice " << endl;
	cin >> choice;

	switch (choice)
	{
		case 1:
		{
			Point *point = new Point();
			point->input();
			sketch.add(point);
		}
		break;
		case 2:
		{
			Circle* circle = new Circle();
			circle->input();
			sketch.add(circle);
		}
		break;
	case 3:
		{
			Line* line = new Line();
			line->input();
			sketch.add(line);
		}
		break;

	case 4:
		{
			Vector* vec = new Vector();
			vec->input();
			sketch.add(vec);
		}
		break;

	case 5:
	{
		Matrix* matrix = new Matrix(3,3);
		matrix->input();
		sketch.add(matrix);
	}
	break;

	case  6:
	{
		sketch.display();	
	}
	break;

    default:
		cout << "Function Exited!!" << endl;
		return -1;
	}
	return 1;
}