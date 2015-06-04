#-------------------------------------------------
#
# Project created by QtCreator 2015-05-16T18:18:09
#
#-------------------------------------------------

QT       += core gui serialport
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Splines
TEMPLATE = app


SOURCES += main.cpp\
    MainWindow.cpp \
    AssesmentState.cpp \
    ShapeState.cpp \
    IdleState.cpp \
    EndState.cpp \
    BeginState.cpp

HEADERS  += \
    State.h \
    ShapeState.h \
    AssesmentState.h \
    IdleState.h \
    MainWindow.h \
    EndState.h \
    BeginState.h

FORMS    += \
    MainWindow.ui \
    PositivityWidget.ui \
    ArousalWidget.ui \
    BeginWidget.ui

RESOURCES += \
    pics.qrc
