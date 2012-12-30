#ifndef GENERAL_CONFIG_SERVICE_TEST_H
#define GENERAL_CONFIG_SERVICE_TEST_H

#include <QObject>

#include "general_config_service.h"

class GeneralConfigServiceTest: public QObject
{
    Q_OBJECT
public:
    explicit GeneralConfigServiceTest(QObject *parent = 0);

private slots:
    void initTestCase();
    void testLanguageCode();
    void testServerPath();
    void testDBstrings();
    void cleanupTestCase();

private:
    QString configPath;
    QString dsPath;
    Service::ConfigService::GeneralConfigService service;
};

#endif // GENERAL_CONFIG_SERVICE_TEST_H
