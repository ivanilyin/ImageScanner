#-------------------------------------------------
#
# Project created by QtCreator 2012-08-04T14:39:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = thread_images
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagesmodel.cpp \
    imagecreatorthread.cpp

HEADERS  += mainwindow.h \
    imagesmodel.h \
    imagecreatorthread.h

FORMS    += mainwindow.ui
