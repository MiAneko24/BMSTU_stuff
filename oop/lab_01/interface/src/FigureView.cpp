#include "../inc/FigureView.h"

FigureView::FigureView(QWidget *parent, changes_params_t params)
    : QWidget(parent)
{    
    this->params = params;
    setMinimumWidth(400);
    setMinimumHeight(400);
}

void FigureView::paintEvent(QPaintEvent *e)
{

    Q_UNUSED(e);
    QPalette pal = palette();

    pal.setColor(QPalette::Background, Qt::white); 
    this->setAutoFillBackground(true); 
    this->setPalette(pal);
    QPainter *painter = new QPainter(this);
    int h = height();
    int w = width();
    painter->setPen(QPen(QBrush("#535353"), 2));
    painter->translate(QPoint(w/2, h/2));

    params.painter = painter;
    params.action = draw_action;

    make_action(params);
    
    params.painter = NULL;
    painter->end();
    delete painter;
}

void FigureView::change_pic()
{
    update();
}