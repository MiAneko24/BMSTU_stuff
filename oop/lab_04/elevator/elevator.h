#ifndef ELEVATOR_H
#define ELEVATOR_h
#include "../control_panel/control_panel.h"
#include "../cabin/cabin.h"

class Elevator : public QObject
{
    Q_OBJECT

    public:
        Elevator();
        void call(int floor);
    
    signals:
        void setTarget(int);

    private:
        ControlPanel panel;
        Cabin cabin;
};


#endif 