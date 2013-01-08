! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}


QT       += core testlib
QT       -= gui

TARGET = EmulatorCoreTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += SRCDIR=\\\"$$PWD/\\\"

DESTDIR = $$EMULATOR_CORE_TEST_BUILD_DIR

EMULATOR_CORE_PATH = $$PWD/../Core
INCLUDEPATH += $$EMULATOR_CORE_PATH
DEPENDPATH += $$EMULATOR_CORE_PATH

HORUS_NETWORK_PATH = $$PWD/../../libs/HorusNetwork
INCLUDEPATH += $$HORUS_NETWORK_PATH
DEPENDPATH += $$HORUS_NETWORK_PATH

LIBS += -L$$EMULATOR_CORE_BUILD_DIR -lEmulatorCore
LIBS += $$HORUS_NETWORK_LIBS

SOURCES += \
    main.cpp \
    server_emulator_test.cpp

HEADERS += \
    server_emulator_test.h
