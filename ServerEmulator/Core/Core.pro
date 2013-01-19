! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT -= gui

TARGET = $$EMULATOR_CORE_TARGET
TEMPLATE = lib
CONFIG += staticlib

DESTDIR = $$EMULATOR_CORE_BUILD_DIR

VERSION = 0.0.1
DEFINES += LIB_VERSION=\\\"$$VERSION\\\"

# Horus Network library dependency
INCLUDEPATH += $$NETWORK_LIB_SRC_DIR
DEPENDPATH += $$NETWORK_LIB_SRC_DIR
LIBS += $$NETWORK_LIB_LD

SOURCES += server_emulator.cpp \
    emulator_connection_manager.cpp \
    input_parser.cpp \
    event_file_logger.cpp \
    pilot_manager.cpp \
    mission_manager.cpp

HEADERS += server_emulator.h \
    emulator_connection_manager.h \
    input_parser.h \
    console_prints_collector.h \
    event_file_logger.h \
    pilot_manager.h \
    mission_manager.h
