#ifndef CONFIG_H
#define CONFIG_H

#include "generalconfig.h"
#include "logconfig.h"
#include "windowconfig.h"
#include <QList>

namespace CONFIG
{
    void INIT();
    void SAVE();
    void LOAD();
    void DEFAULTS();
    bool IS_CHANGED();

    QString PATH();

    extern GeneralConfig    GENERAL;
    extern LogConfig        LOG;
    extern WindowConfig     WINDOW;
}

#endif // CONFIG_H
