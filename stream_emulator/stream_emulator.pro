#-------------------------------------------------
#
# Project created by QtCreator 2015-04-07T10:25:22
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stream_emulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mystream.cpp \
    log.cpp

HEADERS  += mainwindow.h \
    mystream.h \
    log.h

FORMS    += mainwindow.ui
