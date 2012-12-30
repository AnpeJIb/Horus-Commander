#include "general_config_service.h"

#include <QObject>
#include <QList>
#include <QString>

#include "model_parameter_value_xml_dao.h"
#include "model_parameter_xml_dao.h"
#include "simple_parameter_xml_dao.h"
#include "general_config.h"

using namespace Dao::Parameters;

namespace Service { namespace ConfigService {

const QString CODE_NAME_LANG = "LANG_CODE";
const QString CODE_NAME_ROOT = "GENERAL_CONFIG";

GeneralConfigService::GeneralConfigService()
{
}

void GeneralConfigService::setLanguageCode(const QString &value)
{
    if (currentScheme() == NULL) return;

    ModelParameterValueXmlDao valuesDao;
    ModelParameterValue* mpValue = langCodeValue();
    mpValue->value = value;
    valuesDao.update(mpValue);

    Dao::XmlDaoBase::sync();
}

QString GeneralConfigService::languageCode()
{
    if (currentScheme() == NULL) return "unknown";
    return langCodeValue()->value;
}

ModelParameterValue *GeneralConfigService::langCodeValue()
{
    ModelParameterValueXmlDao valuesDao;
    QList<ModelParameterValue *> values;
    valuesDao.findByCodeNameForScheme(CODE_NAME_LANG, currentScheme(), &values);

    ModelParameterValue* mpValue = NULL;

    if (values.count() != 0)
    {
        mpValue = values.first();
    } else {
        mpValue = new ModelParameterValue(&valuesDao);
        mpValue->setParameter(langCodeModelParameter());
        mpValue->setScheme(currentScheme());
        mpValue->value = Config::General::defaultLanguageCode();
        valuesDao.save(mpValue);
        Dao::XmlDaoBase::sync();
    }

    return mpValue;
}

ModelParameter *GeneralConfigService::langCodeModelParameter()
{
    ModelParameterXmlDao mParamsDao;
    QList<ModelParameter *> mParams;
    mParamsDao.findByCodeName(CODE_NAME_LANG, &mParams);

    ModelParameter* mParam = NULL;

    if (mParams.count() != 0)
    {
        mParam = mParams.first();
    } else {
        SimpleParameter* sParam = langCodeSimpleParameter();

        mParam = new ModelParameter(&mParamsDao);
        mParam->title = sParam->title;
        mParam->setSimpleParameter(sParam);
        mParam->setModel(currentScheme()->model());
        mParam->setParent(rootModelParameter());
        mParamsDao.save(mParam);
        Dao::XmlDaoBase::sync();
    }

    return mParam;
}

ModelParameter *GeneralConfigService::rootModelParameter()
{
    ModelParameterXmlDao mParamsDao;
    QList<ModelParameter *> mParams;
    mParamsDao.findByCodeName(CODE_NAME_ROOT, &mParams);

    ModelParameter* mParam = NULL;

    if (mParams.count() != 0)
    {
        mParam = mParams.first();
    } else {
        SimpleParameter* sParam = rootSimpleParameter();

        mParam = new ModelParameter(&mParamsDao);
        mParam->title = sParam->title;
        mParam->setSimpleParameter(sParam);
        mParam->setModel(currentScheme()->model());
        mParamsDao.save(mParam);
        Dao::XmlDaoBase::sync();
    }

    return mParam;
}

SimpleParameter *GeneralConfigService::rootSimpleParameter()
{
    return simpleParameter(CODE_NAME_ROOT, QObject::tr("General configuration"));
}

SimpleParameter *GeneralConfigService::langCodeSimpleParameter()
{
    return simpleParameter(CODE_NAME_LANG, QObject::tr("Language code"));
}

SimpleParameter *GeneralConfigService::simpleParameter(const domain_codeName_t &codeName, const domain_title_t &title)
{
    SimpleParameterXmlDao sParamsDao;
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
