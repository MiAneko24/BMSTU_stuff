#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H
#include <QObject>
#include <QVector>
#include "../constants/consts.h"

enum PanelState
{
    FREE, 
    BUSY
};

class ControlPanel : public QObject
{
    Q_OBJECT;

    public:
        explicit ControlPanel(QObject *parent = nullptr);
        void setNewTarget(int fl);
        
    public slots:
        void reachedFloor(int fl);
        void passedFloor(int fl);

    signals:
        void call(int fl);

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