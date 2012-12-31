#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <QString>
#include "log_config.h"

class Logger
{
public:
    Logger(Config::Log::LOG_KIND kind):m_logKind(kind){}
    virtual ~Logger(){}

    virtual void taskNew(QString str) = 0;
    virtual void taskDone() = 0;
    virtual void taskFail() = 0;

    virtual void msgDebug(QString str) = 0;
    virtual void msgInfo(QString str) = 0;
    virtual void msgWarning(QString str) = 0;
    virtual void msgError(QString str) = 0;

    Config::Log::LOG_KIND logKind() {return m_logKind;}

    void setLevel(quint8 value){this->level = value;}

protected:
    quint8 level;
    Config::Log::LOG_KIND m_logKind;
};

#endif // LOGGER_LOGGER_H
