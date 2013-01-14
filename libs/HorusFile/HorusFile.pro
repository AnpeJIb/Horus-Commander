! include( ../../root.pri ) {
    error( Couldn't find the root.pri file! )
}

QT -= gui

TARGET = HorusFile
TEMPLATE = lib
CONFIG += staticlib

DESTDIR = $$FILE_LIB_BUILD_DIR

VERSION = 1.0.0
DEFINES += LIB_VERSION=\\\"$$VERSION\\\"

SOURCES += \
    file_line_reader.cpp
HEADERS += \
    file_line_reader.h

