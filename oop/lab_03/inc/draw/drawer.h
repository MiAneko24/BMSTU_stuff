#ifndef DRAWER_H
#define DRAWER_H
#include "visitor.h"
#include "../base_elems/point.hpp"

class Drawer
{
    public:
        virtual void drawLine(Point& point1, Point& point2) = 0;
        virtual void clear() = 0;
        virtual ~Drawer() = default;
};

#endif