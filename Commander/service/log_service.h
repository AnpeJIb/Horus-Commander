#ifndef LOGGER_SERVICE_H
#define LOGGER_SERVICE_H

#include "logger.h"
#include "log_config.h"

#include <QList>
#include <QMap>

namespace Service {

class LOGGER
{
public:
    static void registerLogger  (Logger* logger);
    static void unregisterLogger(Logger* logger);
    static void setLoggersLevel (Config::Log::LOG_KIND kind, Config::Log::LOG_LEVEL level);

    static void taskNew (const QString& str);
    static void taskDone();
    static void taskFail();

    static void msgDebug   (const QString& str);
    static void msgInfo    (const QString& str);
    static void msgWarning (const QString& str);
    static void msgError   (const QString& str);

private:
    LOGGER(){}

    static QMap<Config::Log::LOG_KIND, QList<Logger*> > m_loggers;
};

}

#endif // LOGGER_SERVICE_H
