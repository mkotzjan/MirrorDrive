#-------------------------------------------------
#
# Project created by QtCreator 2015-09-29T14:19:14
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MirrorDrive
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += debug

# Include the path to the header file include lookup path
INCLUDEPATH += $$PWD/../MirrorDriveLib

# Adds the MirrorDriveLib.lib to the linker
unix:LIBS += -L$$OUT_PWD/../MirrorDriveLib/ -l MirrorDriveLib
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../MirrorDriveLib/release -lMirrorDriveLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../MirrorDriveLib/debug -lMirrorDriveLib
