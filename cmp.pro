#-------------------------------------------------
#
# Project created by QtCreator 2016-10-19T07:08:40
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cmp
TEMPLATE = app

CONFIG += console

SOURCES += main.cpp\
        temp.cpp \
    dftengine.cpp

HEADERS  += temp.h \
    dftengine.h

FORMS    += temp.ui
