! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT += core
QT -= gui

TARGET = $$EMULATOR_APP_TARGET
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = $$EMULATOR_APP_BUILD_DIR

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

SOURCES += main.cpp
