#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T13:02:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PredictiveText
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    CharTree.cpp \
    functs.cpp \
    TreeEdit.cpp

HEADERS  += widget.h \
    CharTree.h \
    functs.h \
    main.h \
    TreeEdit.h

FORMS    += widget.ui

RESOURCES +=
