#include "net_config.h"

#define XML_ELEM                            "net"
#define ALLOW_CUSTOM_SKINS_ELEM             "allowCustomSkins"
#define CHECK_CLIENT_TIME_SPEED_ELEM        "checkClientTimeSpeed"
#define CHECK_SERVER_TIME_SPEED_ELEM        "checkServerTimeSpeed"
#define CHECK_TIME_SPEED_DIFFERENSE_ELEM    "checkTimeSpeedDifferense"
#define CHECK_TIME_SPEED_INTERVAL_ELEM      "checkTimeSpeedInterval"
#define CHANNELS_COUNT_ELEM                 "channelsCount"
#define CHEATER_WARNING_DELAY_ELEM          "cheaterWarningDelay"
#define CHEATER_WARNING_NUM_ELEM            "cheaterWarningNum"
#define FAR_MAX_LAG_TIME_ELEM               "farMaxLagTime"
#define NEAR_MAX_LAG_TIME_ELEM              "nearMaxLagTime"
#define CLIENT_PORT_ELEM                    "clientPort"
#define LOCAL_PORT_ELEM                     "localPort"
#define LOCAL_IP_ELEM                       "localIP"

NetConfig::NetConfig()
{
}

void NetConfig::save(QDomElement *root, QDomDocument *doc)
{
    QDomElement elem = doc->createElement(XML_ELEM);
    root->appendChild(elem);

    appendTextNode(&elem, doc, ALLOW_CUSTOM_SKINS_ELEM,             QString::number(m_allowCustomSkins));
    appendTextNode(&elem, doc, CHECK_CLIENT_TIME_SPEED_ELEM,        QString::number(m_checkClientTimeSpeed));
    appendTextNode(&elem, doc, CHECK_SERVER_TIME_SPEED_ELEM,        QString::number(m_checkServerTimeSpeed));
    appendTextNode(&elem, doc, CHECK_TIME_SPEED_DIFFERENSE_ELEM,    QString::number(m_checkTimeSpeedDifferense));
    appendTextNode(&elem, doc, CHECK_TIME_SPEED_INTERVAL_ELEM,      QString::number(m_checkTimeSpeedInterval));
    appendTextNode(&elem, doc, CHANNELS_COUNT_ELEM,                 QString::number(m_channelsCount));
    appendTextNode(&elem, doc, CHEATER_WARNING_DELAY_ELEM,          QString::number(m_cheaterWarningDelay));
    appendTextNode(&elem, doc, CHEATER_WARNING_NUM_ELEM,            QString::number(m_cheaterWarningNum));
    appendTextNode(&elem, doc, FAR_MAX_LAG_TIME_ELEM,               QString::number(m_farMaxLagTime));
    appendTextNode(&elem, doc, NEAR_MAX_LAG_TIME_ELEM,              QString::number(m_nearMaxLagTime));
    appendTextNode(&elem, doc, CLIENT_PORT_ELEM,                    QString::number(m_clientPort));
    appendTextNode(&elem, doc, LOCAL_PORT_ELEM,                     QString::number(m_localPort));
    appendTextNode(&elem, doc, LOCAL_IP_ELEM,                       m_localIP);

    notChanged();
}

void NetConfig::load(QDomElement *root)
{
    if(root->tagName() != XML_ELEM) return;

    QDomNode n;
    for(n = root->firstChild();
        n.isNull()==false;
        n = n.nextSibling())
    {
        QDomElement e = n.toElement();
        if(e.isNull()) continue;

        if(e.tagName() == ALLOW_CUSTOM_SKINS_ELEM)
            {setAllowCustomSkins(e.text().toInt()>0);           continue;}
        if(e.tagName() == CHECK_CLIENT_TIME_SPEED_ELEM)
            {setCheckClientTimeSpeed(e.text().toInt()>0);       continue;}
        if(e.tagName() == CHECK_SERVER_TIME_SPEED_ELEM)
            {setCheckServerTimeSpeed(e.text().toInt()>0);       continue;}
        if(e.tagName() == CHECK_TIME_SPEED_DIFFERENSE_ELEM)
            {setCheckTimeSpeedDifferense(e.text().toFloat());   continue;}
        if(e.tagName() == CHECK_TIME_SPEED_INTERVAL_ELEM)
            {setCheckTimeSpeedInterval(e.text().toFloat());     continue;}
        if(e.tagName() == CHANNELS_COUNT_ELEM)
            {setChannelsCount(e.text().toInt());                continue;}
        if(e.tagName() == CHEATER_WARNING_DELAY_ELEM)
            {setCheaterWarningDelay(e.text().toFloat());        continue;}
        if(e.tagName() == CHEATER_WARNING_NUM_ELEM)
            {setCheaterWarningNum(e.text().toInt());            continue;}
        if(e.tagName() == FAR_MAX_LAG_TIME_ELEM)
            {setFarMaxLagTime(e.text().toFloat());              continue;}
        if(e.tagName() == NEAR_MAX_LAG_TIME_ELEM)
            {setNearMaxLagTime(e.text().toFloat());             continue;}
        if(e.tagName() == CLIENT_PORT_ELEM)
            {setClientPort(e.text().toInt());                   continue;}
        if(e.tagName() == LOCAL_PORT_ELEM)
            {setLocalPort(e.text().toInt());                    continue;}
        if(e.tagName() == LOCAL_IP_ELEM)
            {setLocalIP(e.text());                              continue;}
    }

    notChanged();
}

void NetConfig::loadDefaults()
{
    setAllowCustomSkins(            DEFAULT_ALLOW_CUSTOM_SKINS);
    setCheckClientTimeSpeed(        DEFAULT_CHECK_CLIENT_TIME_SPEED);
    setCheckServerTimeSpeed(        DEFAULT_CHECK_SERVER_TIME_SPEED);
    setCheckTimeSpeedDifferense(    DEFAULT_CHECK_TIME_SPEED_DIFFERENSE);
    setCheckTimeSpeedInterval(      DEFAULT_CHECK_TIME_SPEED_INTERVAL);
    setChannelsCount(               DEFAULT_CHANNELS_COUNT);
    setCheaterWarningDelay(         DEFAULT_CHEATER_WARNING_DELAY);
    setCheaterWarningNum(           DEFAULT_CHEATER_WARNING_NUM);
    setFarMaxLagTime(               DEFAULT_FAR_MAX_LAG_TIME);
    setNearMaxLagTime(              DEFAULT_NEAR_MAX_LAG_TIME);
    setClientPort(                  DEFAULT_CLIENT_PORT);
    setLocalPort(                   DEFAULT_LOCAL_PORT);
    setLocalIP(                     DEFAULT_LOCAL_IP);
}
