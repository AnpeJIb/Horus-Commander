#ifndef COMMON_LOG_CONFIG_H
#define COMMON_LOG_CONFIG_H

#include <QString>

class CommonLogConfig
{
public:
    CommonLogConfig(){}

    bool isEnable() {return m_enable;}
    quint8 level()  {return m_level;}

    void setEnable(bool value)  {m_enable   = value;}
    void setLevel(quint8 value) {m_level    = value;}

private:
    bool    m_enable;
    quint8  m_level;
};

#endif // COMMON_LOG_CONFIG_H
