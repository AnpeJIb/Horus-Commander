#ifndef COMMONLOGCONFIG_H
#define COMMONLOGCONFIG_H

#include "configmodule.h"
#include <QString>

class CommonLogConfig : public ConfigModule
{
public:
    CommonLogConfig(const QString& XML_ELEM);

    void save(QDomElement* root, QDomDocument* doc);
    void load(QDomElement* root);
    void loadDefaults();

    bool isEnable();
    quint8 level();

    void setEnable(bool value);
    void setLevel(quint8 value);

private:
    QString m_XML_ELEM;
    bool    m_enable;
    quint8  m_level;
};

#endif // COMMONLOGCONFIG_H
