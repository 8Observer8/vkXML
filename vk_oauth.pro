#-------------------------------------------------
#
# Project created by QtCreator 2014-02-15T11:09:56
#
#-------------------------------------------------

QT       += core gui webkitwidgets network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vk_oauth
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vkoauth.cpp

HEADERS  += mainwindow.h \
    vkoauth.h

FORMS    += mainwindow.ui
