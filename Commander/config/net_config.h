#ifndef NET_CONFIG_H
#define NET_CONFIG_H

#include <QtCore>
#include <QList>
#include <QHostAddress>
#include <QNetworkInterface>

#define DEFAULT_ALLOW_CUSTOM_SKINS              true
#define DEFAULT_CHECK_CLIENT_TIME_SPEED         false
#define DEFAULT_CHECK_SERVER_TIME_SPEED         false
#define DEFAULT_CHECK_TIME_SPEED_DIFFERENSE     0.3f
#define DEFAULT_CHECK_TIME_SPEED_INTERVAL       10.0f
#define DEFAULT_CHANNELS_COUNT                  32
#define DEFAULT_CHEATER_WARNING_DELAY           10.0f
#define DEFAULT_CHEATER_WARNING_NUM             3
#define DEFAULT_FAR_MAX_LAG_TIME                2.0f
#define DEFAULT_NEAR_MAX_LAG_TIME               1.0f
#define DEFAULT_CLIENT_PORT                     21000
#define DEFAULT_LOCAL_PORT                      20001
#define DEFAULT_LOCAL_IP                        "127.0.0.1"

class NetConfig
{
public:
    NetConfig(){}

    bool    allowCustomSkins()          {return m_allowCustomSkins;}
    bool    checkClientTimeSpeed()      {return m_checkClientTimeSpeed;}
    bool    checkServerTimeSpeed()      {return m_checkServerTimeSpeed;}
    float   checkTimeSpeedDifferense()  {return m_checkTimeSpeedDifferense;}
    float   checkTimeSpeedInterval()    {return m_checkTimeSpeedInterval;}
    quint8  channelsCount()             {return m_channelsCount;}
    float   cheaterWarningDelay()       {return m_cheaterWarningDelay;}
    quint8  cheaterWarningNum()         {return m_cheaterWarningNum;}
    float   farMaxLagTime()             {return m_farMaxLagTime;}
    float   nearMaxLagTime()            {return m_nearMaxLagTime;}
    uint    clientPort()                {return m_clientPort;}
    uint    localPort()                 {return m_localPort;}
    QString localIP() const             {return m_localIP;}

    QList<QHostAddress> availableAddresses() const {return QNetworkInterface::allAddresses();}

    QString defaultLocalIP() const
    {
        QList<QHostAddress> list = availableAddresses();
        return (list.count()>0)?list.at(0).toString():DEFAULT_LOCAL_IP;
    }

    void setAllowCustomSkins(bool value)            {m_allowCustomSkins=value;}
    void setCheckClientTimeSpeed(bool value)        {m_checkClientTimeSpeed=value;}
    void setCheckServerTimeSpeed(bool value)        {m_checkServerTimeSpeed=value;}
    void setCheckTimeSpeedDifferense(float value)   {m_checkTimeSpeedDifferense=value;}
    void setCheckTimeSpeedInterval(float value)     {m_checkTimeSpeedInterval=value;}
    void setChannelsCount(quint8 value)             {m_channelsCount=value;}
    void setCheaterWarningDelay(float value)        {m_cheaterWarningDelay=value;}
    void setCheaterWarningNum(quint8 value)         {m_cheaterWarningNum=value;}
    void setFarMaxLagTime(float value)              {m_farMaxLagTime=value;}
    void setNearMaxLagTime(float value)             {m_nearMaxLagTime=value;}
    void setClientPort(uint value)                  {m_clientPort=value;}
    void setLocalPort(uint value)                   {m_localPort=value;}
    void setLocalIP(const QString& value)           {m_localIP=value;}

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
