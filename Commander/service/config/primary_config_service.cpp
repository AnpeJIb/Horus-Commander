#include "primary_config_service.h"
#include "xml_dao_helper.h"

#include "model_xml_dao.h"
#include "scheme_xml_dao.h"

namespace Config
{

const QString CURRENT_SCHEME_ID_KEY = "Schemes/primary";

bool PrimaryConfigService::m_initialized = false;
QSettings* PrimaryConfigService::m_settings = NULL;
Dao::Parameters::Scheme* PrimaryConfigService::m_scheme = NULL;

void PrimaryConfigService::init(const QString& configPath, const QString& dataSrcPath)
{
    if (m_initialized) return;

    Dao::XmlDaoHelper::init(dataSrcPath);
    m_settings = new QSettings(configPath, QSettings::IniFormat);
    selectCurrentScheme(m_settings->value(CURRENT_SCHEME_ID_KEY, "1").toLongLong());

    m_initialized = true;
}

void PrimaryConfigService::cleanUp()
{
    m_initialized = false;

    m_scheme = NULL;
    m_settings->sync();
    delete m_settings;

    Dao::XmlDaoHelper::tearDown();
}

void PrimaryConfigService::selectCurrentScheme(domain_id_t id)
{
    if (id == Q_UINT64_C(0)) return;

    if ((m_scheme != NULL) && (m_scheme->id == id)) return;

    loadCurrentScheme(id);

    if (m_scheme != NULL)
    {
        m_settings->setValue(CURRENT_SCHEME_ID_KEY, QString::number(id));
        m_settings->sync();
    }
}

bool PrimaryConfigService::isInitialized()
{
    return m_initialized;
}

void PrimaryConfigService::shemes(QList<Domain::Parameters::Scheme *> *result)
{
    Dao::Parameters::SchemeXmlDao schemeDao;
    schemeDao.findByModelKind(Model::MODEL_PRIMARY_SETTINGS, result);
}

void PrimaryConfigService::loadCurrentScheme(domain_id_t id)
{
    Dao::Parameters::SchemeXmlDao schemeDao;

    /** Try to load specified scheme */

    Scheme* sch = schemeDao.find(id);

    if ((sch != NULL) && (sch->model()->kind == Model::MODEL_PRIMARY_SETTINGS))
    {
        m_scheme = sch;
        return;
    }

    /** Try to load any scheme */

    QList<Scheme*> schemeLst;
    schemeDao.all(&schemeLst);

    if (schemeLst.count() > 0)
    {
        m_scheme = schemeLst.at(0);
        return;
    }

    /** Create new scheme */

    Dao::Parameters::ModelXmlDao modelDao;

    QList<Model*> modelLst;
    modelDao.findByKind(Model::MODEL_PRIMARY_SETTINGS, &modelLst);

    Model* model = NULL;

    if (modelLst.count() > 0)
    {
        /** Load any model */

        model = modelLst.at(0);
    } else {
        /** Create new model */

        model = new Model;
        model->title = QObject::tr("Primary config model");
        model->kind  = Model::MODEL_PRIMARY_SETTINGS;
        modelDao.save(model);
    }

    sch = new Scheme(&schemeDao);
    sch->title = QObject::tr("Default");
    sch->description = QObject::tr("Default primary config scheme");
    sch->setModel(model);
    schemeDao.save(sch);
    m_scheme = sch;

    Dao::XmlDaoBase::sync();
}

}
