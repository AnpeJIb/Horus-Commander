#ifndef CONFIG_H
#define CONFIG_H

#include "generalconfig.h"
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

    static GeneralConfig GENERAL;

private:
    static QList<ConfigModule*> CHILDREN;
};

#endif // CONFIG_H
