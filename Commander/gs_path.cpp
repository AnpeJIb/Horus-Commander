#include "gs_path.h"
#include "config.h"

static QString logsDir();

QString logsDir()
{
    return CONFIG::GENERAL.serverPath().append(PATH_SEP).append(GS_LOGS_SUBDIR_PATH);
}

QString SC::GS::PATH::stdOutPath()
{
    return logsDir().append(PATH_SEP).append(GS_STDOUT_FILE);
}

QString SC::GS::PATH::stdErrPath()
{
    return logsDir().append(PATH_SEP).append(GS_STDERR_FILE);
}

QString SC::GS::PATH::exePath()
{
    return CONFIG::GENERAL.serverPath().append(PATH_SEP).append(GS_SERVER_EXE_FILE);
}

QString SC::GS::PATH::confsPath()
{
    return CONFIG::GENERAL.serverPath().append(PATH_SEP).append(GS_CFG_FILE);
}

QString SC::GS::PATH::logsAbsolutePath()
{
    return CONFIG::GENERAL.serverPath().append(PATH_SEP).append(GS_LOGS_SUBDIR_PATH);
}

QString SC::GS::PATH::eventsLogRelativePath()
{
    return QString(GS_LOGS_SUBDIR_PATH).append(PATH_SEP).append(GS_EVTLOG_FILE);
}

QString SC::GS::PATH::eventsLogAbsolutePath()
{
    return CONFIG::GENERAL.serverPath().append(PATH_SEP).append(SC::GS::PATH::eventsLogRelativePath());
}
