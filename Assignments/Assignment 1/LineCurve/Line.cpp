#include <iostream>
#include <fstream>
#include <vector>

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
    Point p1, p2;
    Curve line;
    int numU = 10;
    cout << "Enter Point p1\n";
    cin >> p1.data[0] >> p1.data[1] >> p1.data[2];
    cout << "Enter Point p2\n";
    cin >> p2.data[0] >> p2.data[1] >> p2.data[2];
    if (generateLine(p1, p2, numU, line))
    {
        string outfilename("lineOutput.gnu");
        ofstream fout(outfilename);
        for (auto subItem : line)
            fout << subItem.data[0] << "\t" << subItem.data[1] << "\t" << subItem.data[2] << "\n";
        fout.close();
        if (!displayGNU(outfilename))
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}