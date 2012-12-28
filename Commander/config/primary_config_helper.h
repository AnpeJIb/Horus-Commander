#ifndef PRIMARY_CONFIG_HELPER_H
#define PRIMARY_CONFIG_HELPER_H

#include <QString>
#include <QSettings>

#include "scheme.h"

#include "model_xml_dao.h"
#include "scheme_xml_dao.h"

namespace Config
{

class PrimaryConfigHelper
{
public:
    static void init(const QString& configPath, const QString& dataSrcPath);
    static void cleanUp();
    static void selectCurrentScheme(domain_id_t id);
    static bool isInitialized();

protected:
    static bool m_initialized;
    static QSettings* m_settings;
    static Dao::Parameters::Scheme* m_scheme;

private:
    static void loadCurrentScheme(domain_id_t id);
};

}

#endif // PRIMARY_CONFIG_HELPER_H
