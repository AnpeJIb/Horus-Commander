#include "gsconfig.h"
#include "statusprint.h"
#include "config.h"

#include <QFile>

static void initLogging();
static void initConsoleConnection();
static void initVersionChecking();
static void fixBackslashes();

static QSettings* m_settings;

bool SC::GS::CFG::init()
{
    STATUS_PRINT::NEW(QObject::tr("Initializing game server's config"));

    if (checkConfigPath()==false)
    {
        STATUS_PRINT::FAIL();
        return false;
    }

    m_settings = new QSettings(path(), QSettings::IniFormat);

    initLogging();
    initConsoleConnection();
    initVersionChecking();
    fixBackslashes();

    m_settings->sync();
    delete m_settings;

    STATUS_PRINT::DONE();
    return true;
}

bool SC::GS::CFG::checkConfigPath()
{
    STATUS_PRINT::NEW(QObject::tr("Checking config path"));

    QString p = path();
    QFile file(p);

    if (file.exists())
    {
        STATUS_PRINT::DONE();
    } else {
        STATUS_PRINT::ERROR(QObject::tr("Could not find server's config at path \"%1\"").arg(p));
        STATUS_PRINT::FAIL();
        return false;
    }

    if (file.open(QIODevice::ReadWrite))
        file.close();
    else {
        STATUS_PRINT::ERROR(QObject::tr("Server config file \"%1\" cannot be opened.").arg(p));
        STATUS_PRINT::FAIL();
        return false;
    }

    return true;
}

QString SC::GS::CFG::path()
{
    return CONFIG::GENERAL.serverPath() + PATH_SEP + GS_CFG_FILE;
}

void initLogging()
{
    // TODO:
}

void initConsoleConnection()
{
    // TODO:
}

void initVersionChecking()
{
    // TODO:
}

void fixBackslashes()
{
    // TODO:
}
