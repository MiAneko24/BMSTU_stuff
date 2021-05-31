#ifndef QTDRAWER_H
#define QTDRAWER_H
#include "drawer.h"
#include <QtWidgets/QGraphicsScene>

class QtDrawer : public Drawer
{
    public:
        QtDrawer() = delete;
        explicit QtDrawer(QGraphicsScene *new_scene);
        QtDrawer(const QtDrawer &drawer);

        void drawLine(Point &point1, Point &point2) override;
        void clear() override;

    private:
        QGraphicsScene *scene;
};

#endif