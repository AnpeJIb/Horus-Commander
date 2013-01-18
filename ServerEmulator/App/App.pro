! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT += core
QT -= gui

TARGET = EmulatorApp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = $$EMULATOR_APP_BUILD_DIR

# Emulator Core library dependency
EMULATOR_CORE_PATH = $$PROJECT_ROOT_DIRECTORY/ServerEmulator/Core
INCLUDEPATH += $$EMULATOR_CORE_PATH
DEPENDPATH += $$EMULATOR_CORE_PATH

LIBS += -L$$EMULATOR_CORE_BUILD_DIR -lEmulatorCore

# Horus Network library dependency
HORUS_NETWORK_PATH = $$PROJECT_ROOT_DIRECTORY/libs/HorusNetwork
INCLUDEPATH += $$HORUS_NETWORK_PATH
DEPENDPATH += $$HORUS_NETWORK_PATH

LIBS += -L$$NETWORK_LIB_BUILD_DIR -lHorusNetwork
LIBS += $$HORUS_NETWORK_LIBS

# Horus File library dependency
HORUS_FILE_PATH = $$PROJECT_ROOT_DIRECTORY/libs/HorusFile
INCLUDEPATH += $$HORUS_FILE_PATH
DEPENDPATH += $$HORUS_FILE_PATH

LIBS += -L$$FILE_LIB_BUILD_DIR -lHorusFile

SOURCES += main.cpp
