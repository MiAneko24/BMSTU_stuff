#include "TransformWidget.h"


int main ( int lArgc, char * lArgv [ ] )
{
//Создаём объект QApplication, который инициализирует и настраивает оконную программу,
//управляет её выполнением с помощью цикла обработки событий
	QApplication lApplication ( lArgc, lArgv );
	TransformWidget widget;
//	widget.setGeometry();
	widget.show();
	
	return lApplication.exec ( ); //Запускаем программу на выполнение exec() выполняет
//цикл обработки событий. Программа ожидает действия пользователя и выполняет их обработку.
}