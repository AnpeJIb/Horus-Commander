#ifndef LOG_CONFIG_H
#define LOG_CONFIG_H

namespace Config { namespace Log {

enum LOG_KIND
{
    LOG_NONE = 0,
    LOG_FILE = 1,
    LOG_GUI  = 2
};

enum LOG_LEVEL
{
    LEVEL_NONE    = 0,
    LEVEL_ALL     = 0x1F,
    LEVEL_TASKS   = (1 << 0),
    LEVEL_DEBUG   = (1 << 1),
    LEVEL_INFO    = (1 << 2),
    LEVEL_WARNING = (1 << 3),
    LEVEL_ERROR   = (1 << 4)
};


const LOG_LEVEL defaultLogLevel = LEVEL_ALL;

}}

#endif // LOG_CONFIG_H
