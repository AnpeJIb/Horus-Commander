! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT -= gui

TEMPLATE = lib
TARGET = HorusNetwork
CONFIG += staticlib

DESTDIR = $$NETWORK_LIB_BUILD_DIR

VERSION = 1.0.0
DEFINES += LIB_VERSION=\\\"$$VERSION\\\"

LIBS += $$HORUS_NETWORK_LIBS

SOURCES += \
    stream_server.cpp \
    stream_server_connection.cpp \
    stream_server_connection_manager.cpp \
    stream_server_echo_connection.cpp \
    stream_server_single_echo_connection_manager.cpp \
    stream_client.cpp \
    stream_connection.cpp

HEADERS += \
    stream_server.h \
    stream_server_connection.h \
    stream_server_connection_manager.h \
    stream_server_echo_connection.h \
    stream_server_single_echo_connection_manager.h \
    stream_client.h \
    stream_connection.h \
    stream_defaults.h
