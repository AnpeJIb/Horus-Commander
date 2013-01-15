! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT += core testlib
QT -= gui

TARGET = EmulatorCoreTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += SRCDIR=\\\"$$PWD/\\\"

DESTDIR = $$EMULATOR_CORE_TEST_BUILD_DIR

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

# Test Util library dependency
TEST_UTIL_PATH = $$PROJECT_ROOT_DIRECTORY/TestUtil
INCLUDEPATH += $$TEST_UTIL_PATH
DEPENDPATH += $$TEST_UTIL_PATH

LIBS += -L$$TEST_UTIL_BUILD_DIR -lTestUtil

# Headers and sources
SOURCES += \
    main.cpp \
    server_emulator_test.cpp

HEADERS += \
    server_emulator_test.h
