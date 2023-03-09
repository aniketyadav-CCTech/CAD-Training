#include <iostream>
#include <fstream>
#include <vector>
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

bool generateCircle(Point &centrePoint, double &radius, int &numU, Curve &circle)
{
    double deltatheta = 2 * M_PI / (numU);
    for (double i = 0; i < 2 * M_PI; i += deltatheta)
    {
        Point p;
        p.data[0] = centrePoint.data[0] + radius * cos(i);
        p.data[1] = centrePoint.data[1] + radius * sin(i);
        p.data[2] = centrePoint.data[2];
        circle.push_back(p);
    }
    return true;
}

bool displayGNU(string &filename)
{
    ofstream fout("gnuScript.plt", ios::out | ios::trunc);
    fout << "set title '" << filename << "'" << endl;
    fout << "set view equal xyz" << endl;
    fout << "set view 1,1,1" << endl;
    fout << "splot '" << filename << "' with linespoints" << endl;
    fout << endl
         << "pause -9 \"Hit Enter\" " << endl;
    fout.close();
    system("gnuplot gnuScript.plt");
    return true;
}

int main(int argc, char *argv[])
{
    Point centerPoint;
    Curve circle;
    int numU = 50;
    double radius;
    cout << "Enter Center Point\n";
    cin >> centerPoint.data[0] >> centerPoint.data[1] >> centerPoint.data[2];
    cout << "Enter Radius\n";
    cin >> radius;

    if (generateCircle(centerPoint, radius, numU, circle))
    {
        string outfilename = "circleOutput.gnu";
        ofstream fout(outfilename, ios::out | ios::trunc);
        for (auto point : circle)
            fout << point.data[0] << "\t" << point.data[1] << "\t" << point.data[2] << "\n";
        fout.close();
        if (!displayGNU(outfilename))
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}