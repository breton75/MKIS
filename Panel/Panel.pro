#-------------------------------------------------
#
# Project created by QtCreator 2015-08-24T12:37:10
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Panel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    panel_tcp.cpp

HEADERS  += mainwindow.h \
    panel_tcp.h

FORMS    += mainwindow.ui
