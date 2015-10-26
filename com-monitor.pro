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
    settingsdialog.cpp \
    console.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    console.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    console.ui

RESOURCES += \
    com-monitor.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../qt/5.5/Src/led-designer-plugin/release/ -lled-designer-plugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../qt/5.5/Src/led-designer-plugin/debug/ -lled-designer-plugin
else:unix: LIBS += -L$$PWD/../../qt/5.5/Src/led-designer-plugin/ -lled-designer-plugin

INCLUDEPATH += $$PWD/../../qt/5.5/Src/led-designer-plugin/release
DEPENDPATH += $$PWD/../../qt/5.5/Src/led-designer-plugin/release

DISTFILES +=
