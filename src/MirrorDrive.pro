#-------------------------------------------------
#
# Project created by QtCreator 2015-09-23T19:21:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MirrorDrive
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treehelper.cpp

HEADERS  += mainwindow.h \
    treehelper.h

FORMS    += mainwindow.ui

RESOURCES += \
    qtresource.qrc