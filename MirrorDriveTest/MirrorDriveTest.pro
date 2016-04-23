#-------------------------------------------------
#
# Project created by QtCreator 2016-04-21T19:57:26
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = MirrorDriveTest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += testcase

TEMPLATE = app


SOURCES += main.cpp \
    errorhelpertest.cpp

HEADERS += \
    errorhelpertest.h

QT += testlib

# Include the path to the header file include lookup path
INCLUDEPATH += $$PWD/../MirrorDriveLib

# Adds the MirrorDriveLib.lib to the linker
unix:LIBS += -L$$OUT_PWD/../MirrorDriveLib/ -l MirrorDriveLib
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../MirrorDriveLib/release -lMirrorDriveLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../MirrorDriveLib/debug -lMirrorDriveLib
