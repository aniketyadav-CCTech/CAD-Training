#include "Matrix.h"

Matrix::Matrix():IGeometry("Matrix")
{
}

Matrix::Matrix(int row, int column)
{
	this->row = row;
	this->column = column;
    this->name = "Matrix";
}

void Matrix::input()
{
    for (int i = 0; i < row; i++)
    {
        vector<double> v1;
        for (int j = 0; j < column; j++)
        {
            int num;
            cout << "Enter Matrix Element" << endl;
            cin >> num;
            v1.push_back(num);
        }
        matElement.push_back(v1);
    }
}

void Matrix::display()
{
    cout << this->name << endl;
    for (int i = 0; i < matElement.size(); i++) 
    {
        for (int j = 0; j < matElement[i].size(); j++)
            cout << matElement[i][j] << " ";
        cout << endl;
    }
}