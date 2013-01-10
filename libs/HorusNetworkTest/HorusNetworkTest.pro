! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT       += core testlib
QT       -= gui

TEMPLATE = app
TARGET = HorusNetworkTest
CONFIG   += console
CONFIG   -= app_bundle

DESTDIR = $$NETWORK_LIB_TEST_BUILD_DIR

HORUS_NETWORK_PATH = $$PROJECT_ROOT_DIRECTORY/libs/HorusNetwork
INCLUDEPATH += $$HORUS_NETWORK_PATH
DEPENDPATH += $$HORUS_NETWORK_PATH

LIBS += -L$$NETWORK_LIB_BUILD_DIR -lHorusNetwork
LIBS += $$HORUS_NETWORK_LIBS

HEADERS += \
    single_connectioned_echo_stream_server_test.h

SOURCES += main.cpp \
    single_connectioned_echo_stream_server_test.cpp
