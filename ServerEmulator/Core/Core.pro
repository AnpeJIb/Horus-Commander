! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT       -= gui

TARGET = EmulatorCore
TEMPLATE = lib
CONFIG += staticlib

DESTDIR = $$EMULATOR_CORE_BUILD_DIR

VERSION = 0.0.1
DEFINES += LIB_VERSION=\\\"$$VERSION\\\"

HORUS_NETWORK_PATH = $$PWD/../../libs/HorusNetwork
INCLUDEPATH += $$HORUS_NETWORK_PATH
DEPENDPATH += $$HORUS_NETWORK_PATH

LIBS += -L$$NETWORK_LIB_BUILD_DIR -lHorusNetwork
LIBS += $$HORUS_NETWORK_LIBS

SOURCES += server_emulator.cpp

HEADERS += server_emulator.h
