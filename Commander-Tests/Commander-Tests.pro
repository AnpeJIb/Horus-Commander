#-------------------------------------------------
#
# Project created by QtCreator 2012-11-27T20:27:54
#
#-------------------------------------------------

QT += network xml gui testlib

TARGET = Horus-Commander-Tests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    footest.cpp \
    main.cpp \
    util/statusprinttest.cpp \
    ../Commander/util/statusprint.cpp \
    util/statusfileloggertest.cpp \
    ../Commander/util/statusfilelogger.cpp \
    util/statustester.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    footest.h \
    util/statusprinttest.h \
    ../Commander/util/statusprint.h \
    util/statusfileloggertest.h \
    ../Commander/util/statusfilelogger.h \
    util/statustester.h

INCLUDEPATH += util \
  ../Commander \
  ../Commander/util

win32 {
    DEFINES += _WIN32_
}
