#ifndef CONFIG_H
#define CONFIG_H

#include "general_config.h"
#include "log_config.h"
#include "window_config.h"
#include "net_config.h"

#include <QList>

namespace CONFIG
{
    void INIT();
    void SAVE();
    void LOAD();
    void DEFAULTS();
    bool IS_CHANGED();

    QString DIR_PATH();
    QString FILE_PATH();

    extern GeneralConfig    GENERAL;
    extern LogConfig        LOG;
    extern NetConfig        NET;
    extern WindowConfig     WINDOW;
}

#endif // CONFIG_H
