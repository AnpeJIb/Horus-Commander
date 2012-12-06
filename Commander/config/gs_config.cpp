#include "gs_config.h"
#include "gs_path.h"
#include "gs_config_key.h"
#include "status_print.h"
#include "config.h"
#include "file.h"
#include "str.h"

#include <QFile>
#include <QDir>
#include <QObject>

static bool checkConfigPath();
static bool checkPathLogs();
static void setValues();
static void setEscapedValue(const char *key, char* value);

static QSettings* m_settings;

bool SC::GS::CFG::applyToServer()
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

    QString fPath = SC::GS::PATH::confsPath();

    m_settings = new QSettings(fPath, QSettings::IniFormat);
    setValues();
    m_settings->sync();
    delete m_settings;

    rmDoubleSymbInFile(fPath, '\\');

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

void setValues()
{
    STATUS_PRINT::DEBUG_(QObject::tr("Suppressing logging to chat"));
    m_settings->setValue(GS_CFG_KEY_AUTO_LOG_DETAIL, QString::number(0));

    STATUS_PRINT::DEBUG_(QObject::tr("Disabling saving console output to file"));
    m_settings->setValue(GS_CFG_KEY_LOG, GS_CFG_FALSE);

    STATUS_PRINT::DEBUG_(QObject::tr("Setting logging output file"));
    m_settings->setValue(GS_CFG_KEY_EVENTLOG, SC::GS::PATH::eventsLogRelativePath());

    STATUS_PRINT::DEBUG_(QObject::tr("Enabling log resetting for every mission"));
    m_settings->setValue(GS_CFG_KEY_EVENTLOG_KEEP, GS_CFG_FALSE);

    STATUS_PRINT::DEBUG_(QObject::tr("Enabling buildings destruction logging"));
    m_settings->setValue(GS_CFG_KEY_EVENTLOG_HOUSE, GS_CFG_TRUE);

    STATUS_PRINT::DEBUG_(QObject::tr("Setting console allowed clients list"));
    m_settings->setValue(GS_CFG_KEY_IPS, "127.0.0.1");

    STATUS_PRINT::DEBUG_(QObject::tr("Enabling server's console"));
    m_settings->setValue(GS_CFG_KEY_IP,
                         QString::number(CONFIG::NET.localPort()));

    STATUS_PRINT::DEBUG_(QObject::tr("Setting client port"));
    m_settings->setValue(GS_CFG_KEY_LOCAL_PORT,
                         QString::number(CONFIG::NET.clientPort()));

    STATUS_PRINT::DEBUG_(QObject::tr("Setting maximum channels count"));
    m_settings->setValue(GS_CFG_KEY_SERVER_CHANNELS,
                         QString::number(CONFIG::NET.channelsCount()));

    STATUS_PRINT::DEBUG_(QObject::tr("Setting custom skins parameter"));
    m_settings->setValue(GS_CFG_KEY_SKIN,
                         CONFIG::NET.allowCustomSkins()?GS_CFG_TRUE:GS_CFG_FALSE);

    STATUS_PRINT::DEBUG_(QObject::tr("Setting client time speed check"));
    m_settings->setValue(GS_CFG_KEY_CHECK_CLIENT_TIME_SPEED,
                         CONFIG::NET.checkClientTimeSpeed()?GS_CFG_TRUE:GS_CFG_FALSE);

    STATUS_PRINT::DEBUG_(QObject::tr("Setting server time speed check"));
    m_settings->setValue(GS_CFG_KEY_CHECK_SERVER_TIME_SPEED,
                         CONFIG::NET.checkServerTimeSpeed()?GS_CFG_TRUE:GS_CFG_FALSE);

    STATUS_PRINT::DEBUG_(QObject::tr("Setting time speed differense"));
    m_settings->setValue(GS_CFG_KEY_CHECK_TIME_SPEED_DIFF,
                         QString::number(CONFIG::NET.checkTimeSpeedDifferense()));

    STATUS_PRINT::DEBUG_(QObject::tr("Setting time speed interval"));
    m_settings->setValue(GS_CFG_KEY_CHECK_TIME_SPEED_INTV,
                         QString::number(CONFIG::NET.checkTimeSpeedInterval()));

    STATUS_PRINT::DEBUG_(QObject::tr("Setting cheater warning delay"));
    m_settings->setValue(GS_CFG_KEY_CHEAT_WARN_DELAY,
                         QString::number(CONFIG::NET.cheaterWarningDelay()));

    STATUS_PRINT::DEBUG_(QObject::tr("Setting cheater warnings number"));
    m_settings->setValue(GS_CFG_KEY_CHEAT_WARN_NUM,
                         QString::number(CONFIG::NET.cheaterWarningNum()));

    STATUS_PRINT::DEBUG_(QObject::tr("Setting far max lag time"));
    m_settings->setValue(GS_CFG_KEY_CHEAT_FAR_MAX_LAG_TIME,
                         QString::number(CONFIG::NET.farMaxLagTime()));

    STATUS_PRINT::DEBUG_(QObject::tr("Setting near max lag time"));
    m_settings->setValue(GS_CFG_KEY_CHEAT_NEAR_MAX_LAG_TIME,
                         QString::number(CONFIG::NET.nearMaxLagTime()));

    STATUS_PRINT::DEBUG_(QObject::tr("Setting client version checking"));
    m_settings->setValue(GS_CFG_KEY_CHECK_RUNTIME, QString::number(1));

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
