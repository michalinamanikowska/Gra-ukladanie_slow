QT += core network gui widgets

TARGET = Server
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += debug_and_release

HEADERS += \
    chatserver.h \
    main.h \
    serverworker.h \
    serverwindow.h

SOURCES += \
    chatserver.cpp \
    servermain.cpp \
    serverworker.cpp \
    serverwindow.cpp \
    main.cpp

FORMS += \
    serverwindow.ui


