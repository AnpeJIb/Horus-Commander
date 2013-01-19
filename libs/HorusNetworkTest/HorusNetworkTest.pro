! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT       += core testlib
QT       -= gui

TEMPLATE = app
TARGET = $$NETWORK_TEST_TARGET
CONFIG   += console
CONFIG   -= app_bundle

DESTDIR = $$NETWORK_LIB_TEST_BUILD_DIR

# Horus Network library dependency
INCLUDEPATH += $$NETWORK_LIB_SRC_DIR
DEPENDPATH += $$NETWORK_LIB_SRC_DIR
LIBS += $$NETWORK_LIB_LD

HEADERS += \
    single_connectioned_echo_stream_server_test.h

SOURCES += main.cpp \
    single_connectioned_echo_stream_server_test.cpp
