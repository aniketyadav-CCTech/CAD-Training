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
    Point(double x = 0, double y = 0, double z = 0)
    {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
    }
    double data[3];
};
typedef vector<Point> Curve;
typedef vector<Curve> Surface;

bool surfaceLoft(Curve &circle1, Curve &circle2, int &numV, Surface &loftSurface)
{
    if (circle1.size() != circle2.size())
        return 0;
    double deltaV = 1.0 / numV;
    for (double v = 0; v <= 1.0; v += deltaV)
    {
        Curve c;
        c.resize(circle1.size());
        for (int i = 0; i < circle1.size(); i++)
        {
            for (int j = 0; j < 3; j++)
                c[i].data[j] = (circle1[i].data[j] * (1 - v)) + (circle2[i].data[j] * v);
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
        p.data[2] = centrePoint.data[2];
        circle.push_back(p);
    }
    return 1;
}

bool displayGNU()
{
    ofstream fout("gnuScript.plt", ios::out | ios::trunc);
    fout << "set title 'Bottle Loft'" << endl;
    fout << "set view equal xyz" << endl;
    fout << "set hidden3d" << endl;
    fout << "set view ,,.3" << endl;
    fout << "splot 'NeckOutput.gnu' w l,'ChamferOutput.gnu' w l,'MainOutput.gnu' w l,'BaseOutput.gnu' w l" << endl;
    fout << "pause -9 \"Hit Enter\" " << endl;
    fout.close();
    system("gnuplot gnuScript.plt");
    return true;
}

int main()
{
    Curve NeckTop;
    Curve NeckBottom;
    Curve MainTop;
    Curve BaseTop;
    Curve BaseBottom;
    Point centerPoint1(0,0,200);
    Point centerPoint2(0,0,185);
    Point centerPoint3(0,0,170);
    Point centerPoint4(0,0,5);
    Point centerPoint5(0,0,0);
    int numU = 50, numV = 40, numVMain = 200;
    double NeckRadius = 15;
    double MainRadius = 30;
    double BaseRadius = 20;

    Surface NeckLoft;
    Surface ChamferLoft;
    Surface MainLoft;
    Surface BaseLoft;

    generateCircle(centerPoint1, NeckRadius, numU, NeckTop);
    generateCircle(centerPoint2, NeckRadius, numU, NeckBottom);
    generateCircle(centerPoint3, MainRadius, numU, MainTop);
    generateCircle(centerPoint4, MainRadius, numU, BaseTop);
    generateCircle(centerPoint5, BaseRadius, numU, BaseBottom);

    surfaceLoft(NeckTop, NeckBottom, numV, NeckLoft);
    surfaceLoft(NeckBottom, MainTop, numV, ChamferLoft);
    surfaceLoft(MainTop, BaseTop, numVMain, MainLoft);
    surfaceLoft(BaseTop, BaseBottom, numV, BaseLoft);

    ofstream foutNeck("NeckOutput.gnu");
    for (auto item : NeckLoft)
    {
        for (auto subItem : item)
            foutNeck << subItem.data[0] << "\t" << subItem.data[1] << "\t" << subItem.data[2] << "\n";
    }
    ofstream foutChamfer("ChamferOutput.gnu");
    for (auto item : ChamferLoft)
    {
        for (auto subItem : item)
            foutChamfer << subItem.data[0] << "\t" << subItem.data[1] << "\t" << subItem.data[2] << "\n";
    }
    ofstream foutMain("MainOutput.gnu");
    for (auto item : MainLoft)
    {
        for (auto subItem : item)
            foutMain << subItem.data[0] << "\t" << subItem.data[1] << "\t" << subItem.data[2] << "\n";
    }
    ofstream foutBase("BaseOutput.gnu");
    for (auto item : BaseLoft)
    {
        for (auto subItem : item)
            foutBase << subItem.data[0] << "\t" << subItem.data[1] << "\t" << subItem.data[2] << "\n";
    }
    displayGNU();

    return 1;
}
