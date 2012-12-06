#ifndef SERVERCOMMANDER_H
#define SERVERCOMMANDER_H

#include "mission_manager.h"
#include "server_process.h"
#include "gs_command.h"
#include "gs_console.h"
#include "config.h"

namespace SC
{
    extern MissionManager   MSSN;
    extern ServerProcess    SP;
    extern GsCommands       CMD;
    extern GsConsole        CONSOLE;
}

#endif // SERVERCOMMANDER_H
