#-------------------------------------------------
#
# Project created by QtCreator 2015-08-21T04:28:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DrawingTool_ZK
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    circle.cpp \
    line.cpp \
    paintwidget.cpp \
    rect.cpp \
    shape.cpp

HEADERS  += mainwindow.h \
    circle.h \
    line.h \
    paintwidget.h \
    rect.h \
    shape.h
