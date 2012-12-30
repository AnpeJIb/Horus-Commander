#include "config_service_base.h"

namespace Service { namespace ConfigService {

void ConfigServiceBase::setValue(ModelParameterValue* modelParameterValue, const QString& value)
{
    if (getCurrentScheme() == NULL) return;

    modelParameterValue->value = value;
    valuesDao()->update(modelParameterValue);
    syncDao();
}

ModelParameter* ConfigServiceBase::modelParameter(
        const domain_codeName_t &codeName, const domain_title_t &title, ModelParameter *parent)
{
    QList<ModelParameter *> mParams;
    modelParamsDao()->findByCodeName(codeName, &mParams);

    ModelParameter* mParam = NULL;

    if (mParams.count() != 0)
    {
        mParam = mParams.first();
    } else {
        SimpleParameter* sParam = simpleParameter(codeName, title);

        mParam = new ModelParameter(modelParamsDao());
        mParam->title = sParam->title;
        mParam->setSimpleParameter(sParam);
        mParam->setModel(getCurrentScheme()->model());
        mParam->setParent(parent);
        modelParamsDao()->save(mParam);
        syncDao();
    }

    return mParam;
}

SimpleParameter* ConfigServiceBase::simpleParameter(
        const domain_codeName_t &codeName, const domain_title_t &title)
{
    QList<SimpleParameter *> sParams;
    simpleParamsDao()->findByCodeName(codeName, &sParams);

    SimpleParameter* sParam = NULL;

    if (sParams.count() != 0)
    {
        sParam = sParams.first();
    } else {
        sParam = new SimpleParameter;
        sParam->codeName = codeName;
        sParam->title = title;
        simpleParamsDao()->save(sParam);
        syncDao();
    }

    return sParam;
}

ModelParameterValue * ConfigServiceBase::getValue(
        const domain_codeName_t &codeName, const QString &defaultValue, ModelParameter* parameter)
{
    QList<ModelParameterValue *> values;
    valuesDao()->findByCodeNameForScheme(codeName, getCurrentScheme(), &values);

    ModelParameterValue* mpValue = NULL;

    if (values.count() != 0)
    {
        mpValue = values.first();
    } else {
        mpValue = new ModelParameterValue(valuesDao());
        mpValue->setParameter(parameter);
        mpValue->setScheme(getCurrentScheme());
        mpValue->value = defaultValue;
        valuesDao()->save(mpValue);
        syncDao();
    }

    return mpValue;
}

}}
