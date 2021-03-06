#-------------------------------------------------
#
# Project created by QtCreator 2017-11-17T15:43:04
#
#-------------------------------------------------

QT       += charts
QT       += core gui
QT       += serialport
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialPortTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH +=C:\Python36\include
LIBS += -LEC:\Python36\libs\-l_tkinter\-lpython3\-lpython36


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    xyseriesiodevice.cpp \
    usercombox.cpp \
    touchdtone.cpp

HEADERS += \
        mainwindow.h \
    xyseriesiodevice.h \
    usercombox.h \
    touchstone.h

FORMS += \
        mainwindow.ui
