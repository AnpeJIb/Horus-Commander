#-------------------------------------------------
#
# Project created by QtCreator 2012-11-27T19:57:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Horus-Commander
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32 {
    DEFINES += _WIN32_
}

CPPFLAGS +=	"--pedantic -Wall -Wno-error=unused-result -Werror -Wfatal-errors -std=gnu99"
