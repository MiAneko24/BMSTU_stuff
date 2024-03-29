######################################################################
# Automatically generated by qmake (3.1) Thu Mar 11 22:47:08 2021
######################################################################

TEMPLATE = app
TARGET = lab_04
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += cabin/cabin.h constants/consts.h control_panel/control_panel.h
HEADERS += elevator/elevator.h elevator_doors/elevator_doors.h interface/ElevatorInterface.h
SOURCES += cabin/cabin.cpp control_panel/control_panel.cpp interface/main.cpp
SOURCES += elevator/elevator.cpp elevator_doors/elevator_doors.cpp interface/ElevatorInterface.cpp

# Указываем тип проекта
TEMPLATE = app # app - Application, прикладная программа
# Используемые модули Qt
QT -= gui # Удаляем из списка модуль gui
QT += widgets
# это означает отказ от использования графического интрефейса,
# то есть - консольную программу
CONFIG += console # Конфигурируем создание консольного проекта
# (нужно только для консольных проектов в Windows, в Linux и Mac OS X не выполняет никаких
действий)
CONFIG -= app_bundle # Предотвращает создание Application bundle в Mac OS X
# (нужно только для консольных проектов в Mac OS X)
TARGET = lab_04.out # Название исполняемого файла
