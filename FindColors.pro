#-------------------------------------------------
#
# Project created by QtCreator 2017-04-07T18:46:45
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FindColors
TEMPLATE = app


SOURCES += main.cpp\
        findcolors.cpp \
    styles.cpp \
    video.cpp

HEADERS  += findcolors.h \
    video.h

FORMS    += findcolors.ui

INCLUDEPATH += /usr/local/include/opencv /usr/local/include/opencv2

LIBS += `pkg-config --cflags --libs opencv`

DISTFILES += \
    Resources/War.jpg
