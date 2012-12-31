#ifndef LOG_CONFIG_SERVICE_H
#define LOG_CONFIG_SERVICE_H

#include <QString>

#include "log_config.h"
#include "logger.h"

#include "config_service_base.h"
#include "primary_config_service.h"

#include "model_parameter_value.h"

using namespace Domain::Parameters;
using namespace Dao::Parameters;

namespace Service { namespace ConfigService {

class LogConfigService: public PrimaryConfigService, public ConfigServiceBase
{
public:
    LogConfigService();

    Config::Log::LOG_LEVEL logLevel(Config::Log::LOG_KIND logKind);
    void setLogLevel(Config::Log::LOG_KIND logKind, Config::Log::LOG_LEVEL value);

protected:
    ModelParameterValueDao* valuesDao()   { return &m_valuesDao;  }
    ModelParameterDao* modelParamsDao()   { return &m_mParamsDao; }
    SimpleParameterDao* simpleParamsDao() { return &m_sParamsDao; }

    Scheme* getCurrentScheme() { return currentScheme(); }
    void syncDao() {Dao::XmlDaoBase::sync();}

private:
    ModelParameterValue* logLevelValue(Config::Log::LOG_KIND logKind);

    ModelParameter *rootModelParameter();
    ModelParameter *fileLogLevelModelParameter();
    ModelParameter *guiLogLevelModelParameter();
};

}}

#endif // LOG_CONFIG_SERVICE_H
