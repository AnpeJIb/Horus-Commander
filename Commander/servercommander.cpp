#include "servercommander.h"

MissionManager  SC::MSSN;
ServerProcess   SC::SP;
GsCommands      SC::CMD;
GsConsole       SC::CONSOLE;

QString SC::GS::logsDirPath()
{
    return CONFIG::GENERAL.serverPath().append(PATH_SEP).append("logs");
}
