#include "cabin.h"

#include <QDebug>
#include <QString>

Cabin::Cabin(QObject *parent) : QObject(parent),
                                floor(1), 
                                target(-1), 
                                state(waiting), 
                                direction(MOTIONLESS) 
{
    motionTimer.setSingleShot(true);
    motionTimer.setInterval(crossFloor);

    qDebug("Лифт ожидает на %d этаже", floor);
    QObject::connect(this, SIGNAL(stop()), this, SLOT(stand()));
    QObject::connect(this, SIGNAL(prepare()), &doors, SLOT(close()));
    QObject::connect(this, SIGNAL(reachTarget(int)), &doors, SLOT(beginOpening()));

    QObject::connect(&motionTimer, SIGNAL(timeout()), this, SLOT(move()));
    QObject::connect(&doors, SIGNAL(closed()), &motionTimer, SLOT(start()));
}

void Cabin::move()
{   
    if (state == stopped)
    {
        qDebug("Лифт ожидает на %d этаже", floor);
        return;   
    }
    if (state == moving)
    {
        floor += direction;
    }
    state = moving;
    if (floor != target)
    {
        emit crossingFloor(floor);
        motionTimer.start();
    }
    else
    {
        emit stop();
    }
}

void Cabin::stand()
{
    if (state == moving || state == waiting) 
    {
        qDebug("Лифт находится на %d этаже", floor);
        state = stopped;
        direction = MOTIONLESS;
        emit reachTarget(floor);
    }
}

void Cabin::call(int fl)
{
    if (state == stopped)
        state = waiting;
    target = fl;
    direction = target > floor ? UP : DOWN;
    emit prepare();
}
