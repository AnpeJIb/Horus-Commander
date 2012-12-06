#ifndef NET_CONFIG_H
#define NET_CONFIG_H

#include "config_module.h"
#include <QtCore>

#define DEFAULT_ALLOW_CUSTOM_SKINS            true
#define DEFAULT_CHECK_CLIENT_TIME_SPEED       false
#define DEFAULT_CHECK_SERVER_TIME_SPEED       false
#define DEFAULT_CHECK_TIME_SPEED_DIFFERENSE   0.3f
#define DEFAULT_CHECK_TIME_SPEED_INTERVAL     10.0f
#define DEFAULT_CHANNELS_COUNT                32
#define DEFAULT_CHEATER_WARNING_DELAY         10.0f
#define DEFAULT_CHEATER_WARNING_NUM           3
#define DEFAULT_FAR_MAX_LAG_TIME              2.0f
#define DEFAULT_NEAR_MAX_LAG_TIME             1.0f
#define DEFAULT_CLIENT_PORT                   21000
#define DEFAULT_LOCAL_PORT                    20001
#define DEFAULT_LOCAL_IP                      "127.0.0.1"

class NetConfig : public ConfigModule
{
public:
    NetConfig();

    void save(QDomElement* root, QDomDocument* doc);
    void load(QDomElement* root);
    void loadDefaults();

    bool    allowCustomSkins()          {return m_allowCustomSkins;}
    bool    checkClientTimeSpeed()      {return m_checkClientTimeSpeed;}
    bool    checkServerTimeSpeed()      {return m_checkServerTimeSpeed;}
    float   checkTimeSpeedDifferense()  {return m_checkTimeSpeedDifferense;}
    float   checkTimeSpeedInterval()    {return m_checkTimeSpeedInterval;}
    quint8  channelsCount()             {return m_channelsCount;}
    float   cheaterWarningDelay()       {return m_cheaterWarningDelay;}
    quint8  cheaterWarningNum()         {return m_cheaterWarningNum;}
    float   farMaxLagTime()             {return m_farMaxLagTime;}
    float   nearMaxLagTime()            {return m_farMaxLagTime;}
    uint    clientPort()                {return m_clientPort;}
    uint    localPort()                 {return m_localPort;}
    QString localIP() const             {return m_localIP;}

    void setAllowCustomSkins(bool value)            {CFG_SET_VALUE(m_allowCustomSkins,          value)}
    void setCheckClientTimeSpeed(bool value)        {CFG_SET_VALUE(m_checkClientTimeSpeed,      value)}
    void setCheckServerTimeSpeed(bool value)        {CFG_SET_VALUE(m_checkServerTimeSpeed,      value)}
    void setCheckTimeSpeedDifferense(float value)   {CFG_SET_VALUE(m_checkTimeSpeedDifferense,  value)}
    void setCheckTimeSpeedInterval(float value)     {CFG_SET_VALUE(m_checkTimeSpeedInterval,    value)}
    void setChannelsCount(quint8 value)             {CFG_SET_VALUE(m_channelsCount,             value)}
    void setCheaterWarningDelay(float value)        {CFG_SET_VALUE(m_cheaterWarningDelay,       value)}
    void setCheaterWarningNum(quint8 value)         {CFG_SET_VALUE(m_cheaterWarningNum,         value)}
    void setFarMaxLagTime(float value)              {CFG_SET_VALUE(m_farMaxLagTime,             value)}
    void setNearMaxLagTime(float value)             {CFG_SET_VALUE(m_nearMaxLagTime,            value)}
    void setClientPort(uint value)                  {CFG_SET_VALUE(m_clientPort,                value)}
    void setLocalPort(uint value)                   {CFG_SET_VALUE(m_localPort,                 value)}
    void setLocalIP(const QString& value)           {CFG_SET_VALUE(m_localIP,                   value)}

private:
    bool    m_allowCustomSkins;
    bool    m_checkClientTimeSpeed;
    bool    m_checkServerTimeSpeed;
    float   m_checkTimeSpeedDifferense;
    float   m_checkTimeSpeedInterval;
    quint8  m_channelsCount;
    float   m_cheaterWarningDelay;
    quint8  m_cheaterWarningNum;
    float   m_farMaxLagTime;
    float   m_nearMaxLagTime;
    uint    m_clientPort;
    uint    m_localPort;
    QString m_localIP;
};

#endif // NET_CONFIG_H
