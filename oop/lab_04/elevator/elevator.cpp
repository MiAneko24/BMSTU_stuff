#include "elevator.h"

Elevator::Elevator()
{
    QObject::connect(&panel, SIGNAL(call(int)), &cabin, SLOT(call(int)));
    QObject::connect(&cabin, SIGNAL(crossingFloor(int)), &panel, SLOT(passedFloor(int)));
    QObject::connect(&cabin, SIGNAL(reachTarget(int)), &panel, SLOT(reachedFloor(int)));
}

void Elevator::call(int floor)
{
    panel.setNewTarget(floor);
}