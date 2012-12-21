#ifndef SERVER_COMMANDER_H
#define SERVER_COMMANDER_H

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

#endif // SERVER_COMMANDER_H
