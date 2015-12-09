#-------------------------------------------------
#
# Project created by QtCreator 2015-12-09T11:01:41
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = testing
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11
TEMPLATE = app


SOURCES += testing.cpp \
    testpostdescriptor.cpp \
    testfiledescriptor.cpp \
    testnetworkdescriptor.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    testpostdescriptor.h \
    testfiledescriptor.h \
    testnetworkdescriptor.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../NetworkServiceLib/release/ -lNetworkServiceLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../NetworkServiceLib/debug/ -lNetworkServiceLib
else:unix: LIBS += -L$$OUT_PWD/../NetworkServiceLib/ -lNetworkServiceLib

INCLUDEPATH += $$PWD/../NetworkServiceLib
DEPENDPATH += $$PWD/../NetworkServiceLib
