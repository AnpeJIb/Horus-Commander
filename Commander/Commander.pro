#-------------------------------------------------
#
# Project created by QtCreator 2012-11-27T19:57:53
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Horus-Commander
TEMPLATE = app

INCLUDEPATH += config \
  util \
  util/ui \
  logger \
  logger/ui \
  config/ui \
  ui \
  parser \
  path \
  domain \
  domain/territory \
  domain/gameflow \
  domain/parameters \
  dao \
  dao/parameters \
  dao/xml \
  dao/xml/parameters \
  service \
  service/config

SOURCES += main.cpp \
    util/file.cpp \
    util/str.cpp \
    config/ui/named_page.cpp \
    config/ui/uiconfig_module.cpp \
    ui/main_window.cpp \
    domain/belligerent.cpp \
    domain/territory/node.cpp \
    domain/territory/battleground.cpp \
    domain/gameflow/weather_report.cpp \
    domain/parameters/model.cpp \
    domain/parameters/scheme.cpp \
    domain/parameters/model_parameter_value.cpp \
    domain/commander_info.cpp \
    domain/gameflow/mission_set.cpp \
    domain/gameflow/mission_definition.cpp \
    domain/gameflow/mission_cycle.cpp \
    domain/gameflow/mission_execution.cpp \
    dao/xml/xml_dao.cpp \
    dao/xml/parameters/model_xml_dao.cpp \
    dao/xml/parameters/model_parameter_xml_dao.cpp \
    domain/parameters/model_parameter.cpp \
    dao/xml/parameters/simple_parameter_xml_dao.cpp \
    ui/listed_stack.cpp \
    dao/xml/parameters/scheme_xml_dao.cpp \
    dao/xml/xml_dao_helper.cpp \
    service/config/primary_config_service.cpp \
    path/system_path.cpp \
    util/ui/scheme_editor.cpp \
    service/config/general_config_service.cpp \
    config/general_config.cpp \
    dao/xml/parameters/model_parameter_value_xml_dao.cpp \
    config/ui/general_config_page.cpp \
    config/sqlite_connection_string_composer.cpp \
    config/ui/sqlite_connection_string_editor.cpp \
    config/ui/window_config_page.cpp \
    config/ui/primary_config_dialog.cpp \
    service/config/window_config_service.cpp \
    service/config/config_service_base.cpp \
    config/ui/common_log_config_page.cpp \
    config/ui/log_config_page.cpp \
    service/config/log_config_service.cpp \
    logger/file_logger.cpp \
    logger/ui/logger_tree_widget.cpp \
    service/log_service.cpp

HEADERS  += \
    util/file.h \
    util/str.h \
    config/ui/named_page.h \
    config/ui/uiconfig_module.h \
    ui/main_window.h \
    util/file_ext.h \
    domain/generic_domain.h \
    domain/belligerent.h \
    domain/territory/node.h \
    domain/territory/node_carrier.h \
    domain/territory/battleground.h \
    util/bitwise.h \
    domain/gameflow/weather_report.h \
    domain/pointF2D.h \
    domain/belligerent_carrier.h \
    domain/title_carrier.h \
    domain/description_carrier.h \
    domain/code_name_carrier.h \
    domain/parameters/model.h \
    domain/logical_operation_types.h \
    domain/parameters/scheme.h \
    domain/parameters/scheme_carrier.h \
    domain/commander_info.h \
    domain/gameflow/mission_set.h \
    domain/gameflow/mission_definition.h \
    domain/territory/battleground_carrier.h \
    domain/gameflow/mission_cycle.h \
    domain/gameflow/mission_execution.h \
    domain/kind_carrier.h \
    dao/generic_dao.h \
    dao/xml/xml_dao.h \
    dao/title_carrier_dao.h \
    dao/parameters/model_dao.h \
    dao/kind_carrier_dao.h \
    dao/xml/parameters/model_xml_dao.h \
    domain/parent_carrier.h \
    dao/parent_carrier_dao.h \
    domain/parameters/model_parameter.h \
    dao/parameters/model_parameter_dao.h \
    dao/xml/parameters/model_parameter_xml_dao.h \
    domain/parameters/model_carrier.h \
    domain/parameters/simple_parameter.h \
    dao/parameters/simple_parameter_dao.h \
    dao/parameters/model_carrier_dao.h \
    dao/xml/parameters/simple_parameter_xml_dao.h \
    config/ui/primary_config_dialog.h \
    ui/listed_stack.h \
    dao/xml/xml_dao_helper.h \
    domain/parameters/model_parameter_value.h \
    domain/parameters/scheme_helper.h \
    domain/parameters/model_parameter_helper.h \
    domain/parameters/model_parameter_value_helper.h \
    domain/domain_helper.h \
    dao/xml/parameters/scheme_carrier_xml_dao.h \
    dao/xml/parameters/scheme_xml_dao.h \
    service/config/primary_config_service.h \
    path/system_path.h \
    util/ui/scheme_editor.h \
    domain/title_judge.h \
    dao/parameters/scheme_carrier_dao.h \
    dao/parameters/scheme_dao.h \
    dao/parameters/model_parameter_value_dao.h \
    domain/parameters/scheme_judge.h \
    service/config/general_config_service.h \
    config/general_config.h \
    config/ui/general_config_page.h \
    util/string_composer.h \
    config/sqlite_connection_string_composer.h \
    config/ui/db_connection_string_editor.h \
    config/ui/sqlite_connection_string_editor.h \
    config/ui/db_connection_string_editor_factory.h \
    config/ui/window_config_page.h \
    service/config/window_config_service.h \
    config/window_config.h \
    service/config/config_service_base.h \
    config/ui/common_log_config_page.h \
    config/log_config.h \
    config/ui/log_config_page.h \
    service/config/log_config_service.h \
    logger/logger.h \
    logger/file_logger.h \
    logger/ui/logger_tree_widget.h \
    service/log_service.h

FORMS    += \
    ui/main_window.ui \
    config/ui/primary_config_dialog.ui \
    ui/listed_stack.ui \
    util/ui/scheme_editor.ui \
    config/ui/sqlite_connection_string_editor.ui \
    config/ui/general_config_page.ui \
    config/ui/window_config_page.ui \
    config/ui/common_log_config_page.ui \
    config/ui/log_config_page.ui

unix {
    DEFINES += _UNIX_
    DEFINES += DEV_NULL=\\\"/dev/null\\\"

    LIBS    += -lpthread
}

win32 {
    DEFINES += _WIN32_

    LIBS    += -lws2_32

    RC_FILE = qapp.rc

    HEADERS += util/win_proc.h util/winsock_helper.h
    SOURCES += util/win_proc.cpp util/winsock_helper.cpp
}

CPPFLAGS +=	"--pedantic -Wall -Wno-error=unused-result -Werror -Wfatal-errors -std=gnu99"

RESOURCES += \
    img.qrc

TRANSLATIONS += l10n/ru.ts

VERSION = 0.2.2
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
