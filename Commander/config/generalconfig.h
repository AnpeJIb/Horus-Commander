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

private:
    void saveLangCode(QDomElement* root, QDomDocument* doc);
    void loadLangCode(QDomElement* root);

    QString m_langCode;
};

#endif // GENERALCONFIG_H
