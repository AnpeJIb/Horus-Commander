#include "general_config_service.h"

#include <QObject>
#include <QList>
#include <QString>

namespace Service { namespace ConfigService {

const QString CODE_NAME_ROOT      = "GENERAL_CONFIG";
const QString CODE_NAME_LANG      = "LANG_CODE";
const QString CODE_NAME_SERV_PATH = "SERV_PATH";
const QString CODE_NAME_DB_ROOT   = "DB";
const QString CODE_NAME_DB_SQLITE = "DB_SQLITE";

QString GeneralConfigService::languageCode()
{
    return (currentScheme() == NULL)?QObject::tr("unknown"):langCodeValue()->value;
}

QString GeneralConfigService::serverPath()
{
    return (currentScheme() == NULL)?QObject::tr("no path"):serverPathValue()->value;
}

Config::General::DB_KIND GeneralConfigService::dbKind()
{
    return (currentScheme() == NULL)
            ? Config::General::DB_NONE
            : (Config::General::DB_KIND) dbRootValue()->value.toUInt();
}

QString GeneralConfigService::dbConnectionString(Config::General::DB_KIND dbKind)
{
    return (currentScheme() == NULL)
            ? defaultDbConnectionString()
            : dbConnectionValue(dbKind)->value;
}

void GeneralConfigService::setLanguageCode(const QString &value)
{
    setValue(langCodeValue(), value);
}

void GeneralConfigService::setServerPath(const QString &value)
{
    setValue(serverPathValue(), value);
}

void GeneralConfigService::setDbKind(Config::General::DB_KIND value)
{
    setValue(dbRootValue(), QString::number(value));
}

void GeneralConfigService::setDbConnectionString(Config::General::DB_KIND dbKind, const QString &value)
{
    setValue(dbConnectionValue(dbKind), value);
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
                    Config::General::defaultLanguage().codeName,
                    &GeneralConfigService::langCodeModelParameter);
}

ModelParameterValue *GeneralConfigService::serverPathValue()
{
    return getValue(CODE_NAME_SERV_PATH,
                    Config::General::defaultServerPath(),
                    &GeneralConfigService::servPathModelParameter);
}

ModelParameterValue *GeneralConfigService::dbRootValue()
{
    return getValue(CODE_NAME_DB_ROOT,
                    QString::number(Config::General::defaultDB().kind),
                    &GeneralConfigService::dbRootModelParameter);
}

ModelParameterValue *GeneralConfigService::dbConnectionValue(Config::General::DB_KIND dbKind)
{
    switch (dbKind) {
        case Config::General::DB_SQLITE:
            return getValue(CODE_NAME_DB_SQLITE,
                            defaultDbConnectionString(),
                            &GeneralConfigService::dbSQLiteModelParameter);
        default:
            return NULL;
    }
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

ModelParameter *GeneralConfigService::dbRootModelParameter()
{
    return modelParameter(CODE_NAME_DB_ROOT, QObject::tr("Database configuration"), rootModelParameter());
}

ModelParameter *GeneralConfigService::dbSQLiteModelParameter()
{
    return modelParameter(CODE_NAME_DB_SQLITE, QObject::tr("SQLite configuration"), dbRootModelParameter());
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

QString GeneralConfigService::defaultDbConnectionString() const
{
    return QObject::tr("invalid connection string");
}

}}
