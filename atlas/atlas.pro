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
    widgets/widgetpregunta.cpp \
    model/persona.cpp \
    model/preguntabase.cpp \
    model/historiaclinica.cpp \
    model/preguntasino.cpp \
    model/preguntacheckbox.cpp \
    model/preguntacompuesta.cpp \
    model/preguntatexto.cpp \
    model/preguntacombo.cpp \
    model/preguntacombodoble.cpp \
    model/factory.cpp

HEADERS  += mainwindow.h \
    widgets/widgetpaciente.h \
    dialogs/dialoghistoriaclinica.h \
    widgets/widgetpregunta.h \
    model/persona.h \
    model/preguntabase.h \
    model/historiaclinica.h \
    model/preguntasino.h \
    model/preguntacheckbox.h \
    model/preguntacompuesta.h \
    model/preguntatexto.h \
    model/preguntacombo.h \
    model/preguntacombodoble.h \
    model/forward.h \
    model/factory.h

FORMS    += mainwindow.ui \
    widgets/widgetpaciente.ui \
    dialogs/dialoghistoriaclinica.ui \
    widgets/widgetpregunta.ui
