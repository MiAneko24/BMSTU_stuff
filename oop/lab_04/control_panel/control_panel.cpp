#include "control_panel.h"

ControlPanel::ControlPanel(QObject *parent) : QObject(parent),
                                                        direction(MOTIONLESS),
                                                        floor(AMOUNT_OF_FLOORS, false),
                                                        state(FREE),
                                                        currentFloor(1),
                                                        currentTarget(-1){};

void ControlPanel::setNewTarget(int fl)
{
    floor[fl - 1] = true;
    currentTarget = getClosestTarget();
    if (currentTarget != -1) 
    {
        if (currentTarget != currentFloor)
            direction = currentTarget > currentFloor ? UP : DOWN;
        emit call(currentTarget);
    }
}

int ControlPanel::getUp()
{
    int target = -1;
    for (int i = currentFloor; target == -1 && i <= AMOUNT_OF_FLOORS; i++)
    {
        if (floor[i - 1])
        {
            target = i;
        }
    }
    return target;
}

int ControlPanel::getDown()
{
    int target = -1;
    for (int i = currentFloor; target == -1 && i >= 1; i--)
        if (floor[i - 1])
        {
            target = i;
        }
    return target;
}

int ControlPanel::getClosestTarget()
{
    int target = -1;
    if (direction == UP)
        target = getUp();
    else if (direction == DOWN)
        target = getDown();
    if (target == -1)
    {
        int target_up = getUp();
        int target_down = getDown();
        if (((target_up - currentFloor) < (currentFloor - target_down) || target_down == -1) && target_up != -1)
        {
            target = target_up;
        }
        else
        {
            target = target_down;
        }
    }
    return target;
}

void ControlPanel::reachedFloor(int fl)
{
    state = FREE;
    currentFloor = fl;
    floor[fl - 1] = false;
    currentTarget = getClosestTarget();
    if (currentTarget != -1)
    {
        if (currentTarget != currentFloor)
            direction = currentTarget > currentFloor ? UP : DOWN;
        emit call(currentTarget);
    }
    else
        direction = MOTIONLESS;
}

void ControlPanel::passedFloor(int fl)
{
    state = BUSY;
    qDebug("Проезжаем %d этаж", fl);
    currentFloor = fl + direction;
}