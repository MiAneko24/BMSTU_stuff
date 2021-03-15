#include "../inc/FigureView.h"

FigureView::FigureView(QWidget *parent, math_model_t &figure)
    : QWidget(parent)
{    
    setMinimumWidth(400);
    setMinimumHeight(400);
    this->figure = figure;
}

void FigureView::paintEvent(QPaintEvent *e)
{

    Q_UNUSED(e);
    QPalette pal = palette();

    pal.setColor(QPalette::Background, Qt::white); 
    this->setAutoFillBackground(true); 
    this->setPalette(pal);
    QPainter painter(this);
 
    painter.setPen(QPen(QBrush("#535353"), 0.5));

    int h = height();
    int w = width();
    painter.translate(QPoint(w/2, h/2));
    for (int i = 0; i < figure.connections_amount; i++)
    {
        painter.drawLine(
            figure.dimensional_coords.matrix[(int)figure.connection.matrix[i][0]][0], 
            figure.dimensional_coords.matrix[(int)figure.connection.matrix[i][0]][1],
            figure.dimensional_coords.matrix[(int)figure.connection.matrix[i][1]][0],
            figure.dimensional_coords.matrix[(int)figure.connection.matrix[i][1]][1]
            );
    }
}

void FigureView::change_pic()
{
    update();
}