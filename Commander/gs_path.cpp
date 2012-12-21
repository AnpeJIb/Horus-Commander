#include "gs_path.h"
#include "config.h"
#include <QDir>

static QString serverLogsDir();

QString serverLogsDir()
{
    return CONFIG::GENERAL.serverPath().append(QDir::separator ()).append(GS_LOGS_SUBDIR_PATH);
}

QString SC::GS::PATH::stdOutPath()
{
    return serverLogsDir().append(QDir::separator ()).append(GS_STDOUT_FILE);
}

QString SC::GS::PATH::stdErrPath()
{
    return serverLogsDir().append(QDir::separator ()).append(GS_STDERR_FILE);
}

QString SC::GS::PATH::exePath()
{
    return CONFIG::GENERAL.serverPath().append(QDir::separator ()).append(GS_SERVER_EXE_FILE);
}

QString SC::GS::PATH::confsPath()
{
    return CONFIG::GENERAL.serverPath().append(QDir::separator ()).append(GS_CFG_FILE);
}

QString SC::GS::PATH::logsAbsolutePath()
{
    return CONFIG::GENERAL.serverPath().append(QDir::separator ()).append(GS_LOGS_SUBDIR_PATH);
}

QString SC::GS::PATH::eventsLogRelativePath()
{
    return QString(GS_LOGS_SUBDIR_PATH).append(QDir::separator ()).append(GS_EVTLOG_FILE);
}

QString SC::GS::PATH::eventsLogAbsolutePath()
{
    return CONFIG::GENERAL.serverPath().append(QDir::separator ()).append(SC::GS::PATH::eventsLogRelativePath());
}
