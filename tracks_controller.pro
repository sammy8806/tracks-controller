#-------------------------------------------------
#
# Project created by QtCreator 2017-03-10T14:27:49
#
#-------------------------------------------------

QT       += core gui widgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tracks_controller
TEMPLATE = app

SOURCES += main.cpp\
        maincontroller.cpp \
        mainwindow.cpp \
        serialworker.cpp \
    dspprotocol.cpp \
    dspcontroller.cpp \
    handlerdspprotocol.cpp \
    handlerchinfoprotocol.cpp

HEADERS  += maincontroller.h \
        mainwindow.h \
        serialworker.h \
    dspprotocol.h \
    dspcontroller.h \
    dspprotocolhandler.h \
    handlerdspprotocol.h \
    handlerchinfoprotocol.h

FORMS    += mainwindow.ui
