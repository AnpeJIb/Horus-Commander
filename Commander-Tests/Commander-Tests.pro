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
    ../Commander/logger/logger.cpp \
    ../Commander/logger/file_logger.cpp \
    ../Commander/util/str.cpp \
    util/file_util.cpp \
    ../Commander/util/file.cpp \
    util/file_test.cpp \
    util/str_test.cpp \
    dao/xml/parameters/model_xml_dao_test.cpp \
    ../Commander/dao/xml/xml_dao.cpp \
    ../Commander/dao/xml/parameters/model_xml_dao.cpp \
    ../Commander/domain/commander_info.cpp \
    ../Commander/domain/belligerent.cpp \
    ../Commander/domain/parameters/scheme.cpp \
    ../Commander/domain/parameters/model_parameter.cpp \
    ../Commander/domain/parameters/model.cpp \
    ../Commander/dao/xml/parameters/model_parameter_xml_dao.cpp \
    dao/xml/parameters/model_parameter_xml_dao_test.cpp \
    ../Commander/dao/xml/parameters/simple_parameter_xml_dao.cpp \
    dao/xml/parameters/simple_parameter_xml_dao_test.cpp \
    ../Commander/dao/xml/parameters/scheme_xml_dao.cpp \
    dao/xml/parameters/scheme_xml_dao_test.cpp \
    ../Commander/dao/xml/parameters/model_parameter_value_xml_dao.cpp \
    dao/xml/parameters/model_parameter_value_xml_dao_test.cpp \
    ../Commander/domain/parameters/model_parameter_value.cpp \
    ../Commander/service/config/primary_config_service.cpp \
    ../Commander/dao/xml/xml_dao_helper.cpp \
    service/config/primary_config_service_test.cpp \
    path/system_path_test.cpp \
    ../Commander/path/system_path.cpp \
    service/config/general_config_service_test.cpp \
    ../Commander/config/general_config.cpp \
    ../Commander/service/config/general_config_service.cpp \
    ../Commander/service/config/window_config_service.cpp \
    ../Commander/service/config/log_config_service.cpp \
    ../Commander/service/config/config_service_base.cpp \
    logger/file_logger_test.cpp \
    logger/foo_logger.cpp \
    logger/logger_tester.cpp \
    ../Commander/service/log_service.cpp \
    service/log_service_test.cpp

HEADERS += \
    ../Commander/logger/logger.h \
    ../Commander/logger/file_logger.h \
    ../Commander/util/str.h \
    util/file_util.h \
    ../Commander/util/file.h \
    util/file_test.h \
    util/str_test.h \
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
    ../Commander/domain/parameters/model_parameter.h \
    ../Commander/domain/parameters/model.h \
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
    ../Commander/domain/parameters/model_parameter_helper.h \
    ../Commander/dao/parameters/scheme_dao.h \
    ../Commander/dao/description_carrier_dao.h \
    ../Commander/domain/parameters/scheme_helper.h \
    ../Commander/dao/xml/parameters/scheme_xml_dao.h \
    dao/xml/parameters/scheme_xml_dao_test.h \
    ../Commander/domain/parameters/model_parameter_value.h \
    ../Commander/dao/xml/title_carrier_xml_dao.h \
    ../Commander/dao/xml/description_carrier_xml_dao.h \
    ../Commander/dao/xml/kind_carrier_xml_dao.h \
    ../Commander/dao/xml/code_name_carrier_xml_dao.h \
    ../Commander/dao/parent_carrier_dao.h \
    ../Commander/dao/xml/parent_carrier_xml_dao.h \
    ../Commander/dao/xml/parameters/model_carrier_xml_dao.h \
    ../Commander/dao/parameters/model_parameter_value_dao.h \
    ../Commander/domain/parameters/model_parameter_value_helper.h \
    ../Commander/dao/parameters/scheme_carrier_dao.h \
    ../Commander/dao/xml/parameters/scheme_carrier_xml_dao.h \
    ../Commander/dao/xml/parameters/model_parameter_value_xml_dao.h \
    dao/xml/parameters/model_parameter_value_xml_dao_test.h \
    ../Commander/dao/xml/xml_dao_helper.h \
    service/config/primary_config_service_test.h \
    path/system_path_test.h \
    ../Commander/path/system_path.h \
    service/config/general_config_service_test.h \
    ../Commander/config/general_config.h \
    ../Commander/service/config/general_config_service.h \
    ../Commander/service/config/window_config_service.h \
    ../Commander/service/config/primary_config_service.h \
    ../Commander/service/config/log_config_service.h \
    ../Commander/service/config/config_service_base.h \
    logger/file_logger_test.h \
    logger/foo_logger.h \
    logger/logger_tester.h \
    ../Commander/service/log_service.h \
    service/log_service_test.h

INCLUDEPATH += util \
  config \
  logger \
  dao \
  dao/xml/parameters \
  service \
  service/config \
  path \
  ../Commander \
  ../Commander/util \
  ../Commander/logger \
  ../Commander/config \
  ../Commander/domain \
  ../Commander/domain/parameters \
  ../Commander/dao \
  ../Commander/dao/parameters \
  ../Commander/dao/xml \
  ../Commander/dao/xml/parameters \
  ../Commander/service \
  ../Commander/service/config \
  ../Commander/path

win32 {
    DEFINES += _WIN32_
}

DEFINES += SRCDIR=\\\"$$PWD/\\\"
