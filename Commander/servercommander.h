#ifndef SERVERCOMMANDER_H
#define SERVERCOMMANDER_H

#include "missionmanager.h"
#include "serverprocess.h"
#include "gscommand.h"
#include "gsconsole.h"
#include "config.h"

#include <QString>

namespace SC
{
    extern MissionManager   MSSN;
    extern ServerProcess    SP;
    extern GsCommands       CMD;
    extern GsConsole        CONSOLE;

    namespace GS
    {
        QString logsDirPath();
    }
}

#endif // SERVERCOMMANDER_H
