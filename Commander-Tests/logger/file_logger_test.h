#ifndef LOGGER_FILE_LOGGER_TEST_H
#define LOGGER_FILE_LOGGER_TEST_H

#include <QObject>
#include "file_logger.h"
#include "logger_tester.h"

class FileLoggerTest: public QObject, public LoggerTester
{
    Q_OBJECT
public:
    explicit FileLoggerTest(QObject *parent = 0);

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
    FileLogger* m_logger;
    QString filepath;
};

#endif // LOGGER_FILE_LOGGER_TEST_H
