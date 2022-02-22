#include "ElevatorInterface.h"

ElevatorInterface::ElevatorInterface(QWidget *parent)
	: QWidget(parent)
{
	elevator_lbl = new QLabel(tr("Лифт"), this);
	
	btn_1 = new QPushButton("1", this);
	btn_2 = new QPushButton("2", this);
	btn_3 = new QPushButton("3", this);
	btn_4 = new QPushButton("4", this);
	btn_5 = new QPushButton("5", this);
	btn_6 = new QPushButton("6", this);
	btn_7 = new QPushButton("7", this);
	btn_8 = new QPushButton("8", this);
	btn_9 = new QPushButton("9", this);
	btn_10 = new QPushButton("10", this);

	connect(btn_1, SIGNAL(clicked()), this, SLOT(onBtn1Clicked()));
	connect(btn_2, SIGNAL(clicked()), this, SLOT(onBtn2Clicked()));
	connect(btn_3, SIGNAL(clicked()), this, SLOT(onBtn3Clicked()));
	connect(btn_4, SIGNAL(clicked()), this, SLOT(onBtn4Clicked()));
	connect(btn_5, SIGNAL(clicked()), this, SLOT(onBtn5Clicked()));
	connect(btn_6, SIGNAL(clicked()), this, SLOT(onBtn6Clicked()));
	connect(btn_7, SIGNAL(clicked()), this, SLOT(onBtn7Clicked()));
	connect(btn_8, SIGNAL(clicked()), this, SLOT(onBtn8Clicked()));
	connect(btn_9, SIGNAL(clicked()), this, SLOT(onBtn9Clicked()));
	connect(btn_10, SIGNAL(clicked()), this, SLOT(onBtn10Clicked()));
	
	mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	
	mainLayout->addWidget(elevator_lbl, 0, 0, 1, 3);
    mainLayout->addWidget(btn_10, 1, 1);
    mainLayout->addWidget(btn_9, 2, 1);
    mainLayout->addWidget(btn_8, 3, 1);
    mainLayout->addWidget(btn_7, 4, 1);
    mainLayout->addWidget(btn_6, 5, 1);
    mainLayout->addWidget(btn_5, 6, 1);
    mainLayout->addWidget(btn_4, 7, 1);
    mainLayout->addWidget(btn_3, 8, 1);
    mainLayout->addWidget(btn_2, 9, 1);
    mainLayout->addWidget(btn_1, 10, 1);
    setLayout(mainLayout);

	setWindowTitle(tr("Лифт"));
}

ElevatorInterface::~ElevatorInterface()
{
	delete elevator_lbl;

    delete btn_1;
    delete btn_2;
    delete btn_3;
    delete btn_4;
    delete btn_5;
    delete btn_6;
    delete btn_7;
    delete btn_8;
    delete btn_9;
    delete btn_10;
    

	delete mainLayout;
}

void ElevatorInterface::onBtn1Clicked()
{
    qDebug("Лифт вызван на 1 этаж");
    elevator.call(1);
}

void ElevatorInterface::onBtn2Clicked()
{
    qDebug("Лифт вызван на 2 этаж");
    elevator.call(2);
}

void ElevatorInterface::onBtn3Clicked()
{
    qDebug("Лифт вызван на 3 этаж");
    elevator.call(3);
}

void ElevatorInterface::onBtn4Clicked()
{
    qDebug("Лифт вызван на 4 этаж");
    elevator.call(4);
}

void ElevatorInterface::onBtn5Clicked()
{
    qDebug("Лифт вызван на 5 этаж");
    elevator.call(5);
}

void ElevatorInterface::onBtn6Clicked()
{
    qDebug("Лифт вызван на 6 этаж");
    elevator.call(6);
}

void ElevatorInterface::onBtn7Clicked()
{
    qDebug("Лифт вызван на 7 этаж");
    elevator.call(7);
}

void ElevatorInterface::onBtn8Clicked()
{
    qDebug("Лифт вызван на 8 этаж");
    elevator.call(8);
}

void ElevatorInterface::onBtn9Clicked()
{
    qDebug("Лифт вызван на 9 этаж");
    elevator.call(9);
}

void ElevatorInterface::onBtn10Clicked()
{
    qDebug("Лифт вызван на 10 этаж");
    elevator.call(10);
}

