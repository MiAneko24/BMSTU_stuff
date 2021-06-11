#ifndef ELEVATOR_DOORS_H
#define ELEVATOR_DOORS_H
#include <QObject>
#include "../constants/consts.h"

enum DoorsState
{
    OPENING,
    OPENED,
    CLOSING,
    CLOSED
};

class ElevatorDoors : public QObject
{
    Q_OBJECT
    
    public:
        explicit ElevatorDoors(QObject *parent = nullptr);
    
    public slots:
        void beginOpening();
        void beginClosing();
        void close();
    
    signals:
        void opened();
        void closed();

    private:
        DoorsState state;
        QTimer openTimer;
        QTimer closeTimer;
        QTimer stayOpenTimer;

    private slots:
        void open();
};



#endif