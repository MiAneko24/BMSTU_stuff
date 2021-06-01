#include "QTDrawer.h"

QtDrawer::QtDrawer(QGraphicsScene *new_scene)
{
    scene = new_scene;
}

void QtDrawer::clear()
{
    scene->clear();
}

void QtDrawer::drawLine(Point &point1, Point &point2)
{
    scene->addLine(point1.getX(), point1.getY(), point2.getX(), point2.getY());
}