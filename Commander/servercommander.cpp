#include "servercommander.h"

MissionManager SC::MSSN;

void SC::INIT()
{
}

void SC::RUN()
{
    // TODO:
}

void SC::STOP()
{
    MSSN.stop();
    // TODO:
}

void SC::SET_LOADED(int sig)
{
    Q_UNUSED(sig)
    // TODO:
}
