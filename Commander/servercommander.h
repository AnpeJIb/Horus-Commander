#ifndef SERVERCOMMANDER_H
#define SERVERCOMMANDER_H

#include <QObject>

#include "missionmanager.h"

namespace SC
{
    void INIT();

    void RUN();
    void STOP();
    void SET_LOADED(int sig);

    extern MissionManager MSSN;
}

#endif // SERVERCOMMANDER_H
