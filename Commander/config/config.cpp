#include "config.h"
#include "file_ext.h"
#include "status_print.h"

#include <QFile>
#include <QDir>
#include <QTextStream>

#define XML_ROOT  "horusConfig"

static QString m_CONFIG_DIR_PATH = QDir::homePath().append(QDir::separator()).append(".horusCommander");
static QString CONFIG_NAME = QString("config").append(FILE_EXT_XML);
static QString m_CONFIG_PATH = QString(m_CONFIG_DIR_PATH).append(QDir::separator()).append(CONFIG_NAME);

GeneralConfig   CONFIG::GENERAL;
LogConfig       CONFIG::LOG;
NetConfig       CONFIG::NET;
WindowConfig    CONFIG::WINDOW;

void CONFIG::INIT()
{
    QDir d;
    if (d.exists(m_CONFIG_DIR_PATH)==false)
        d.mkpath(m_CONFIG_DIR_PATH);
}

void CONFIG::CLEAN_UP()
{
    // TODO:
}

void CONFIG::SAVE()
{
    // TODO:
}

void CONFIG::LOAD()
{
    // TODO:
}

void CONFIG::DEFAULTS()
{
    // TODO:
}

QString CONFIG::DIR_PATH()
{
    return m_CONFIG_DIR_PATH;
}

QString CONFIG::FILE_PATH()
{
    return m_CONFIG_PATH;
}
