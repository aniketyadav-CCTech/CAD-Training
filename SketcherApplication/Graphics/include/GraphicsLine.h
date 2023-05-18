#pragma once
#include "IGraphics.h"
class DllExport GraphicsLine :
    public IGraphics
{
public:
    void display();
    void input();
private:
    Line line;
};

