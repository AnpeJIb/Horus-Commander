#ifndef GENERAL_CONFIG_SERVICE_H
#define GENERAL_CONFIG_SERVICE_H

#include <QString>

#include "primary_config_service.h"
#include "model_parameter_value.h"

using namespace Domain::Parameters;

namespace Service { namespace ConfigService {

class GeneralConfigService: public PrimaryConfigService
{
public:
    GeneralConfigService();

    void setLanguageCode(const QString& value);
    QString languageCode();

private:
    ModelParameterValue* langCodeValue();

    ModelParameter *langCodeModelParameter();
    ModelParameter *rootModelParameter();

    SimpleParameter *langCodeSimpleParameter();
    SimpleParameter *rootSimpleParameter();
    SimpleParameter *simpleParameter(const domain_codeName_t& codeName, const domain_title_t& title);
};

}}

#endif // GENERAL_CONFIG_SERVICE_H
