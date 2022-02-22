#ifndef ELEVATORINTERFACE_H
#define ELEVATORINTERFACE_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>
#include "../elevator/elevator.h"

class ElevatorInterface : public QWidget
{
	Q_OBJECT

private slots:
    void onBtn1Clicked();
    void onBtn2Clicked();
    void onBtn3Clicked();
    void onBtn4Clicked();
    void onBtn5Clicked();
    void onBtn6Clicked();
    void onBtn7Clicked();
    void onBtn8Clicked();
    void onBtn9Clicked();
    void onBtn10Clicked();

public: 
	ElevatorInterface(QWidget *parent = nullptr);
	~ElevatorInterface();
	QLabel *elevator_lbl;

	QPushButton *btn_1;
	QPushButton *btn_2;
	QPushButton *btn_3;
	QPushButton *btn_4;
	QPushButton *btn_5;
	QPushButton *btn_6;
	QPushButton *btn_7;
	QPushButton *btn_8;
	QPushButton *btn_9;
	QPushButton *btn_10;

	QGridLayout *mainLayout;
    Elevator elevator;
};

#endif
