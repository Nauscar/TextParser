#-------------------------------------------------
#
# Project created by QtCreator 2013-12-02T09:50:46
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = TextParser
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    applicationui.cpp \
    fileparser.cpp \
    countdown.cpp \
    twofish/TWOFISH.C \
    encryption.cpp

HEADERS += \
    applicationui.h \
    fileparser.h \
    countdown.h \
    delay.h \
    twofish/TABLE.H \
    twofish/platform.h \
    twofish/DEBUG.H \
    twofish/AES.H \
    encryption.h
