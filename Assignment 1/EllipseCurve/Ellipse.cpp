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
    double rMax, rMin;
    cout << "Enter Center Point\n";
    cin >> centerPoint.data[0] >> centerPoint.data[1] >> centerPoint.data[2];
    cout << "Enter Major and Minor Radius\n";
    cin >> rMax >> rMin;

    if (generateEllipse(centerPoint, rMax, rMin, numU, circle))
    {
        string outfilename = "ellipseOutput.gnu";
        ofstream fout(outfilename, ios::out | ios::trunc);
        for (auto point : circle)
            fout << point.data[0] << "\t" << point.data[1] << "\t" << point.data[2] << "\n";
        fout.close();
        if (!displayGNU(outfilename))
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}