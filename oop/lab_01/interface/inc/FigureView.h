#ifndef FIGUREVIEW_H
#define FIGUREVIEW_H

#include <QtWidgets/QWidget>
#include <QPainter>
#include "../../logic/inc/logic.h"

class FigureView : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event);

public:
    FigureView(QWidget *parent, changes_params_t params);
    changes_params_t params;
    void change_pic(); 
};

#endif