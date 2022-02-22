#include "cabin.h"

#include <QDebug>
#include <QString>

Cabin::Cabin(QObject *parent) : QObject(parent),
                                floor(1), 
                                target(-1), 
                                state(cabinFree), 
                                direction(MOTIONLESS) 
{
    motionTimer.setSingleShot(true);
    motionTimer.setInterval(crossFloor);

    qDebug("Лифт ожидает на %d этаже", floor);
    QObject::connect(this, SIGNAL(stop()), this, SLOT(stand()));
    QObject::connect(this, SIGNAL(openDoors()), &doors, SLOT(beginOpening()));
    QObject::connect(this, SIGNAL(freeCabin()), this, SLOT(freedCabin()));
    QObject::connect(&motionTimer, SIGNAL(timeout()), this, SLOT(move()));
    QObject::connect(&doors, SIGNAL(closed()), this, SLOT(freedCabin()));
}

void Cabin::move()
{   
    if (state == stopped)
    {
        return;   
    }
    if (state == moving)
    {
        floor += direction;
    }
    state = moving;
    if (floor == target)
        emit stop();
    else
    {

        qDebug("Проезжаем %d этаж", floor);
        motionTimer.start();
    }
}

void Cabin::stand()
{
    if (state == moving || state == setTarget) 
    {
        qDebug("Лифт находится на %d этаже", floor);
        state = stopped;
        direction = MOTIONLESS;
        emit openDoors();
    }
}

void Cabin::call(int fl)
{
    int prev_state = state;
    if (prev_state == moving)
    {
        floor+=direction;
    }
    state = setTarget;
    target = fl;
    direction = target > floor ? UP : DOWN;
    if (floor == fl && prev_state != moving)
        emit stop();
    else if (prev_state == cabinFree)
        motionTimer.start();
}

void Cabin::freedCabin()
{
    if (state != cabinFree)
    {
        state = cabinFree;
        emit reachTarget(floor);
    }
}