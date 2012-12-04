#ifndef LOGS_H
#define LOGS_H

#include "statusfilelogger.h"
#include "statuswidget.h"
#include "commonlogconfig.h"

namespace LOGS
{
    void INIT();

    void SET_GUI_LOGGER(StatusWidget* value);

    void UPDATE_LOGGERS();
    void UPDATE_FILE_LOGGER();
    void UPDATE_GUI_LOGGER();
}

#endif // LOGS_H
