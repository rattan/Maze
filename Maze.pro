#-------------------------------------------------
#
# Project created by QtCreator 2016-03-18T08:14:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Maze
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    map.cpp \
    heap.cpp

HEADERS  += dialog.h \
    map.h \
    heap.h

FORMS    += dialog.ui

CONFIG +=c++11
