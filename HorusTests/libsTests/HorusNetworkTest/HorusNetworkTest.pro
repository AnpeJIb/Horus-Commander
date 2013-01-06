! include( ../../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT       += core testlib
QT       -= gui

TARGET = HorusNetworkTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \
    single_connectioned_echo_stream_server_test.h

SOURCES += main.cpp \
    single_connectioned_echo_stream_server_test.cpp

INCLUDEPATH += $$PWD/../../../libs/HorusNetwork
DEPENDPATH += $$PWD/../../../libs/HorusNetwork

unix: LIBS += -L$$NETWORK_LIB_BUILD_DIR -lHorusNetwork
unix:LIBS += -lboost_system -lboost_thread
