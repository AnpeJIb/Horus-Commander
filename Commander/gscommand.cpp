#include "gscommand.h"

QString GsCommands::get_GC()
{
    return "GC";
}

QString GsCommands::get_RUN_FILE(QString relativePath)
{
    return QString("f ").append(relativePath);
}

QString GsCommands::get_TIMEOUT(int secondsDelay, QString cmd)
{
    return QString("timeout ").append(QString::number(secondsDelay)).append(" ").append(cmd);
}

QString GsCommands::get_EXIT()
{
    return "exit";
}
