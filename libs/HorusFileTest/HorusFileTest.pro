! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT += core testlib
QT -= gui

TARGET = HorusFileTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

DESTDIR = $$FILE_LIB_TEST_BUILD_DIR

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
SOURCES += main.cpp \
    file_line_reader_test.cpp

HEADERS += \
    file_line_reader_test.h
