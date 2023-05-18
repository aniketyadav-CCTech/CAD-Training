#pragma once
#include "IGraphics.h"
#include "OpenGLWrapper.h"

class Point;
class DllExport GraphicsPoint :
    public IGraphics
{
public:
    void display();
    void input();
private:
    Point point;
};

