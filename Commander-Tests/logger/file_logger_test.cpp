#include "file_logger_test.h"

#include <QFile>
#include <QFileInfo>
#include <iostream>

#include "file_util.h"
#include "log_config.h"
#include "log_service.h"

using namespace std;

FileLoggerTest::FileLoggerTest(QObject *parent)
    : QObject(parent)
{
}

Logger* FileLoggerTest::getLogger()
{
    return m_logger;
}

void FileLoggerTest::initTestCase()
{
    QFileInfo fileInfo("./test.log");
    filepath = fileInfo.absoluteFilePath();

    m_logger = new FileLogger(filepath);
    Service::LOGGER::registerLogger(m_logger);
}

void FileLoggerTest::testLevelNone()   {testAll(Config::Log::LEVEL_NONE);}
void FileLoggerTest::testLevelTasks()  {testAll(Config::Log::LEVEL_TASKS);}
void FileLoggerTest::testLevelDebug()  {testAll(Config::Log::LEVEL_DEBUG);}
void FileLoggerTest::testLevelInfo()   {testAll(Config::Log::LEVEL_INFO);}
void FileLoggerTest::testLevelWarn()   {testAll(Config::Log::LEVEL_WARNING);}
void FileLoggerTest::testLevelErr()    {testAll(Config::Log::LEVEL_ERROR);}
void FileLoggerTest::testLevelAll()    {testAll(Config::Log::LEVEL_ALL);}

void FileLoggerTest::testLevelTaskAndDebug() {testAll(Config::Log::LEVEL_TASKS | Config::Log::LEVEL_DEBUG);}
void FileLoggerTest::testLevelTaskAndInfo()  {testAll(Config::Log::LEVEL_TASKS | Config::Log::LEVEL_INFO);}
void FileLoggerTest::testLevelTaskAndWarn()  {testAll(Config::Log::LEVEL_TASKS | Config::Log::LEVEL_WARNING);}
void FileLoggerTest::testLevelTaskAndErr()   {testAll(Config::Log::LEVEL_TASKS | Config::Log::LEVEL_ERROR);}

void FileLoggerTest::cleanupTestCase()
{
    Service::LOGGER::unregisterLogger(m_logger);
    delete m_logger;

    printFile(filepath);
    QFile::remove(filepath);
}
