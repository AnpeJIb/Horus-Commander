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
    ../Commander/config/config.cpp \
    ../Commander/gs_path.cpp \
    ../Commander/sc_path.cpp \
    dao/xml/parameters/model_xml_dao_test.cpp \
    ../Commander/dao/xml/xml_dao.cpp \
    ../Commander/dao/xml/parameters/model_xml_dao.cpp \
    ../Commander/domain/commander_info.cpp \
    ../Commander/domain/belligerent.cpp \
    ../Commander/domain/parameters/scheme.cpp \
    ../Commander/domain/parameters/parameter_value.cpp \
    ../Commander/domain/parameters/model_parameter.cpp \
    ../Commander/domain/parameters/model.cpp \
    ../Commander/dao/xml/parameters/model_parameter_xml_dao.cpp \
    dao/xml/parameters/model_parameter_xml_dao_test.cpp \
    ../Commander/dao/xml/parameters/simple_parameter_xml_dao.cpp \
    dao/xml/parameters/simple_parameter_xml_dao_test.cpp

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
    config/general_config_test.h \
    ../Commander/gs_path.h \
    ../Commander/sc_path.h \
    dao/xml/parameters/model_xml_dao_test.h \
    ../Commander/dao/title_carrier_dao.h \
    ../Commander/dao/kind_carrier_dao.h \
    ../Commander/dao/generic_dao.h \
    ../Commander/dao/parameters/model_dao.h \
    ../Commander/dao/xml/xml_dao.h \
    ../Commander/dao/xml/parameters/model_xml_dao.h \
    ../Commander/domain/title_carrier.h \
    ../Commander/domain/pointF2D.h \
    ../Commander/domain/logical_operation_types.h \
    ../Commander/domain/kind_carrier.h \
    ../Commander/domain/generic_domain.h \
    ../Commander/domain/description_carrier.h \
    ../Commander/domain/commander_info.h \
    ../Commander/domain/code_name_carrier.h \
    ../Commander/domain/belligerent_carrier.h \
    ../Commander/domain/belligerent.h \
    ../Commander/domain/parameters/scheme_carrier.h \
    ../Commander/domain/parameters/scheme.h \
    ../Commander/domain/parameters/parameter_value.h \
    ../Commander/domain/parameters/model_parameter.h \
    ../Commander/domain/parameters/model.h \
    ../Commander/dao/xml/xml_dao_helper.h \
    ../Commander/dao/code_name_carrier_dao.h \
    ../Commander/dao/xml/parameters/model_parameter_xml_dao.h \
    ../Commander/domain/parent_carrier.h \
    ../Commander/dao/parameters/model_parameter_dao.h \
    dao/xml/parameters/model_parameter_xml_dao_test.h \
    ../Commander/domain/parameters/model_carrier.h \
    ../Commander/domain/parameters/simple_parameter.h \
    ../Commander/dao/parameters/model_carrier_dao.h \
    ../Commander/dao/parameters/simple_parameter_dao.h \
    ../Commander/dao/xml/parameters/simple_parameter_xml_dao.h \
    dao/xml/parameters/simple_parameter_xml_dao_test.h \
    ../Commander/domain/parameters/model_parameter_helper.h

INCLUDEPATH += util \
  config \
  dao \
  dao/xml/parameters \
  ../Commander \
  ../Commander/util \
  ../Commander/config \
  ../Commander/domain \
  ../Commander/domain/parameters \
  ../Commander/dao \
  ../Commander/dao/parameters \
  ../Commander/dao/xml \
  ../Commander/dao/xml/parameters

win32 {
    DEFINES += _WIN32_
}

DEFINES += SRCDIR=\\\"$$PWD/\\\"
