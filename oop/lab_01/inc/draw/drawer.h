#ifndef DRAWER_H
#define DRAWER_H
#include "visitor.h"
#include "../point.hpp"

class Drawer
{
    public:
        virtual void drawLine(Point& point1, Point& point2);
        virtual void clear();
};

#endif