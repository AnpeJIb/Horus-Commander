#ifndef SERVERCOMMANDER_H
#define SERVERCOMMANDER_H

#include "missionmanager.h"
#include "serverprocess.h"
#include "gscommand.h"
#include "gsconsole.h"

namespace SC
{
    extern MissionManager   MSSN;
    extern ServerProcess    SP;
    extern GsCommands       CMD;
    extern GsConsole        CONSOLE;
}

#endif // SERVERCOMMANDER_H
