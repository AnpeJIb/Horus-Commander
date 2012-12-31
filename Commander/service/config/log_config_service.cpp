#include "log_config_service.h"

namespace Service { namespace ConfigService {

const QString CODE_NAME_ROOT = "LOGGING_CONFIG";
const QString CODE_NAME_FILE = "LOG_FILE";
const QString CODE_NAME_GUI  = "LOG_GUI";

LogConfigService::LogConfigService()
{
}

StatusPrinter::Level LogConfigService::logLevel(Config::Log::LOG_KIND logKind)
{
    return (currentScheme() == NULL)
            ? StatusPrinter::LEVEL_NONE
            : (StatusPrinter::Level) logLevelValue(logKind)->value.toUInt();
}

void LogConfigService::setLogLevel(Config::Log::LOG_KIND logKind, StatusPrinter::Level value)
{
    setValue(logLevelValue(logKind), QString::number(value));
}

ModelParameterValue *LogConfigService::logLevelValue(Config::Log::LOG_KIND logKind)
{
    QString defaultLevelStr = QString::number(Config::Log::defaultLogLevel);

    switch (logKind) {
        case Config::Log::LOG_FILE:
            return getValue(CODE_NAME_FILE, defaultLevelStr, fileLogLevelModelParameter());
        case Config::Log::LOG_GUI:
            return getValue(CODE_NAME_GUI, defaultLevelStr, guiLogLevelModelParameter());
        default:
            return NULL;
    }
}

ModelParameter *LogConfigService::rootModelParameter()
{
    return modelParameter(CODE_NAME_ROOT, QObject::tr("Logging configuration"));
}

ModelParameter *LogConfigService::fileLogLevelModelParameter()
{
    return modelParameter(CODE_NAME_FILE, QObject::tr("File log level"), rootModelParameter());
}

ModelParameter *LogConfigService::guiLogLevelModelParameter()
{
    return modelParameter(CODE_NAME_GUI, QObject::tr("GUI log level"), rootModelParameter());
}

}}
