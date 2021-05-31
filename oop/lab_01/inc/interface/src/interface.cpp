#include "../inc/TransformWidget.h"


int main(int Argc, char *Argv[])
{
	QApplication Application(Argc, Argv);
	TransformWidget widget;
	widget.setGeometry(100, 100, 200, 200);
	widget.show();
	
	return Application.exec(); 
}