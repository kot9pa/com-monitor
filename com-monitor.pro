#-------------------------------------------------
#
# Project created by QtCreator 2015-10-06T15:09:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = com-monitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    com-monitor.qrc
