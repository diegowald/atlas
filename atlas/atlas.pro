#-------------------------------------------------
#
# Project created by QtCreator 2015-01-21T14:46:35
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = atlas
TEMPLATE = app

win32:LIBS += -LC:\boost\lib
else:LIBS += -lboost_system

win32:INCLUDEPATH += C:\boost\boost_1_57_0

win32:LIBS += -LC:\QtProjects\atlas\atlas\3rdparty\mongo\lib
else:LIBS += -L$$PWD/../../mongo-cxx-driver/build/linux2/use-system-boost/ -lmongoclient
#LIBS += -L/home/diego/QtProjects/mongo-cxx-driver/build/linux2/use-system-boost -lmongoclient

win32:INCLUDEPATH += C:\QtProjects\atlas\atlas\3rdparty\mongo\include
else:INCLUDEPATH += $$PWD/../../mongo-cxx-driver/src

win32:DEPENDPATH += C:\QtProjects\atlas\atlas\3rdparty\mongo\include
else:DEPENDPATH += $$PWD/../../mongo-cxx-driver/src


SOURCES += main.cpp\
        mainwindow.cpp \
    widgets/widgetpaciente.cpp \
    dialogs/dialoghistoriaclinica.cpp \
    #widgets/widgetpregunta.cpp \
    model/persona.cpp \
    model/preguntabase.cpp \
    model/historiaclinica.cpp \
    model/preguntasino.cpp \
    model/preguntacheckbox.cpp \
    model/preguntacompuesta.cpp \
    model/preguntatexto.cpp \
    model/preguntacombo.cpp \
    model/preguntacombodoble.cpp \
    model/factory.cpp \
    widgets/wdgtcheckbox.cpp \
    widgets/wdgtcombo.cpp \
    widgets/wdgtcombodoble.cpp \
    widgets/wdgtcompuesto.cpp \
    widgets/wdgtsino.cpp \
    widgets/wdgttexto.cpp \
    widgets/wdgtwithlabel.cpp \
    widgets/customtooltipwidget.cpp \
    db/serializable.cpp \
    dialogs/dlglocalips.cpp \
    dialogs/dlgsetalarma.cpp \
    model/alarma.cpp \
    db/dbmanager.cpp \
    dialogs/dlgedittooltip.cpp \
    dialogs/dialogdbserver.cpp

HEADERS  += mainwindow.h \
    widgets/widgetpaciente.h \
    dialogs/dialoghistoriaclinica.h \
    #widgets/widgetpregunta.h \
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
    model/factory.h \
    widgets/wdgtcheckbox.h \
    widgets/wdgtcombo.h \
    widgets/wdgtcombodoble.h \
    widgets/wdgtcompuesto.h \
    widgets/wdgtsino.h \
    widgets/wdgttexto.h \
    widgets/wdgtwithlabel.h \
    widgets/customtooltipwidget.h \
    db/serializable.h \
    dialogs/dlglocalips.h \
    dialogs/dlgsetalarma.h \
    model/alarma.h \
    db/dbmanager.h \
    dialogs/dlgedittooltip.h \
    dialogs/dialogdbserver.h

FORMS    += mainwindow.ui \
    widgets/widgetpaciente.ui \
    dialogs/dialoghistoriaclinica.ui \
    #widgets/widgetpregunta.ui \
    widgets/wdgtcheckbox.ui \
    widgets/wdgtcombo.ui \
    widgets/wdgtcombodoble.ui \
    widgets/wdgtcompuesto.ui \
    widgets/wdgtsino.ui \
    widgets/wdgttexto.ui \
    widgets/wdgtwithlabel.ui \
    dialogs/dlglocalips.ui \
    dialogs/dlgsetalarma.ui \
    dialogs/dlgedittooltip.ui \
    dialogs/dialogdbserver.ui

