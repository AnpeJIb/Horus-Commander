#include "log_service_test.h"

#include "log_config.h"
#include "log_service.h"

LogServiceTest::LogServiceTest(QObject *parent) :
    QObject(parent)
{
}

Logger *LogServiceTest::getLogger()
{
    return &m_logger;
}

void LogServiceTest::initTestCase()
{
    Service::LOGGER::registerLogger(&m_logger);
}

void LogServiceTest::testLevelNone()   {testAll(Config::Log::LEVEL_NONE);}
void LogServiceTest::testLevelTasks()  {testAll(Config::Log::LEVEL_TASKS);}
void LogServiceTest::testLevelDebug()  {testAll(Config::Log::LEVEL_DEBUG);}
void LogServiceTest::testLevelInfo()   {testAll(Config::Log::LEVEL_INFO);}
void LogServiceTest::testLevelWarn()   {testAll(Config::Log::LEVEL_WARNING);}
void LogServiceTest::testLevelErr()    {testAll(Config::Log::LEVEL_ERROR);}
void LogServiceTest::testLevelAll()    {testAll(Config::Log::LEVEL_ALL);}

void LogServiceTest::testLevelTaskAndDebug() {testAll(Config::Log::LEVEL_TASKS | Config::Log::LEVEL_DEBUG);}
void LogServiceTest::testLevelTaskAndInfo()  {testAll(Config::Log::LEVEL_TASKS | Config::Log::LEVEL_INFO);}
void LogServiceTest::testLevelTaskAndWarn()  {testAll(Config::Log::LEVEL_TASKS | Config::Log::LEVEL_WARNING);}
void LogServiceTest::testLevelTaskAndErr()   {testAll(Config::Log::LEVEL_TASKS | Config::Log::LEVEL_ERROR);}

void LogServiceTest::cleanupTestCase()
{
    Service::LOGGER::unregisterLogger(&m_logger);
}
