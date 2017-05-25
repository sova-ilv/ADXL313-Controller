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
    adxl313.cpp \
    usbserialapp.cpp

HEADERS  += mainwindow.h \
         chartwindow.h \
        ../qcustomplot.h \
    adxl313.h \
    usbserialapp.h


FORMS    += mainwindow.ui \
    chartwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L../StaticFTDIDriver/i386/ -lftd2xx
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../StaticFTDIDriver/i386/ -lftd2xxd

INCLUDEPATH += ../StaticFTDIDriver/i386
DEPENDPATH += ../StaticFTDIDriver/i386
LIBS += ../StaticFTDIDriver/i386/ftd2xx.lib


#win32:CONFIG(release, debug|release): LIBS +="C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc/visa32.lib"

#INCLUDEPATH += "C:/Program Files (x86)/IVI Foundation/VISA/WinNT/Include"
#DEPENDPATH += "C:/Program Files (x86)/IVI Foundation/VISA/WinNT/Include"
#LIBS +="C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc/visa32.lib"

#DISTFILES += Config_settings.xml
