#-------------------------------------------------
#
# Project created by QtCreator 2017-06-28T00:10:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    reader.cpp \
    obj.cpp \
    errors.cpp \
    facade.cpp \
    comcapsule.cpp \
    transformer.cpp \
    drawer.cpp \
    logger.cpp \
    singletone.cpp \
    mydisplay.cpp \
    camera.cpp \
    math_abstracts.cpp \
    baseobjects.cpp \
    spacesystems.cpp

HEADERS  += mainwindow.h \
    reader.h \
    obj.h \
    errors.h \
    facade.h \
    comcapsule.h \
    transformer.h \
    drawer.h \
    logger.h \
    mydisplay.h \
    camera.h \
    math_abstracts.h \
    baseobjects.h \
    spacesystems.h \
    singletone.h

FORMS    += mainwindow.ui
