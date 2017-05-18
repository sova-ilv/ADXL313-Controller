#-------------------------------------------------
#
# Project created by QtCreator 2017-05-12T08:56:13
#
#-------------------------------------------------

QT       += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = EP200
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        chartwindow.cpp \
        ../qcustomplot.cpp \
    adxl313.cpp

HEADERS  += mainwindow.h \
         chartwindow.h \
        ../qcustomplot.h \
    adxl313.h


FORMS    += mainwindow.ui \
    chartwindow.ui
