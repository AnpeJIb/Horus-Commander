#-------------------------------------------------
#
# Project created by QtCreator 2012-11-27T19:57:53
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Horus-Commander
TEMPLATE = app

INCLUDEPATH += config util

SOURCES += main.cpp\
        mainwindow.cpp \
    util/statusprint.cpp \
    util/statusfilelogger.cpp \
    util/statuswidget.cpp \
    config/configmodule.cpp \
    config/config.cpp \
    config/generalconfig.cpp

HEADERS  += mainwindow.h \
    util/statusprint.h \
    util/statusfilelogger.h \
    util/statuswidget.h \
    config/configmodule.h \
    config/config.h \
    config/generalconfig.h \
    util/fileext.h

FORMS    += mainwindow.ui

win32 {
    DEFINES += _WIN32_
}

CPPFLAGS +=	"--pedantic -Wall -Wno-error=unused-result -Werror -Wfatal-errors -std=gnu99"

RESOURCES += \
    img.qrc

TRANSLATIONS += l10n/ru.ts
