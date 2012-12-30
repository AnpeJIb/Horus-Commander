#ifndef CONFIG_SERVICE_H
#define CONFIG_SERVICE_H

#include "model_parameter_value.h"

#include "model_parameter_value_dao.h"
#include "model_parameter_dao.h"
#include "simple_parameter_dao.h"

using namespace Domain::Parameters;
using namespace Dao::Parameters;

namespace Service { namespace ConfigService {

class ConfigServiceBase
{
public:
    virtual ~ConfigServiceBase(){}

protected:
    void setValue(ModelParameterValue* modelParameterValue, const QString& value);
    ModelParameterValue* getValue(
            const domain_codeName_t& codeName, const QString& defaultValue, ModelParameter *parameter);

    ModelParameter*  modelParameter(const domain_codeName_t& codeName, const domain_title_t& title, ModelParameter* parent = NULL);
    SimpleParameter* simpleParameter(const domain_codeName_t& codeName, const domain_title_t& title);

    virtual ModelParameterValueDao*   valuesDao() = 0;
    virtual ModelParameterDao*   modelParamsDao() = 0;
    virtual SimpleParameterDao* simpleParamsDao() = 0;

    virtual Scheme* getCurrentScheme() = 0;

    virtual void syncDao() = 0;
};

}}

#endif // CONFIG_SERVICE_H
