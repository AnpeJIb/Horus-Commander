#ifndef LOGGER_LOGGER_SERVICE_TEST_H
#define LOGGER_LOGGER_SERVICE_TEST_H

#include <QObject>
#include "logger.h"
#include "logger_tester.h"
#include "foo_logger.h"

class LogServiceTest : public QObject, public LoggerTester
{
    Q_OBJECT
public:
    explicit LogServiceTest(QObject *parent = 0);
    
protected:
    Logger* getLogger();

private slots:
    void initTestCase();
    void testLevelNone();
    void testLevelTasks();
    void testLevelDebug();
    void testLevelInfo();
    void testLevelWarn();
    void testLevelErr();
    void testLevelAll();

    void testLevelTaskAndDebug();
    void testLevelTaskAndInfo();
    void testLevelTaskAndWarn();
    void testLevelTaskAndErr();
    void cleanupTestCase();

private:
    FooLogger m_logger;
};

#endif // LOGGER_LOGGER_SERVICE_TEST_H
