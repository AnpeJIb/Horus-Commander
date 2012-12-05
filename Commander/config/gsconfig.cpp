#include "gsconfig.h"
#include "gspath.h"
#include "gsconfigkey.h"
#include "statusprint.h"
#include "config.h"
#include "file.h"
#include "str.h"

#include <QFile>
#include <QDir>
#include <QObject>

static bool checkConfigPath();
static bool checkPathLogs();

static void setLogging();
static void setLoggingChat();
static void setLoggingConsole();
static void setLoggingFile();

static void setConsoleConnection();
static void setVersionChecking();
static void setServerInfo();
static void setEscapedValue(const char *key, char* value);

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

    if (checkPathLogs()==false)
    {
        STATUS_PRINT::FAIL();
        return false;
    }

    m_settings = new QSettings(SC::GS::PATH::confsPath(), QSettings::IniFormat);

    setLogging();
    setConsoleConnection();
    setVersionChecking();
    setServerInfo();

    m_settings->sync();
    delete m_settings;

    fixBackslashes();

    STATUS_PRINT::DONE();
    return true;
}

bool checkConfigPath()
{
    STATUS_PRINT::NEW(QObject::tr("Checking config path"));

    QString p = SC::GS::PATH::confsPath();
    QFile file(p);

    if (file.exists())
    {
        STATUS_PRINT::DONE();
    } else {
        STATUS_PRINT::ERROR_(QObject::tr("Could not find server's config at path \"%1\"").arg(p));
        STATUS_PRINT::FAIL();
        return false;
    }

    if (file.open(QIODevice::ReadWrite))
        file.close();
    else {
        STATUS_PRINT::ERROR_(QObject::tr("Server config file \"%1\" cannot be opened.").arg(p));
        STATUS_PRINT::FAIL();
        return false;
    }

    return true;
}

bool checkPathLogs()
{
    STATUS_PRINT::NEW(QObject::tr("Checking logs directory path"));

    QString p = SC::GS::PATH::logsAbsolutePath();

    if (QDir(p).exists()==false)
    {
        STATUS_PRINT::DEBUG_(QObject::tr("Creating missing directory"));

        if (QDir().mkdir(p)==false)
        {
            STATUS_PRINT::ERROR_(QObject::tr("Failed to create \"%1\"").arg(p));
            STATUS_PRINT::FAIL();
            return false;
        }
    }

    STATUS_PRINT::DONE();
    return true;
}

void setLogging()
{
    setLoggingChat();
    setLoggingConsole();
    setLoggingFile();
}

void setLoggingChat()
{
    STATUS_PRINT::DEBUG_(QObject::tr("Suppressing logging to chat"));
    m_settings->setValue(GS_CFG_KEY_AUTO_LOG_DETAIL, "0");
}

void setLoggingConsole()
{
    STATUS_PRINT::DEBUG_(QObject::tr("Disabling saving console output to file"));
    m_settings->setValue(GS_CFG_KEY_LOG, GS_CFG_FALSE);
}

void setLoggingFile()
{
    STATUS_PRINT::DEBUG_(QObject::tr("Setting logging output file"));
    m_settings->setValue(GS_CFG_KEY_EVENTLOG, SC::GS::PATH::eventsLogRelativePath());

    STATUS_PRINT::DEBUG_(QObject::tr("Enabling log resetting for every mission"));
    m_settings->setValue(GS_CFG_KEY_EVENTLOG_KEEP, GS_CFG_FALSE);

    STATUS_PRINT::DEBUG_(QObject::tr("Enabling buildings destruction logging"));
    m_settings->setValue(GS_CFG_KEY_EVENTLOG_HOUSE, GS_CFG_TRUE);
}

void setConsoleConnection()
{
    // TODO:
    // STATUS_PRINT::DEBUG_(QObject::tr("Enabling server's console"));
    // m_settings->setValue(GS_CFG_KEY_IP, GS_CONSOLE_PORT);

    STATUS_PRINT::DEBUG_(QObject::tr("Setting console allowed clients list"));
    m_settings->setValue(GS_CFG_KEY_IPS, "127.0.0.1");
}

void setVersionChecking()
{
    STATUS_PRINT::DEBUG_(QObject::tr("Setting client version checking"));
    m_settings->setValue(GS_CFG_KEY_CHECK_RUNTIME, "1");
}

void setServerInfo()
{
    STATUS_PRINT::DEBUG_(QObject::tr("Setting server's name"));
    setEscapedValue(GS_CFG_KEY_SERVER_NAME, CONFIG::GENERAL.serverName().toUtf8().data());


    STATUS_PRINT::DEBUG_(QObject::tr("Setting server's description"));
    setEscapedValue(GS_CFG_KEY_SERVER_DESCR, CONFIG::GENERAL.serverDescr().toUtf8().data());
}

void setEscapedValue(const char* key, char* value)
{
    int dst_len = 1024;
    char dst[dst_len];

    memset(dst, '\0', dst_len);

    STR::escapeUnicode(value, strlen(value), dst, dst_len);
    m_settings->setValue(key, dst);
}

void fixBackslashes()
{
    rmDoubleSymbInFile(SC::GS::PATH::confsPath(), '\\');
}
