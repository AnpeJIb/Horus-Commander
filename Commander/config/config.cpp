#include "config.h"
#include "sc_path.h"
#include "file_ext.h"
#include "status_print.h"

#include <QFile>
#include <QDir>
#include <QTextStream>

#define XML_ROOT  "horusConfig"

GeneralConfig   CONFIG::GENERAL;
LogConfig       CONFIG::LOG;
NetConfig       CONFIG::NET;
WindowConfig    CONFIG::WINDOW;

void CONFIG::INIT()
{
    QString path = SC::PATH::CONFIG_PATH();
    QDir d;
    if (d.exists(path)==false)
        d.mkpath(path);
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
