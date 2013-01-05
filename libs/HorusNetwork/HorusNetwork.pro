! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT -= gui

TEMPLATE = lib

DEFINES += HORUS_NETWORK_LIBRARY

SOURCES += \
    stream_server.cpp \
    stream_server_connection.cpp \
    stream_server_connection_manager.cpp \
    stream_server_echo_connection.cpp \
    stream_server_single_echo_connection_manager.cpp

HEADERS += \
    horus_network_global.h \
    stream_server.h \
    stream_server_connection.h \
    stream_server_connection_manager.h \
    stream_server_echo_connection.h \
    stream_server_single_echo_connection_manager.h

TARGET = $$qtLibraryTarget(HorusNetwork)

VERSION = 0.0.1
DEFINES += LIB_VERSION=\\\"$$VERSION\\\"

LIBS += -lboost_system -lboost_thread
