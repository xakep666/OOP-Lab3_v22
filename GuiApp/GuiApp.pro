#-------------------------------------------------
#
# Project created by QtCreator 2015-12-12T19:14:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuiApp
TEMPLATE = app

CONFIG += c++11
SOURCES += main.cpp\
        mainwindow.cpp \
    servertable.cpp \
    filemenu.cpp

HEADERS  += mainwindow.h \
    servertable.h \
    filemenu.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../NetworkServiceLib/release/ -lNetworkServiceLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../NetworkServiceLib/debug/ -lNetworkServiceLib
else:unix: LIBS += -L$$OUT_PWD/../NetworkServiceLib/ -lNetworkServiceLib

INCLUDEPATH += $$PWD/../NetworkServiceLib
DEPENDPATH += $$PWD/../NetworkServiceLib
