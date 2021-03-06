! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT -= gui

TARGET = EmulatorCore
TEMPLATE = lib
CONFIG += staticlib

DESTDIR = $$EMULATOR_CORE_BUILD_DIR

VERSION = 0.0.1
DEFINES += LIB_VERSION=\\\"$$VERSION\\\"

HORUS_NETWORK_PATH = $$PROJECT_ROOT_DIRECTORY/libs/HorusNetwork
INCLUDEPATH += $$HORUS_NETWORK_PATH
DEPENDPATH += $$HORUS_NETWORK_PATH

LIBS += -L$$NETWORK_LIB_BUILD_DIR -lHorusNetwork
LIBS += $$HORUS_NETWORK_LIBS

message($$NETWORK_LIB_BUILD_DIR)
message($$LIBS)

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
