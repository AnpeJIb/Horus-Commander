#include "primary_config_helper.h"
#include "xml_dao_helper.h"

namespace Config
{

const QString CURRENT_SCHEME_ID_KEY = "Schemes/primary";

bool PrimaryConfigHelper::m_initialized = false;
QSettings* PrimaryConfigHelper::m_settings = NULL;
Dao::Parameters::Scheme* PrimaryConfigHelper::m_scheme = NULL;

void PrimaryConfigHelper::init(const QString& configPath, const QString& dataSrcPath)
{
    if (m_initialized) return;

    Dao::XmlDaoHelper::init(dataSrcPath);
    m_settings = new QSettings(configPath, QSettings::IniFormat);
    selectCurrentScheme(m_settings->value(CURRENT_SCHEME_ID_KEY, "1").toLongLong());

    m_initialized = true;
}

void PrimaryConfigHelper::cleanUp()
{
    m_initialized = false;

    m_settings->sync();
    delete m_settings;

    Dao::XmlDaoHelper::tearDown();
}

void PrimaryConfigHelper::selectCurrentScheme(domain_id_t id)
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

bool PrimaryConfigHelper::isInitialized()
{
    return m_initialized;
}

void PrimaryConfigHelper::loadCurrentScheme(domain_id_t id)
{
    Dao::Parameters::SchemeXmlDao m_schemeDao;

    /** Try to load specified scheme */

    Scheme* sch = m_schemeDao.find(id);

    if (sch != NULL)
    {
        m_scheme = sch;
        return;
    }

    /** Try to load any scheme */

    QList<Scheme*> schemeLst;
    m_schemeDao.all(&schemeLst);

    if (schemeLst.count() > 0)
    {
        m_scheme = schemeLst.at(0);
        return;
    }

    /** Create new scheme */

    Dao::Parameters::ModelXmlDao modelDao;

    QList<Model*> modelLst;
    modelDao.all(&modelLst);

    Model* model;

    if (modelLst.count() > 0)
    {
        /** Try to load any model */

        model = modelLst.at(0);
    } else {
        /** Create new model */

        model = new Model;
        model->title = QObject::tr("Primary config model");
        model->kind  = Model::MODEL_PRIMARY_SETTINGS;
        modelDao.save(model);
    }

    sch = new Scheme(&m_schemeDao);
    sch->title = QObject::tr("Default");
    sch->description = QObject::tr("Default primary config scheme");
    sch->setModel(model);
    m_schemeDao.save(sch);
    m_scheme = sch;

    Dao::XmlDaoBase::sync();
}

}
