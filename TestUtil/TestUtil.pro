! include( ../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT -= gui

TARGET = TestUtil
TEMPLATE = lib
CONFIG += staticlib

DESTDIR = $$TEST_UTIL_BUILD_DIR

SOURCES += \
    expected_strings.cpp

HEADERS += \
    expected_strings.h
