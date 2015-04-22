#-------------------------------------------------
#
# Project created by QtCreator 2015-04-19T12:35:36
#
#-------------------------------------------------

QT       += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RTCserial
TEMPLATE = app


SOURCES += main.cpp\
    lampara.cpp \
    show.cpp

HEADERS  += lampara.h \
    show.h

FORMS    += lampara.ui \
    show.ui

SUBDIRS += \
    Lampara.pro
