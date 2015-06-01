#-------------------------------------------------
#
# Project created by QtCreator 2015-05-16T18:18:09
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Splines
TEMPLATE = app


SOURCES += main.cpp\
    AffectiveSlider.cpp \
    MainWindow.cpp \
    AssesmentState.cpp \
    ShapeState.cpp \
    IdleState.cpp \
    EndState.cpp

HEADERS  += \
    AffectiveSlider.h \
    State.h \
    ShapeState.h \
    AssesmentState.h \
    IdleState.h \
    MainWindow.h \
    EndState.h

FORMS    += \
    MainWindow.ui
