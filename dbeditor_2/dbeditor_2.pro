#-------------------------------------------------
#
# Project created by QtCreator 2015-07-08T12:09:29
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dbeditor_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../Common/log.cpp \
    ../../Common/sv_pgdb.cpp \
    ../../Common/sv_settings.cpp \
    ../../Common/sv_userlogon.cpp \
    ../../Common/sv_device.cpp \
    ../../Common/sv_dev_class.cpp \
    ../../Common/sv_dev_brand.cpp \
    ../../Common/sv_dev_brands_list.cpp \
    ../../Common/sv_dev_classes_list.cpp \
    ../../Common/sv_device_list.cpp \
    ../../Common/sv_dev_model.cpp \
    ../../Common/sv_dev_models_list.cpp \
    ../../Common/sv_arch_configurator.cpp \
    ../../Common/sv_arch_data_list.cpp \
    ../../Common/sv_ffmpeg2filesettings.cpp

HEADERS  += mainwindow.h \
    ../../Common/log.h \
    ../../Common/sv_pgdb.h \
    ../../Common/sv_settings.h \
    ../../Common/sv_userlogon.h \
    ../../Common/sv_device.h \
    ../../Common/sv_dev_brands_list.h \
    ../../Common/sv_dev_classes_list.h \
    ../../Common/sv_dev_brand.h \
    ../../Common/sv_dev_class.h \
    ../../Common/sv_device_list.h \
    ../../Common/sv_dev_model.h \
    ../../Common/sv_dev_models_list.h \
    ../../Common/sql_create_defs.h \
    ../../Common/sql_fields_defs.h \
    ../../Common/sql_select_defs.h \
    ../../Common/sv_arch_configurator.h \
    ../../Common/sv_arch_data_list.h \
    ../../Common/sv_ffmpeg2filesettings.h \
    ../../Common/ui_ffmpeg2filesettings.h

FORMS    += mainwindow.ui
