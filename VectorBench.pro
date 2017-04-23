#-------------------------------------------------
#
# Project created by QtCreator 2017-04-19T12:23:45
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VectorBench
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    signal.cpp \
    oscillator.cpp \
    oscillatorcontrol.cpp \
    rendervector.cpp

HEADERS  += mainwindow.h \
    signal.h \
    oscillator.h \
    oscillatorcontrol.h \
    rendervector.h

FORMS    += mainwindow.ui
