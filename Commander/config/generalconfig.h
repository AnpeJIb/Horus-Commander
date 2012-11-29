#ifndef GENERALCONFIG_H
#define GENERALCONFIG_H

#include "configmodule.h"

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

private:
    void saveLangCode(QDomElement* root, QDomDocument* doc);
    void saveDaemonMode(QDomElement* root, QDomDocument* doc);

    bool loadLangCode(QDomElement* root);
    bool loadDaemonMode(QDomElement* root);

    QString m_langCode;
    bool m_daemonMode;
};

#endif // GENERALCONFIG_H
