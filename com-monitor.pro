#-------------------------------------------------
#
# Project created by QtCreator 2015-10-06T15:09:35
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = com-monitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    console.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    console.h \
    dialog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    console.ui \
    dialog.ui

RESOURCES += \
    com-monitor.qrc

TRANSLATIONS += \
    com-monitor_ru.ts

DISTFILES +=
