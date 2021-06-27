#ifndef QTDRAWERFACTORY_H
#define QTDRAWERFACTORY_H
#include "drawerFactory.h"
#include <QtWidgets/QGraphicsScene>

class QtDrawerFactory : public DrawerFactory
{
    public:
        explicit QtDrawerFactory(QGraphicsScene *new_scene);
        std::shared_ptr<Drawer> createDrawer() override;
        ~QtDrawerFactory() = default;
    
    private:
        QGraphicsScene *scene;
};


#endif