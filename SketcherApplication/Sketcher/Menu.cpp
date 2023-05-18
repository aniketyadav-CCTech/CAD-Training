#include "Menu.h"


int showMenu(Sketch* sketch) {
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
		IGraphics* point = new GraphicsPoint();
		point->input();
		sketch->add(point);
		break;
	}
	case 2:
	{
		IGraphics* circle = new GraphicsCircle();
		//circle->input();
		sketch->add(circle);
		break;
	}
	case 3:
	{
		IGraphics* line = new GraphicsLine();
		//line->input();
		sketch->add(line);
		break;
	}

	//case 4:
	//{
	//	IGraphics* vec = new Vector();
	//	//vec->input();
	//	sketch->add(vec);
	//}
	//break;

	//case 5:
	//{
	//	IGraphics* matrix = new Matrix(3, 3);
	//	//matrix->input();
	//	sketch->add(matrix);
	//}
	//break;

	case  6:
	{
		sketch->display();
		break;
	}

	default:
		cout << "Function Exited!!" << endl;
		return -1;
	}
	return 1;
}