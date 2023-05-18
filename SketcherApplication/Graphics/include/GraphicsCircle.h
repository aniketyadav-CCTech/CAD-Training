#pragma once
#include "IGraphics.h"
class DllExport GraphicsCircle :
    public IGraphics
{
public:
    void display();
    void input();
private:
    Circle circle;
};

