#ifndef PRIMARY_CONFIG_SERVICE_H
#define PRIMARY_CONFIG_SERVICE_H

#include <QString>
#include <QList>
#include <QSettings>

#include "scheme.h"

namespace Config
{

class PrimaryConfigService
{
public:
    static void init(const QString& configPath, const QString& dataSrcPath);
    static void cleanUp();
    static void selectCurrentScheme(domain_id_t id);
    static bool isInitialized();
    static void shemes(QList<Domain::Parameters::Scheme *> *result);

protected:
    static bool m_initialized;
    static QSettings* m_settings;
    static Domain::Parameters::Scheme* m_scheme;

private:
    static void loadCurrentScheme(domain_id_t id);
};

}

#endif // PRIMARY_CONFIG_SERVICE_H
