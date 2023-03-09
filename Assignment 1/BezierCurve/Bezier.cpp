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

bool generatebezier(Point &p1, Point &p2, Point &p3, Point &p4, int &numV, Curve &bezier)
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
    Point p1, p2, p3, p4;
    Curve bezier;
    int numU = 50;
    double radius;
    cout << "Enter Point p1\n";
    cin >> p1.data[0] >> p1.data[1] >> p1.data[2];
    cout << "Enter Point p2\n";
    cin >> p2.data[0] >> p2.data[1] >> p2.data[2];
    cout << "Enter Point p3\n";
    cin >> p3.data[0] >> p3.data[1] >> p3.data[2];
    cout << "Enter Point p4\n";
    cin >> p4.data[0] >> p4.data[1] >> p4.data[2];

    if (generatebezier(p1,p2,p3,p4, numU, bezier))
    {
        string outfilename = "beizerOutput.gnu";
        ofstream fout(outfilename, ios::out | ios::trunc);
        for (auto point : bezier)
            fout << point.data[0] << "\t" << point.data[1] << "\t" << point.data[2] << "\n";
        fout.close();
        if (!displayGNU(outfilename))
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}