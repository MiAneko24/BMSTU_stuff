#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QWidget>
#include <QPainter>
#include "logic.h"

class FigureView : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event);

public:
    FigureView(QWidget *parent, math_model_t &figure);
    math_model_t figure;
    void change_pic();
};

