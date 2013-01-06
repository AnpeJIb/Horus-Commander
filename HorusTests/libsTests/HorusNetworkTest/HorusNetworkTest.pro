! include( ../../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT       += core testlib
QT       -= gui

TARGET = HorusNetworkTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

unix:!macx|win32: LIBS += -L$$NETWORK_LIB_BUILD_DIR -lHorusNetwork
LIBS += -lboost_system -lboost_thread

INCLUDEPATH += $$PWD/../../../libs/HorusNetwork
DEPENDPATH += $$PWD/../../../libs/HorusNetwork

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    single_connectioned_echo_stream_server_test.h

SOURCES += main.cpp \
    single_connectioned_echo_stream_server_test.cpp
