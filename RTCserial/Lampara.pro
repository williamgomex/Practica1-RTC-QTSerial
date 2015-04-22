#-------------------------------------------------
#
# Project created by QtCreator 2015-04-05T16:40:30
#
#-------------------------------------------------

QT       += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Lampara
TEMPLATE = app


SOURCES += main.cpp\
        lampara.cpp \
    qcustomplot.cpp \
    show.cpp

HEADERS  += lampara.h \
    qcustomplot.h \
    show.h

FORMS    += lampara.ui \
    show.ui
