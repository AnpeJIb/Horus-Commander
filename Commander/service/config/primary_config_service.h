#ifndef PRIMARY_CONFIG_SERVICE_H
#define PRIMARY_CONFIG_SERVICE_H

#include <QString>
#include <QList>
#include <QSettings>

#include "scheme.h"
#include "scheme_judge.h"

#include "model_parameter_value_xml_dao.h"
#include "model_parameter_xml_dao.h"
#include "simple_parameter_xml_dao.h"

namespace Service { namespace ConfigService {

class PrimaryConfigService
{
public:
    static void init(const QString& configPath, const QString& dataSrcPath);
    static void cleanUp();
    static bool isInitialized();

    static void selectCurrentScheme(domain_id_t id);
    static void schemes(QList<Domain::Parameters::Scheme *> *result);
    static Domain::Parameters::Scheme* currentScheme();
    static void copyCurrentSchemeAndSelect();
    static void removeCurrentScheme();
    static void updateCurrentScheme();
    static Domain::Parameters::SchemeJudge* newSchemeJudge();

protected:
    static bool m_initialized;
    static QSettings* m_settings;

    Dao::Parameters::ModelParameterValueXmlDao m_valuesDao;
    Dao::Parameters::ModelParameterXmlDao m_mParamsDao;
    Dao::Parameters::SimpleParameterXmlDao m_sParamsDao;

private:
    static void loadCurrentScheme(domain_id_t id);
    static void saveCurrentSchemeId();

    static Domain::Parameters::Scheme* m_scheme;
};

}}

#endif // PRIMARY_CONFIG_SERVICE_H
