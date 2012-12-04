#include "missionmanager.h"
#include "servercommander.h"

MissionManager::MissionManager()
{
}

void MissionManager::start()
{
    if (SC::SP.isRunning()==false)
        SC::SP.start();

    // TODO:
}

void MissionManager::stop()
{
    // TODO:
}
