#ifndef GENERAL_CONFIG_SERVICE_H
#define GENERAL_CONFIG_SERVICE_H

#include <QString>

#include "primary_config_service.h"
#include "model_parameter_value.h"

#include "model_parameter_value_xml_dao.h"
#include "model_parameter_xml_dao.h"
#include "simple_parameter_xml_dao.h"

using namespace Domain::Parameters;
using namespace Dao::Parameters;

namespace Service { namespace ConfigService {

class GeneralConfigService: public PrimaryConfigService
{
public:
    GeneralConfigService(){}

    QString languageCode();
    QString serverPath();

    void setLanguageCode(const QString& value);
    void setServerPath(const QString& value);

private:
    void setValue(ModelParameterValue* modelParameterValue, const QString& value);
    ModelParameterValue* getValue(
            const domain_codeName_t& codeName, const QString& defaultValue,
            ModelParameter* (GeneralConfigService::*parameterGetter)());

    ModelParameterValue* langCodeValue();
    ModelParameterValue* serverPathValue();

    ModelParameter *rootModelParameter();
    ModelParameter *langCodeModelParameter();
    ModelParameter *servPathModelParameter();

    ModelParameter*  modelParameter(const domain_codeName_t& codeName, const domain_title_t& title, ModelParameter* parent = NULL);
    SimpleParameter* simpleParameter(const domain_codeName_t& codeName, const domain_title_t& title);

    ModelParameterValueXmlDao valuesDao;
    ModelParameterXmlDao mParamsDao;
    SimpleParameterXmlDao sParamsDao;
};

}}

#endif // GENERAL_CONFIG_SERVICE_H
