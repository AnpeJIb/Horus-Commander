#ifndef LOGCONFIG_H
#define LOGCONFIG_H

#include "config_module.h"
#include "common_log_config.h"

class LogConfig : public ConfigModule
{
public:
    LogConfig();

    void save(QDomElement* root, QDomDocument* doc);
    void load(QDomElement* root);
    void loadDefaults();

    CommonLogConfig* FILE();
    CommonLogConfig* GUI();

private:
    CommonLogConfig* m_FILE;
    CommonLogConfig* m_GUI;
};

#endif // LOGCONFIG_H
