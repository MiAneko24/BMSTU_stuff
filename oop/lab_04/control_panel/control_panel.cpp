#include "control_panel.h"

ControlPanel::ControlPanel(QObject *parent) : QObject(parent),
                                                        direction(MOTIONLESS),
                                                        floor(AMOUNT_OF_FLOORS, false),
                                                        state(FREE),
                                                        currentFloor(1),
                                                        currentTarget(-1)
{
    QObject::connect(this, SIGNAL(stayFree()), this, SLOT(makeFree()));
    QObject::connect(this, SIGNAL(atFloor(int)), this, SLOT(reachedFloor(int)));
}

void ControlPanel::setNewTarget(int fl)
{
    int old_state = state;
    floor[fl - 1] = true;
    state = NEW_TARGET;
    emit atFloor(currentFloor);
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
    int prev_state = state;
    if (state != FREE)
    {
        if (currentTarget == fl && prev_state != NEW_TARGET)
            floor[fl - 1] = false;
        state = BUSY;
        currentFloor = fl;
        currentTarget = getClosestTarget();
        if (currentTarget != -1)
        {
            Direction new_direction;
            if (currentTarget != currentFloor)
            {
                new_direction = currentTarget > currentFloor ? UP : DOWN;
            }
            else
                new_direction = direction;
            if (new_direction == direction || direction == MOTIONLESS)
            {
                direction = new_direction;
                emit call(currentTarget);
            }
        }
        else
            emit stayFree();
    }
}

void ControlPanel::makeFree()
{
    if (state != NEW_TARGET)
        qDebug("Лифт ожидает на %d этаже", currentFloor);
    state = FREE;
    currentTarget = -1;
    direction = MOTIONLESS;
}