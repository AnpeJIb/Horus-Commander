#ifndef GENERALCONFIG_H
#define GENERALCONFIG_H

#include "config_module.h"

#define LANG_CODE_EN        "en"
#define LANG_CODE_RU        "ru"

#define DEFAULT_LANG_CODE       LANG_CODE_EN
#define DEFAULT_DEAMON_MODE     false
#define DEFAULT_SERVER_PATH     "../"
#define DEFAULT_SERVER_NAME     "My nice server"
#define DEFAULT_SERVER_DESCR    "This server is really nice"

class GeneralConfig : public ConfigModule
{
public:
    GeneralConfig();

    void save(QDomElement* root, QDomDocument* doc);
    void load(QDomElement* root);
    void loadDefaults();

    QString langCode() const    {return m_langCode;}
    bool    isDaemonMode()      {return m_daemonMode;}
    QString serverPath() const  {return m_serverPath;}
    QString serverName() const  {return m_serverName;}
    QString serverDescr() const {return m_serverDescr;}

    void setLangCode(const QString &value)  {CFG_SET_VALUE(m_langCode,      value)}
    void setDaemonMode(bool value)          {CFG_SET_VALUE(m_daemonMode,    value)}
    void setServerPath(QString value)       {CFG_SET_VALUE(m_serverPath,    value)}
    void setServerName(QString value)       {CFG_SET_VALUE(m_serverName,    value)}
    void setServerDescr(QString value)      {CFG_SET_VALUE(m_serverDescr,   value)}

private:
    void saveServer(QDomElement* root, QDomDocument* doc);
    bool loadServer(QDomElement* root);

    QString m_langCode;
    QString m_serverPath;
    QString m_serverName;
    QString m_serverDescr;
    bool    m_daemonMode;
};

#endif // GENERALCONFIG_H
