#include "system_path.h"

#include <QDir>

#include "file_ext.h"

namespace Path { namespace System {

const QString dirName    = ".horusCommander";
const QString configName = "config" FILE_EXT_INI;
const QString dsName     = "data"   FILE_EXT_XML;
const QString logName    = "system" FILE_EXT_LOG;

QString appDataDir()
{
    return QDir::homePath().append(QDir::separator()).append(dirName).append(QDir::separator());
}

QString config()
{
    return appDataDir().append(configName);
}

QString dataSource()
{
    return appDataDir().append(dsName);
}

QString log()
{
    return appDataDir().append(logName);
}

}}
