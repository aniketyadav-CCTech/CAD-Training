#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

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
    Point(double x, double y, double z)
    {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
    }
    double data[3];
};
typedef vector<Point> Curve;
typedef vector<Curve> Surface;

bool surfaceLoft(Curve &line, Curve &bezier, int &numV, Surface &loftSurface)
{
    if (line.size() != bezier.size())
        return 0;
    double deltaV = 1.0 / numV;
    for (double v = 0; v <= 1.0; v += deltaV)
    {
        Curve c;
        c.resize(line.size());
        for (int i = 0; i < c.size(); i++)
        {
            for (int j = 0; j < 3; j++)
                c[i].data[j] = (line[i].data[j] * (1 - v)) + (bezier[i].data[j] * v);
        }
        loftSurface.push_back(c);
    }
    return 1;
}

bool generateLine(Point &p1, Point &p2, int &numU, Curve &line)
{
    for (double u = 0; u <= 1; u += 1 / (double)(numU - 1))
    {
        Point p;
        for (int j = 0; j < 3; j++)
            p.data[j] = (p1.data[j] * (1 - u)) + (p2.data[j] * u);
        line.push_back(p);
    }
    return 1;
}

bool generateBezier(Point &p1, Point &p2, Point &p3, Point &p4, int &numV, Curve &bezier)
{
    double u = 0;
    for (double u = 0; u <= 1; u += 1 / (double)(numV))
    {
        Point p;
        for (int i = 0; i < 3; i++)
        {
            p.data[i] = (pow((1 - u), 3) * p1.data[i]) + (pow((1 - u), 2) * 3 * u * p2.data[i]) + ((1 - u) * 3 * pow(u, 3) * p2.data[i]) + (pow(u, 3) * p3.data[i]);
        }
        bezier.push_back(p);
    }
    return 1;
}

bool displayGNU(Surface loft)
{
    ofstream fout("gnuScript.plt", ios::out | ios::trunc);
    fout << "set title 'Line Bezier Loft'" << endl;
    fout << "set view equal xyz" << endl;
    fout << "set hidden3d" << endl;
    fout << "set view 1,1,1" << endl;
    fout << "splot 'lineBezierOutput.gnu' with linespoints" << endl;
    fout << endl
         << "pause -9 \"Hit Enter\" " << endl;
    fout.close();
    system("gnuplot gnuScript.plt");
    return true;
}

int main()
{
    Point line_p1(0, 0, 1);
    Point line_p2(10, 10, 1);
    Point bezier_p1(0, 1, 10);
    Point bezier_p2(-1, 5, 10);
    Point bezier_p3(-5, 11, 10);
    Point bezier_p4(10, 9, 10);
    int numU = 20, numV = 20;
    Curve line;
    Curve bezier;
    Surface loftSurface;
    generateLine(line_p1, line_p2, numU, line);
    generateBezier(bezier_p1, bezier_p2, bezier_p3, bezier_p4, numV, bezier);
    surfaceLoft(line, bezier, numV, loftSurface);
    ofstream fout("lineBezierOutput.gnu");
    for (auto item : loftSurface)
    {
        for (auto subItem : item)
            fout << subItem.data[0] << "\t" << subItem.data[1] << "\t" << subItem.data[2] << "\n";
    }
    displayGNU(loftSurface);
    return EXIT_SUCCESS;
}
