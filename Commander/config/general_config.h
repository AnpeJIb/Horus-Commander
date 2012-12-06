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

    QString langCode() const;
    void    setLangCode(QString value);
    bool    isDaemonMode();
    void    setDaemonMode(bool value);
    QString serverPath();
    void setServerPath(QString value);
    QString serverName();
    void setServerName(QString value);
    QString serverDescr();
    void setServerDescr(QString value);

private:
    void saveLangCode(QDomElement* root, QDomDocument* doc);
    void saveDaemonMode(QDomElement* root, QDomDocument* doc);
    void saveServer(QDomElement* root, QDomDocument* doc);

    bool loadLangCode(QDomElement* root);
    bool loadDaemonMode(QDomElement* root);
    bool loadServer(QDomElement* root);

    QString m_langCode;
    QString m_serverPath;
    QString m_serverName;
    QString m_serverDescr;
    bool m_daemonMode;
};

#endif // GENERALCONFIG_H
