! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT += core testlib
QT -= gui

TARGET = $$FILE_TEST_TARGET
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

DESTDIR = $$FILE_LIB_TEST_BUILD_DIR

# Horus File library dependency
INCLUDEPATH += $$FILE_LIB_SRC_DIR
DEPENDPATH += $$FILE_LIB_SRC_DIR
LIBS += $$FILE_LIB_LD

# Test Util library dependency
INCLUDEPATH += $$TEST_UTIL_SRC_BIR
DEPENDPATH += $$TEST_UTIL_SRC_BIR
LIBS += $$TEST_UTIL_LIB_LD

# Headers and sources
SOURCES += main.cpp \
    file_line_reader_test.cpp

HEADERS += \
    file_line_reader_test.h
