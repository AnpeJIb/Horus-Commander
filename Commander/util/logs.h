#ifndef LOGS_H
#define LOGS_H

#include "statusfilelogger.h"
#include "statuswidget.h"
#include "commonlogconfig.h"

class LOGS
{
public:
    LOGS();

    static void SET_GUI_LOGGER(StatusWidget* value);

    static void UPDATE_LOGGERS();
    static void UPDATE_FILE_LOGGER();
    static void UPDATE_GUI_LOGGER();

private:
    static void UPDATE_LOGGER(StatusPrinter* printer, CommonLogConfig*cfg);

    static StatusFileLogger* FILE;
    static StatusWidget* GUI;
};

#endif // LOGS_H
