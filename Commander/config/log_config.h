#ifndef LOG_CONFIG_H
#define LOG_CONFIG_H

#include "status_print.h"

namespace Config { namespace Log {

enum LOG_KIND
{
    LOG_NONE = 0,
    LOG_FILE = 1,
    LOG_GUI  = 2
};

const StatusPrinter::Level defaultLogLevel = StatusPrinter::LEVEL_ALL;

}}

#endif // LOG_CONFIG_H
