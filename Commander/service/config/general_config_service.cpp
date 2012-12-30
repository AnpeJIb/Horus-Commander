#include "general_config_service.h"

#include <QObject>
#include <QList>
#include <QString>

#include "general_config.h"

namespace Service { namespace ConfigService {

const QString CODE_NAME_ROOT      = "GENERAL_CONFIG";
const QString CODE_NAME_LANG      = "LANG_CODE";
const QString CODE_NAME_SERV_PATH = "SERV_PATH";

QString GeneralConfigService::languageCode()
{
    return (currentScheme() == NULL)?QObject::tr("unknown"):langCodeValue()->value;
}

QString GeneralConfigService::serverPath()
{
    return (currentScheme() == NULL)?QObject::tr("no path"):serverPathValue()->value;
}

void GeneralConfigService::setLanguageCode(const QString &value)
{
    setValue(langCodeValue(), value);
}

void GeneralConfigService::setServerPath(const QString &value)
{
    setValue(serverPathValue(), value);
}

void GeneralConfigService::setValue(ModelParameterValue *modelParameterValue, const QString &value)
{
    if (currentScheme() == NULL) return;

    modelParameterValue->value = value;
    valuesDao.update(modelParameterValue);
    Dao::XmlDaoBase::sync();
}

ModelParameterValue *GeneralConfigService::langCodeValue()
{
    return getValue(CODE_NAME_LANG,
                    Config::General::defaultLanguageCode(),
                    &GeneralConfigService::langCodeModelParameter);
}

ModelParameterValue *GeneralConfigService::serverPathValue()
{
    return getValue(CODE_NAME_SERV_PATH,
                    Config::General::defaultServerPath(),
                    &GeneralConfigService::servPathModelParameter);
}

ModelParameterValue * GeneralConfigService::getValue(
        const domain_codeName_t &codeName, const QString &defaultValue,
        ModelParameter* (GeneralConfigService::*parameterGetter)())
{
    QList<ModelParameterValue *> values;
    valuesDao.findByCodeNameForScheme(codeName, currentScheme(), &values);

    ModelParameterValue* mpValue = NULL;

    if (values.count() != 0)
    {
        mpValue = values.first();
    } else {
        mpValue = new ModelParameterValue(&valuesDao);
        mpValue->setParameter((this->*parameterGetter)());
        mpValue->setScheme(currentScheme());
        mpValue->value = defaultValue;
        valuesDao.save(mpValue);
        Dao::XmlDaoBase::sync();
    }

    return mpValue;
}

ModelParameter *GeneralConfigService::langCodeModelParameter()
{
    return modelParameter(CODE_NAME_LANG, QObject::tr("Language code"), rootModelParameter());
}

ModelParameter *GeneralConfigService::servPathModelParameter()
{
    return modelParameter(CODE_NAME_SERV_PATH, QObject::tr("Server path"), rootModelParameter());
}

ModelParameter *GeneralConfigService::rootModelParameter()
{
    return modelParameter(CODE_NAME_ROOT, QObject::tr("General configuration"));
}

ModelParameter *GeneralConfigService::modelParameter(const domain_codeName_t &codeName, const domain_title_t &title, ModelParameter *parent)
{
    QList<ModelParameter *> mParams;
    mParamsDao.findByCodeName(codeName, &mParams);

    ModelParameter* mParam = NULL;

    if (mParams.count() != 0)
    {
        mParam = mParams.first();
    } else {
        SimpleParameter* sParam = simpleParameter(codeName, title);

        mParam = new ModelParameter(&mParamsDao);
        mParam->title = sParam->title;
        mParam->setSimpleParameter(sParam);
        mParam->setModel(currentScheme()->model());
        mParam->setParent(parent);
        mParamsDao.save(mParam);
        Dao::XmlDaoBase::sync();
    }

    return mParam;
}

SimpleParameter *GeneralConfigService::simpleParameter(const domain_codeName_t &codeName, const domain_title_t &title)
{
    QList<SimpleParameter *> sParams;
    sParamsDao.findByCodeName(codeName, &sParams);

    SimpleParameter* sParam = NULL;

    if (sParams.count() != 0)
    {
        sParam = sParams.first();
    } else {
        sParam = new SimpleParameter;
        sParam->codeName = codeName;
        sParam->title = title;
        sParamsDao.save(sParam);
        Dao::XmlDaoBase::sync();
    }

    return sParam;
}

}}
