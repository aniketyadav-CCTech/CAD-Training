#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
// #include "gnuplot-iostream.h"
#include <tuple>

using namespace std;


class Point
{
public:
    Point() {}
    Point(double data[3])
    {
        for (int i = 0; i < 3; i++)
        {
            this->data[i] = data[i];
        }
    }
    double data[3];
};
typedef vector<Point> Curve;
typedef vector<Curve> Surface;

bool surfaceLoft(Curve &circle, Curve &ellipse, int &numV, Surface &loftSurface)
{
    if (circle.size() != ellipse.size())
        return 0;
    double deltaV = 1.0 / numV;
    for (double v = 0; v <= 1.0; v += deltaV)
    {
        Curve c;
        c.resize(circle.size());
        for (int i = 0; i < circle.size(); i++)
        {
            for (int j = 0; j < 3; j++)
                c[i].data[j] = (circle[i].data[j] * (1 - v)) + (ellipse[i].data[j] * v);
        }
        loftSurface.push_back(c);
    }
    return 1;
}

bool generateCircle(Point &centrePoint, double &radius, int &numU, Curve &circle)
{
    double deltatheta = 2 * M_PI / (numU);
    for (double i = 0; i <= 2 * M_PI; i += deltatheta)
    {
        Point p;
        p.data[0] = centrePoint.data[0] + radius * cos(i);
        p.data[1] = centrePoint.data[0] + radius * sin(i);
        p.data[2] = 10;
        circle.push_back(p);
    }
    return 1;
}

bool generateEllipse(Point &centrePoint, double &rMax, double &rMin, int &numU, Curve &ellipse)
{
    double deltatheta = 2 * M_PI / (numU);
    for (double i = 0; i <= 2 * M_PI; i += deltatheta)
    {
        Point p;
        p.data[0] = centrePoint.data[0] + rMax * cos(i);
        p.data[1] = centrePoint.data[0] + rMin * sin(i);
        p.data[2] = 0;
        ellipse.push_back(p);
    }
    return 1;
}

bool displayGNU(Surface loftSurface)
{
    ofstream fout("gnuScript.plt", ios::out | ios::trunc);
    fout << "set title 'circle Ellipse Loft'" << endl;
    fout << "set view equal xyz" << endl;
    fout << "set hidden3d" << endl;
    fout << "set view 1,1,1" << endl;
    fout << "splot 'circleEllipseOutput.gnu' with linespoints" << endl;
    fout << endl
         << "pause -9 \"Hit Enter\" " << endl;
    fout.close();
    system("gnuplot gnuScript.plt");
    return true;
}

int main()
{
    Curve circle;
    Curve ellipse;
    double arr[3]{0, 0, 0};
    int numU = 50, numV = 40;
    Point centrePoint(arr);
    Surface loftSurface;
    double radius = 5.0;
    double rMax = 20, rMin = 30;
    generateCircle(centrePoint, radius, numU, circle);
    generateEllipse(centrePoint, rMax, rMin, numU, ellipse);
    surfaceLoft(circle, ellipse, numV, loftSurface);
    ofstream fout("circleEllipseOutput.gnu");
    for (auto item : loftSurface)
    {
        for (auto subItem : item)
            fout << subItem.data[0] << "\t" << subItem.data[1] << "\t" << subItem.data[2] << "\n";
    }
    displayGNU(loftSurface);
    
    return 1;
}
