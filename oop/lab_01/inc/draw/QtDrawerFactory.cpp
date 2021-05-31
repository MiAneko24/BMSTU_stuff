#include "QtDrawerFactory.h"
#include "QTDrawer.h"

QtDrawerFactory::QtDrawerFactory(QGraphicsScene *new_scene) : scene(new_scene){};

std::shared_ptr<Drawer> QtDrawerFactory::createDrawer()
{
    return std::shared_ptr<Drawer>(new QtDrawer(scene));
}