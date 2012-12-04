#-------------------------------------------------
#
# Project created by QtCreator 2012-11-27T19:57:53
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Horus-Commander
TEMPLATE = app

INCLUDEPATH += config util config/ui

SOURCES += main.cpp\
        mainwindow.cpp \
    util/statusprint.cpp \
    util/statusfilelogger.cpp \
    util/statuswidget.cpp \
    config/configmodule.cpp \
    config/config.cpp \
    config/generalconfig.cpp \
    config/commonlogconfig.cpp \
    config/logconfig.cpp \
    util/logs.cpp \
    config/windowconfig.cpp \
    extramissionmanagementdialog.cpp \
    servercommander.cpp \
    missionmanager.cpp \
    config/ui/configdialog.cpp \
    config/ui/uiconfigmodule.cpp \
    config/ui/namedpage.cpp \
    config/ui/generalpage.cpp

HEADERS  += mainwindow.h \
    util/statusprint.h \
    util/statusfilelogger.h \
    util/statuswidget.h \
    config/configmodule.h \
    config/config.h \
    config/generalconfig.h \
    util/fileext.h \
    config/commonlogconfig.h \
    config/logconfig.h \
    util/logs.h \
    config/windowconfig.h \
    extramissionmanagementdialog.h \
    servercommander.h \
    missionmanager.h \
    config/ui/configdialog.h \
    config/ui/uiconfigmodule.h \
    config/ui/namedpage.h \
    config/ui/generalpage.h

FORMS    += mainwindow.ui \
    extramissionmanagementdialog.ui \
    config/ui/configdialog.ui \
    config/ui/generalpage.ui

unix {
  DEFINES += _UNIX_
}

win32 {
    DEFINES += _WIN32_
    RC_FILE = qapp.rc
}

CPPFLAGS +=	"--pedantic -Wall -Wno-error=unused-result -Werror -Wfatal-errors -std=gnu99"

RESOURCES += \
    img.qrc

TRANSLATIONS += l10n/ru.ts
