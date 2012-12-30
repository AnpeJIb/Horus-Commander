#ifndef GENERAL_CONFIG_SERVICE_H
#define GENERAL_CONFIG_SERVICE_H

#include <QString>

#include "general_config.h"

#include "config_service_base.h"
#include "primary_config_service.h"

#include "model_parameter_value.h"

using namespace Domain::Parameters;
using namespace Dao::Parameters;

namespace Service { namespace ConfigService {

class GeneralConfigService: public PrimaryConfigService, public ConfigServiceBase
{
public:
    GeneralConfigService(){}

    QString languageCode();
    QString serverPath();
    Config::General::DB_KIND dbKind();
    QString dbConnectionString(Config::General::DB_KIND dbKind);

    void setLanguageCode(const QString& value);
    void setServerPath(const QString& value);
    void setDbKind(Config::General::DB_KIND value);
    void setDbConnectionString(Config::General::DB_KIND dbKind, const QString& value);

protected:
    ModelParameterValueDao* valuesDao()   { return &m_valuesDao;  }
    ModelParameterDao* modelParamsDao()   { return &m_mParamsDao; }
    SimpleParameterDao* simpleParamsDao() { return &m_sParamsDao; }

    Scheme* getCurrentScheme() { return currentScheme(); }
    void syncDao() {Dao::XmlDaoBase::sync();}

private:
    ModelParameterValue* langCodeValue();
    ModelParameterValue* serverPathValue();
    ModelParameterValue* dbRootValue();
    ModelParameterValue* dbConnectionValue(Config::General::DB_KIND dbKind);

    ModelParameter *rootModelParameter();
    ModelParameter *langCodeModelParameter();
    ModelParameter *servPathModelParameter();
    ModelParameter *dbRootModelParameter();
    ModelParameter *dbSQLiteModelParameter();

    QString defaultDbConnectionString() const;
};

}}

#endif // GENERAL_CONFIG_SERVICE_H
