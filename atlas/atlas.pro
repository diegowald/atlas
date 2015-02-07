#-------------------------------------------------
#
# Project created by QtCreator 2015-01-21T14:46:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = atlas
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widgets/widgetpaciente.cpp \
    dialogs/dialoghistoriaclinica.cpp \
    widgets/widgetpregunta.cpp

HEADERS  += mainwindow.h \
    widgets/widgetpaciente.h \
    dialogs/dialoghistoriaclinica.h \
    widgets/widgetpregunta.h

FORMS    += mainwindow.ui \
    widgets/widgetpaciente.ui \
    dialogs/dialoghistoriaclinica.ui \
    widgets/widgetpregunta.ui
