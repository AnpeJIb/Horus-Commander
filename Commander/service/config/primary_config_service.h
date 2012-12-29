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
    static bool isInitialized();

    static void selectCurrentScheme(domain_id_t id);
    static void schemes(QList<Domain::Parameters::Scheme *> *result);
    static Domain::Parameters::Scheme* currentScheme();
    static void copyCurrentSchemeAndSelect();
    static void removeCurrentScheme();
    static void updateCurrentScheme();

protected:
    static bool m_initialized;
    static QSettings* m_settings;

private:
    static void loadCurrentScheme(domain_id_t id);
    static void saveCurrentSchemeId();

    static Domain::Parameters::Scheme* m_scheme;
};

}

#endif // PRIMARY_CONFIG_SERVICE_H
