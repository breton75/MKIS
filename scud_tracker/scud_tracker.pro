#-------------------------------------------------
#
# Project created by QtCreator 2015-08-14T09:26:21
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scud_tracker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../demo_1/COMMON/log.cpp \
    ../demo_1/COMMON/sv_pgdb.cpp \
    ../demo_1/COMMON/sv_tcpserverclient.cpp \
    ../demo_1/COMMON/sv_userlogon.cpp \
    ../demo_1/COMMON/sv_secondmeter.cpp \
    ../demo_1/COMMON/sv_settings.cpp

HEADERS  += mainwindow.h \
    ../demo_1/COMMON/log.h \
    ../demo_1/COMMON/sql_select_defs.h \
    ../demo_1/COMMON/sv_pgdb.h \
    ../demo_1/COMMON/sv_tcpserverclient.h \
    ../demo_1/COMMON/sv_userlogon.h \
    ../demo_1/COMMON/sv_secondmeter.h \
    ../demo_1/COMMON/sv_settings.h

FORMS    += mainwindow.ui
