#ifndef LOG_CONFIG_H
#define LOG_CONFIG_H

#include "common_log_config.h"

class LogConfig
{
public:
    LogConfig()
    {
        m_FILE = new CommonLogConfig;
        m_GUI = new CommonLogConfig;
    }

    CommonLogConfig* FILE() {return m_FILE;}
    CommonLogConfig* GUI() {return m_GUI;}

private:
    CommonLogConfig* m_FILE;
    CommonLogConfig* m_GUI;
};

#endif // LOG_CONFIG_H
