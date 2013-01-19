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
INCLUDEPATH += $$NETWORK_LIB_SRC_DIR
DEPENDPATH += $$NETWORK_LIB_SRC_DIR
LIBS += $$NETWORK_LIB_LD

# Horus File library dependency
INCLUDEPATH += $$FILE_LIB_SRC_DIR
DEPENDPATH += $$FILE_LIB_SRC_DIR
LIBS += $$FILE_LIB_LD

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
