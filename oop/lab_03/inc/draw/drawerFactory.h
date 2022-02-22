#ifndef DRAWERFACTORY_H
#define DRAWERFACTORY_H
#include "drawer.h"
#include <memory>

class DrawerFactory
{
    public:
        virtual std::shared_ptr<Drawer> createDrawer() = 0;
        virtual ~DrawerFactory() = default;
};

#endif