#-------------------------------------------------
#
# Project created by QtCreator 2012-11-27T20:27:54
#
#-------------------------------------------------

QT += network xml gui network testlib

TARGET = Horus-Commander-Tests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    ../Commander/util/status_print.cpp \
    ../Commander/util/status_file_logger.cpp \
    ../Commander/util/str.cpp \
    util/file_util.cpp \
    ../Commander/util/file.cpp \
    util/file_test.cpp \
    util/foo_status_printer.cpp \
    util/status_file_logger_test.cpp \
    util/status_print_test.cpp \
    util/status_tester.cpp \
    util/str_test.cpp \
    config/general_config_test.cpp \
    ../Commander/config/config.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../Commander/util/status_print.h \
    ../Commander/util/status_file_logger.h \
    ../Commander/config/general_config.h \
    ../Commander/config/config_module.h \
    ../Commander/config/config.h \
    ../Commander/config/common_log_config.h \
    ../Commander/config/log_config.h \
    ../Commander/config/window_config.h \
    ../Commander/util/str.h \
    util/file_util.h \
    ../Commander/util/file.h \
    util/file_test.h \
    util/foo_status_printer.h \
    util/status_file_logger_test.h \
    util/status_print_test.h \
    util/status_tester.h \
    util/str_test.h \
    ../Commander/config/net_config.h \
    config/general_config_test.h

INCLUDEPATH += util \
  config \
  ../Commander \
  ../Commander/util \
  ../Commander/config

win32 {
    DEFINES += _WIN32_
}
