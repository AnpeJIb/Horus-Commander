#ifndef COMMONLOGCONFIG_H
#define COMMONLOGCONFIG_H

#include "config_module.h"
#include <QString>

class CommonLogConfig : public ConfigModule
{
public:
    CommonLogConfig(const QString& XML_ELEM);

    void save(QDomElement* root, QDomDocument* doc);
    void load(QDomElement* root);
    void loadDefaults();

    bool isEnable() {return m_enable;}
    quint8 level()  {return m_level;}

    void setEnable(bool value)  {CFG_SET_VALUE(m_enable, value)}
    void setLevel(quint8 value) {CFG_SET_VALUE(m_level, value)}

private:
    QString m_XML_ELEM;
    bool    m_enable;
    quint8  m_level;
};

#endif // COMMONLOGCONFIG_H
