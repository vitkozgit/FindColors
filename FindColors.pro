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
    video.cpp \
    matrices.cpp \
    interfaceactions.cpp \
    colorCPP/color.cpp \
    colorCPP/hsv.cpp \
    colorCPP/rgb.cpp \
    xypoints.cpp \
    sizesquare.cpp \
    dialogerror.cpp

HEADERS  += findcolors.h \
    video.h \
    matrices.h \
    colorH/color.h \
    colorH/hsv.h \
    colorH/rgb.h \
    xypoints.h \
    sizesquare.h \
    dialogerror.h

FORMS    += findcolors.ui \
    dialogerror.ui

INCLUDEPATH += /usr/local/include/opencv /usr/local/include/opencv2

LIBS += `pkg-config --cflags --libs opencv`

DISTFILES += \
    Resources/War.jpg \
    colors/hsv.rgb \
    README.md
