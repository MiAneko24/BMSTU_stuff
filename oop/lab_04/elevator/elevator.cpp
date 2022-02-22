#include "elevator.h"

Elevator::Elevator()
{
    QObject::connect(&panel, SIGNAL(call(int)), &cabin, SLOT(call(int)));
    // QObject::connect(&cabin, SIGNAL(crossingFloor(int)), &panel, SLOT(passedFloor(int)));
    QObject::connect(&cabin, SIGNAL(reachTarget(int)), &panel, SLOT(reachedFloor(int)));
    QObject::connect(this, SIGNAL(setTarget(int)), &panel, SLOT(setNewTarget(int)));
}

void Elevator::call(int floor)
{
    emit setTarget(floor);
}