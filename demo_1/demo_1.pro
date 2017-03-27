#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T09:32:14
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo_1
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    sv_treeview.cpp \
    sv_deviceswindow.cpp \
    COMMON/sv_settings.cpp \
    COMMON/sv_userlogon.cpp \
    COMMON/sv_dev_brand.cpp \
    COMMON/sv_dev_brands_list.cpp \
    COMMON/sv_dev_class.cpp \
    COMMON/sv_dev_classes_list.cpp \
    COMMON/sv_dev_model.cpp \
    COMMON/sv_dev_models_list.cpp \
    COMMON/sv_device.cpp \
    COMMON/sv_device_list.cpp \
    sv_videoviewwindow.cpp \
    COMMON/sv_ffmpeg.cpp \
    COMMON/tthread.cpp \
    COMMON/sv_plan.cpp \
    sv_zone.cpp \
    sv_zonedraw.cpp \
    COMMON/sv_zone_list.cpp \
    sv_alarmswindow.cpp \
    sv_varstracker.cpp \
    sv_alarmsTreeView.cpp \
    sv_alarmdialog.cpp \
    sv_zoneswindow.cpp \
    COMMON/sv_pgdb.cpp \
    COMMON/log.cpp \
    sv_scud.cpp \
    COMMON/sv_tcpserverclient.cpp \
    COMMON/sv_secondmeter.cpp \
    sv_employee.cpp \
    COMMON/sv_employees_list.cpp \
    sv_archvideoview.cpp \
    sv_archscudview.cpp \
    sv_rls2bitwidget.cpp \
    COMMON/sv_ffmpeg2filesettings.cpp \
    COMMON/sv_rls2bit2filesettings.cpp \
    ../Panel/panel_tcp.cpp \
    sv_blocklogic.cpp

HEADERS  += mainwindow.h \
    sv_treeview.h \
    sv_deviceswindow.h \
    COMMON/sv_settings.h \
    COMMON/sv_userlogon.h \
    COMMON/sv_dev_brand.h \
    COMMON/sv_dev_brands_list.h \
    COMMON/sv_dev_class.h \
    COMMON/sv_dev_classes_list.h \
    COMMON/sv_dev_model.h \
    COMMON/sv_dev_models_list.h \
    COMMON/sv_device.h \
    COMMON/sv_device_list.h \
    COMMON/sql_create_defs.h \
    COMMON/sql_fields_defs.h \
    COMMON/sql_select_defs.h \
    sv_videoviewwindow.h \
    COMMON/sv_ffmpeg.h \
    COMMON/tthread.h \
    COMMON/sv_plan.h \
    sv_zone.h \
    sv_zonedraw.h \
    COMMON/sv_zone_list.h \
    sv_alarmswindow.h \
    sv_varstracker.h \
    sv_alarmsTreeView.h \
    sv_alarmdialog.h \
    sv_zoneswindow.h \
    COMMON/sv_pgdb.h \
    COMMON/log.h \
    sv_scud.h \
    COMMON/sv_tcpserverclient.h \
    COMMON/sv_secondmeter.h \
    sv_employee.h \
    COMMON/sv_employees_list.h \
    sv_archvideoview.h \
    sv_archscudview.h \
    sv_rls2bitwidget.h \
    COMMON/sv_ffmpeg2filesettings.h \
    COMMON/sv_rls2bit2filesettings.h \
    ../Panel/panel_tcp.h \
    sv_blocklogic.h

FORMS    += mainwindow.ui \
    sv_scud.ui \
    sv_employee.ui \
    sv_blocklogic.ui

RESOURCES += \
    res.qrc

unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -lavcodec
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -lavdevice
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -lavfilter
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -lavformat
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -lavutil
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -lpostproc
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -lswresample
unix:!macx|win32: LIBS += -L$$PWD/../../ffmpeg_win32_dev/lib/ -lswscale

INCLUDEPATH += $$PWD/../../ffmpeg_win32_dev/include
DEPENDPATH += $$PWD/../../ffmpeg_win32_dev/include






