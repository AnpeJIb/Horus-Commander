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
  config/ui \
  ui \
  parser \
  domain \
  domain/territory \
  domain/gameflow \
  domain/parameters

SOURCES += main.cpp\
    config/config.cpp \
    util/logs.cpp \
    util/file.cpp \
    util/str.cpp \
    config/ui/config_dialog.cpp \
    config/ui/general_page.cpp \
    config/ui/named_page.cpp \
    config/ui/uiconfig_module.cpp \
    config/common_log_config.cpp \
    config/config_module.cpp \
    config/general_config.cpp \
    config/gs_config.cpp \
    config/log_config.cpp \
    config/window_config.cpp \
    ui/extra_mission_management_dialog.cpp \
    ui/main_window.cpp \
    util/status_file_logger.cpp \
    util/status_print.cpp \
    util/status_widget.cpp \
    gs_command.cpp \
    gs_console.cpp \
    gs_path.cpp \
    gs_scripts.cpp \
    mission_manager.cpp \
    server_commander.cpp \
    server_process.cpp \
    config/ui/net_page.cpp \
    config/net_config.cpp \
    parser/common_parser.cpp \
    parser/console_parser.cpp \
    domain/belligerent.cpp \
    domain/territory/node.cpp \
    domain/territory/battleground.cpp \
    domain/gameflow/weather_report.cpp \
    config/ui/difficulty_page.cpp \
    config/ui/difficulty_subpage.cpp \
    config/ui/difficulty_flight_model_page.cpp \
    config/ui/difficulty_view_page.cpp \
    config/ui/difficulty_map_icons_page.cpp \
    config/ui/difficulty_var_page.cpp \
    config/ui/difficulty_weapons_page.cpp \
    domain/parameters/model.cpp \
    domain/parameters/parameter.cpp \
    domain/parameters/scheme.cpp \
    domain/parameters/parameter_value.cpp \
    domain/commander_info.cpp \
    domain/gameflow/mission_set.cpp \
    domain/gameflow/mission_definition.cpp \
    domain/gameflow/mission_cycle.cpp \
    domain/gameflow/mission_execution.cpp

HEADERS  += \
    config/config.h \
    util/logs.h \
    util/file.h \
    util/str.h \
    config/ui/config_dialog.h \
    config/ui/general_page.h \
    config/ui/named_page.h \
    config/ui/uiconfig_module.h \
    config/common_log_config.h \
    config/config_module.h \
    config/general_config.h \
    config/gs_config.h \
    config/log_config.h \
    config/window_config.h \
    ui/extra_mission_management_dialog.h \
    ui/main_window.h \
    util/file_ext.h \
    util/status_file_logger.h \
    util/status_print.h \
    util/status_widget.h \
    gs_command.h \
    gs_console.h \
    gs_path.h \
    gs_scripts.h \
    mission_manager.h \
    server_commander.h \
    server_process.h \
    config/gs_config_group.h \
    config/gs_config_key.h \
    config/ui/net_page.h \
    config/net_config.h \
    parser/common_parser.h \
    parser/console_parser.h \
    domain/generic_domain.h \
    domain/belligerent.h \
    domain/type_carrier.h \
    domain/territory/node.h \
    domain/territory/node_carrier.h \
    domain/territory/battleground.h \
    util/bitwise.h \
    domain/gameflow/weather_report.h \
    config/ui/difficulty_page.h \
    config/ui/difficulty_subpage.h \
    config/ui/difficulty_flight_model_page.h \
    config/ui/difficulty_view_page.h \
    config/ui/difficulty_map_icons_page.h \
    config/ui/difficulty_var_page.h \
    config/ui/difficulty_weapons_page.h \
    domain/pointF2D.h \
    domain/belligerent_carrier.h \
    domain/title_carrier.h \
    domain/description_carrier.h \
    domain/code_name_carrier.h \
    domain/parameters/model.h \
    domain/parameters/parameter.h \
    domain/logical_operation_types.h \
    domain/parameters/scheme.h \
    domain/parameters/scheme_carrier.h \
    domain/parameters/parameter_value.h \
    domain/commander_info.h \
    domain/gameflow/mission_set.h \
    domain/gameflow/mission_definition.h \
    domain/territory/battleground_carrier.h \
    domain/gameflow/mission_cycle.h \
    domain/gameflow/mission_execution.h

FORMS    += \
    config/ui/config_dialog.ui \
    config/ui/general_page.ui \
    ui/extra_mission_management_dialog.ui \
    ui/main_window.ui \
    config/ui/net_page.ui \
    config/ui/difficulty_page.ui \
    config/ui/difficulty_flight_model_page.ui \
    config/ui/difficulty_view_page.ui \
    config/ui/difficulty_map_icons_page.ui \
    config/ui/difficulty_var_page.ui \
    config/ui/difficulty_weapons_page.ui

DEFINES += PATH_SEP=\\\"/\\\"

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
