#-------------------------------------------------
#
# Project created by QtCreator 2016-04-21T20:34:50
#
#-------------------------------------------------

QT       += core gui widgets
QT       += sql

TARGET = MirrorDriveLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += mirrordrivelib.cpp \
    filehelper.cpp \
    databasehelper.cpp \
    errorhelper.cpp

HEADERS += mirrordrivelib.h \
    filehelper.h \
    databasehelper.h \
    errorhelper.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
