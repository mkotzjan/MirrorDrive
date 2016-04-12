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
        mainwindow.cpp \
    filehelper.cpp \
    databasehelper.cpp \
    errorhelper.cpp

HEADERS  += mainwindow.h \
    filehelper.h \
    databasehelper.h \
    errorhelper.h

FORMS    += mainwindow.ui

CONFIG += debug
