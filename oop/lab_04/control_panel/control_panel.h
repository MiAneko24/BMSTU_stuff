#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H
#include <QObject>
#include <QVector>
#include "../constants/consts.h"

enum PanelState
{
    FREE, 
    NEW_TARGET,
    BUSY
};

class ControlPanel : public QObject
{
    Q_OBJECT;

    public:
        explicit ControlPanel(QObject *parent = nullptr);
        
    public slots:
        void reachedFloor(int fl);
        void setNewTarget(int fl);
        void makeFree();

    signals:
        void call(int fl);
        void stayFree();
        void atFloor(int);

    private:
        Direction direction;
        QVector<bool> floor;
        PanelState state;
        int currentFloor;
        int currentTarget;
        int getClosestTarget();
        int getUp();
        int getDown();
};


#endif