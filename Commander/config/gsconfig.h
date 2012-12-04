#ifndef GSCONFIG_H
#define GSCONFIG_H

#include <QSettings>

#include "fileext.h"

#define GS_CFG_FILE     "confs" FILE_EXT_INI

namespace SC { namespace GS { namespace CFG {
    bool init();
    bool checkConfigPath();
    QString path();
}}}

#endif // GSCONFIG_H
