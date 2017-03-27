#-------------------------------------------------
#
# Project created by QtCreator 2015-07-05T10:09:58
#
#-------------------------------------------------

QT       += core gui widgets network

CONFIG   += c++11

TARGET = RadarView

TEMPLATE = app


SOURCES += main.cpp \
    glwidget.cpp \
    mainwindow.cpp \
    socketreader.cpp

HEADERS += \
    glwidget.h \
    mainwindow.h \
    socketreader.h
