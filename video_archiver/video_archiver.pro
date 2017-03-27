#-------------------------------------------------
#
# Project created by QtCreator 2015-08-14T09:26:21
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = video_archiver
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    ../demo_1/COMMON/log.cpp \
    ../demo_1/COMMON/sv_pgdb.cpp \
    ../demo_1/COMMON/sv_tcpserverclient.cpp \
    ../demo_1/COMMON/sv_userlogon.cpp \
    ../demo_1/COMMON/sv_secondmeter.cpp \
    ../demo_1/COMMON/sv_settings.cpp \
    ../demo_1/COMMON/sv_ffmpeg2file.cpp \
    ../demo_1/COMMON/sv_ffmpeg2filesettings.cpp

HEADERS  += mainwindow.h \
    ../demo_1/COMMON/log.h \
    ../demo_1/COMMON/sql_select_defs.h \
    ../demo_1/COMMON/sv_pgdb.h \
    ../demo_1/COMMON/sv_tcpserverclient.h \
    ../demo_1/COMMON/sv_userlogon.h \
    ../demo_1/COMMON/sv_secondmeter.h \
    ../demo_1/COMMON/sv_settings.h \
    ../demo_1/COMMON/sv_ffmpeg2file.h \
    ../demo_1/COMMON/sv_ffmpeg2filesettings.h

FORMS    += mainwindow.ui

unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -llibavcodec
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -llibavformat
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -llibswscale
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -lavdevice
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -lavfilter
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -lpostproc
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -lswresample
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -lavutil

INCLUDEPATH += $$PWD/../../ffmpeg_win32_dev/include
DEPENDPATH += $$PWD/../../ffmpeg_win32_dev/include

