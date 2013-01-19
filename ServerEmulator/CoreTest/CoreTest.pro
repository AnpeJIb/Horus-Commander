! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT += core testlib
QT -= gui

TARGET = $$EMULATOR_TEST_TARGET
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += SRCDIR=\\\"$$PWD/\\\"

DESTDIR = $$EMULATOR_TEST_BUILD_DIR

# Emulator Core library dependency
INCLUDEPATH += $$EMULATOR_CORE_SRC_DIR
DEPENDPATH += $$EMULATOR_CORE_SRC_DIR
LIBS += $$EMULATOR_CORE_LD

# Horus Network library dependency
INCLUDEPATH += $$NETWORK_LIB_SRC_DIR
DEPENDPATH += $$NETWORK_LIB_SRC_DIR
LIBS += $$NETWORK_LIB_LD

# Horus File library dependency
INCLUDEPATH += $$FILE_LIB_SRC_DIR
DEPENDPATH += $$FILE_LIB_SRC_DIR
LIBS += $$FILE_LIB_LD

# Test Util library dependency
INCLUDEPATH += $$TEST_UTIL_SRC_BIR
DEPENDPATH += $$TEST_UTIL_SRC_BIR
LIBS += $$TEST_UTIL_LIB_LD

# Headers and sources
SOURCES += \
    main.cpp \
    server_emulator_test.cpp

HEADERS += \
    server_emulator_test.h
