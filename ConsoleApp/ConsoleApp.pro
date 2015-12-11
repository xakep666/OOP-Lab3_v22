TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../NetworkServiceLib/release/ -lNetworkServiceLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../NetworkServiceLib/debug/ -lNetworkServiceLib
else:unix: LIBS += -L$$OUT_PWD/../NetworkServiceLib/ -lNetworkServiceLib

INCLUDEPATH += $$PWD/../NetworkServiceLib
DEPENDPATH += $$PWD/../NetworkServiceLib

HEADERS += \
    menus.h
