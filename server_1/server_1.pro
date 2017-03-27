#-------------------------------------------------
#
# Project created by QtCreator 2015-03-06T11:50:29
#
#-------------------------------------------------

QT       += core gui widgets network sql

TARGET = server_1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../Common/log.cpp \
    ../../Common/sv_serverclient.cpp \
    ../../Common/sv_settings.cpp \
    ../../Common/sv_pgdb.cpp \
    userlogon.cpp \
    ../../Common/sv_secondmeter.cpp \
    ../../Common/sv_tcpclient.cpp \
    ../../Common/sv_server.cpp

HEADERS  += mainwindow.h \
    ../../Common/log.h \
    ../../Common/sv_serverclient.h \
    ../../Common/sv_settings.h \
    ../../Common/sv_pgdb.h \
    userlogon.h \
    ../../Common/sv_secondmeter.h \
    ../../Common/sv_tcpclient.h \
    ../../Common/sv_server.h \
    ../../Common/sv_socket_defs.h

FORMS    += mainwindow.ui

