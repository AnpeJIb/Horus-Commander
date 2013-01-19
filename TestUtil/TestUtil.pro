! include( ../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT -= gui

TARGET = $$TEST_UTIL_LIB_TARGET
TEMPLATE = lib
CONFIG += staticlib

DESTDIR = $$TEST_UTIL_LIB_BUILD_DIR

SOURCES += \
    expected_strings.cpp

HEADERS += \
    expected_strings.h
