#-------------------------------------------------
#
# Project created by QtCreator 2015-12-04T12:56:56
#
#-------------------------------------------------

QT       -= gui

TARGET = NetworkServiceLib
TEMPLATE = lib

CONFIG += c++11

DEFINES += NETWORKSERVICELIB_LIBRARY

SOURCES += \
    server.cpp \
    servicedescriptor.cpp \
    helpers.cpp

HEADERS += \
    servicedescriptor.h \
    networkservice.h \
    postdescriptor.h \
    filedescriptor.h \
    networkdescriptor.h \
    linktable.h \
    myiterator.h \
    server.h \
    application.h \
    helpers.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
