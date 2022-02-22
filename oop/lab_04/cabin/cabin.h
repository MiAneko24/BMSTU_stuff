#ifndef CABIN_H
#define CABIN_H
#include <QObject>
#include "../constants/consts.h"
#include "../control_panel/control_panel.h"
#include "../elevator_doors/elevator_doors.h"

enum CabinState 
{
    moving,
    setTarget,
    stopped, 
    cabinFree
};

class Cabin : public QObject
{
    Q_OBJECT

    public:
        explicit Cabin(QObject *parent = nullptr);

    public slots: 
        void move();
        void stand();
        void call(int fl);
        void freedCabin();

    signals:
        void freeCabin();
        void reachTarget(int floor);
        void openDoors();
        void stop();
    
    private:
        ElevatorDoors doors;
        int floor;
        int target;
        bool new_target;
        CabinState state;
        Direction direction;
        QTimer motionTimer;
};



#endif