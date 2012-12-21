#include "sc_path.h"
#include "file_ext.h"

#include <QDir>

#define DIR_NAME    ".horusCommander"

#define CONFIG_NAME "config" FILE_EXT_XML
#define LOG_NAME    "system" FILE_EXT_LOG

QString SC::PATH::APP_DATA_DIR_PATH()
{
    return QDir::homePath().append(QDir::separator()).append(DIR_NAME);
}

QString SC::PATH::CONFIG_PATH()
{
    return SC::PATH::APP_DATA_DIR_PATH().append(QDir::separator()).append(CONFIG_NAME);
}

QString SC::PATH::LOG_PATH()
{
    return SC::PATH::APP_DATA_DIR_PATH().append(QDir::separator()).append(LOG_NAME);
}
