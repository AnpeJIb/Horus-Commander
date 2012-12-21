#include "mission_manager.h"
#include "sc.h"

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
