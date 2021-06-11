#include "elevator_doors.h"
#include <QDebug>

ElevatorDoors::ElevatorDoors(QObject *parent) : QObject(parent), state(CLOSED)
{
    openTimer.setSingleShot(true);

    closeTimer.setSingleShot(true);

    stayOpenTimer.setInterval(wait);
    stayOpenTimer.setSingleShot(true);
    
    QObject::connect(&openTimer, SIGNAL(timeout()), this, SLOT(open()));
    QObject::connect(this, SIGNAL(opened()), &stayOpenTimer, SLOT(start()));

    QObject::connect(&stayOpenTimer, SIGNAL(timeout()), this, SLOT(beginClosing()));
    QObject::connect(&closeTimer, SIGNAL(timeout()), this, SLOT(close()));
}

void ElevatorDoors::beginOpening()
{
    if (state == CLOSING || state == CLOSED)
    {
        int prevState = state;
        state = OPENING;
        qDebug("    Двери открываются");
        openTimer.start(moveDoors);
    }
}

void ElevatorDoors::beginClosing()
{
    if (state == OPENING || state == OPENED)
    {
        state = CLOSING;
        qDebug("    Двери закрываются");
        closeTimer.start(moveDoors);
    }
}

void ElevatorDoors::open()
{
    if (state == OPENING)
    {
        state = OPENED;
        qDebug("    Двери открыты");
        emit opened();
    }
}

void ElevatorDoors::close()
{
    if (state == CLOSING || state == CLOSED)
    {
        if (state == CLOSING)
            qDebug("    Двери закрыты");
        state = CLOSED;
        emit closed();
    }
}
