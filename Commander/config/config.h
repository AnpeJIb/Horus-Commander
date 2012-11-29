#ifndef CONFIG_H
#define CONFIG_H

#include "generalconfig.h"
#include "logconfig.h"
#include "windowconfig.h"
#include <QList>

class CONFIG
{
public:
    CONFIG();

    static void SAVE();
    static void LOAD();
    static void DEFAULTS();
    static bool IS_CHANGED();
    static QString PATH();

    static GeneralConfig    GENERAL;
    static LogConfig        LOG;
    static WindowConfig     WINDOW;

private:
    static QList<ConfigModule*> CHILDREN;
};

#endif // CONFIG_H
