#ifndef CONSTS_H
#define CONSTS_H

#include <QTimer>

enum Direction {
    DOWN = -1,
    MOTIONLESS,
    UP,
};

enum Times {
    crossFloor = 2500,
    moveDoors = 1500,
    wait = 2000,
};

#define AMOUNT_OF_FLOORS 10

#endif