#ifndef GSPATH_H
#define GSPATH_H

#include <QString>
#include "file_ext.h"

#define GS_LOGS_SUBDIR_PATH "logs"

#define GS_SERVER_EXE_FILE  "il2server" FILE_EXT_EXE
#define GS_STDOUT_FILE      "stdout"    FILE_EXT_LOG
#define GS_STDERR_FILE      "stderr"    FILE_EXT_LOG
#define GS_EVTLOG_FILE      "events"    FILE_EXT_LOG

#define GS_CFG_FILE         "confs"     FILE_EXT_INI

namespace SC { namespace GS { namespace PATH {

QString stdOutPath();
QString stdErrPath();
QString exePath();
QString confsPath();

QString logsAbsolutePath();
QString eventsLogRelativePath();
QString eventsLogAbsolutePath();

}}}

#endif // GSPATH_H
