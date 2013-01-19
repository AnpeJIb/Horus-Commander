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
INCLUDEPATH += $$NETWORK_LIB_SRC_DIR
DEPENDPATH += $$NETWORK_LIB_SRC_DIR
LIBS += $$NETWORK_LIB_LD

# Horus File library dependency
INCLUDEPATH += $$FILE_LIB_SRC_DIR
DEPENDPATH += $$FILE_LIB_SRC_DIR
LIBS += $$FILE_LIB_LD

SOURCES += main.cpp
