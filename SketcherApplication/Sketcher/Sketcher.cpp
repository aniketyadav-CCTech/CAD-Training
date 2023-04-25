#include <iostream>

#include"Sketch.h"
#include"Menu.h"

using namespace std;

int main()
{
    Sketch sketch;
    while(true)
    {
        int status = showMenu(sketch);
        if (status == -1)
        {
            break;
        }
    }
    return 0;
}

