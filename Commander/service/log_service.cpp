#include "log_service.h"

namespace Service {

QMap<Config::Log::LOG_KIND, QList<Logger*> > LOGGER::m_loggers;

void LOGGER::registerLogger(Logger* logger)
{
    if ((logger != NULL) && (LOGGER::m_loggers[logger->logKind()].contains(logger)==false))
        LOGGER::m_loggers[logger->logKind()].append(logger);
}

void LOGGER::unregisterLogger(Logger* logger)
{
    if ((logger != NULL) && (LOGGER::m_loggers[logger->logKind()].contains(logger)))
        LOGGER::m_loggers[logger->logKind()].removeOne(logger);
}

void LOGGER::setLoggersLevel(Config::Log::LOG_KIND kind, Config::Log::LOG_LEVEL level)
{
        foreach(Logger* logger, LOGGER::m_loggers[kind])
            logger->setLevel(level);
}

void LOGGER::taskNew(const QString& str)
{
    foreach(QList<Logger*> lst, LOGGER::m_loggers.values())
        foreach(Logger* logger, lst)
            logger->taskNew(str);
}

void LOGGER::taskDone()
{
    foreach(QList<Logger*> lst, LOGGER::m_loggers.values())
        foreach(Logger* logger, lst)
            logger->taskDone();
}

void LOGGER::taskFail()
{
    foreach(QList<Logger*> lst, LOGGER::m_loggers.values())
        foreach(Logger* logger, lst)
            logger->taskFail();
}

void LOGGER::msgDebug(const QString& str)
{
    foreach(QList<Logger*> lst, LOGGER::m_loggers.values())
        foreach(Logger* logger, lst)
            logger->msgDebug(str);
}

void LOGGER::msgInfo(const QString& str)
{
    foreach(QList<Logger*> lst, LOGGER::m_loggers.values())
        foreach(Logger* logger, lst)
            logger->msgInfo(str);
}

void LOGGER::msgWarning(const QString& str)
{
    foreach(QList<Logger*> lst, LOGGER::m_loggers.values())
        foreach(Logger* logger, lst)
            logger->msgWarning(str);
}

void LOGGER::msgError(const QString& str)
{
    foreach(QList<Logger*> lst, LOGGER::m_loggers.values())
        foreach(Logger* logger, lst)
            logger->msgError(str);
}

}
