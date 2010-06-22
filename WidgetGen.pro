#-------------------------------------------------
#
# Project created by QtCreator 2010-05-05T13:56:52
#
#-------------------------------------------------

QT       += core gui

TARGET = WidgetBuilder
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    renderercreator.cpp \
    widgetcreator.cpp \
    publishercreator.cpp

HEADERS  += mainwindow.h \
    renderercreator.h \
    widgetcreator.h \
    publishercreator.h

FORMS    += mainwindow.ui

RESOURCES += \
    widgetgen.qrc
