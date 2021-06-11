#include "ElevatorInterface.h"

int main(int argc, char **argv)
{
    QApplication Application(argc, argv);
	ElevatorInterface widget;
	widget.setGeometry(100, 100, 200, 200);
	widget.show();
	
	return Application.exec(); 
}