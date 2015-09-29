#-------------------------------------------------
#
# Project created by QtCreator 2015-09-29T14:19:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MirrorDrive
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filehelper.cpp

HEADERS  += mainwindow.h \
    filehelper.h

FORMS    += mainwindow.ui

CONFIG += debug
