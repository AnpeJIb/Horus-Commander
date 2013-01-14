#include "file_line_reader_test.h"

#include <QtCore>
#include <QtTest/QtTest>

FileLineReaderTest::FileLineReaderTest(QObject *parent)
    : QObject(parent),
      m_file_path("fileLineReaderTest.txt")
{
}

void FileLineReaderTest::initTestCase()
{
    m_expected_strings.reset();
    m_producer.configure(m_file_path);
    m_reader.configure(m_file_path);

    connect(&m_producer, SIGNAL(lineProduced(QString)),
            this, SLOT(onLineProduced(QString)), Qt::DirectConnection);
    connect(&m_reader, SIGNAL(lineRead(QString)),
            this, SLOT(onLineRead(QString)), Qt::DirectConnection);
}

void FileLineReaderTest::testLineReader()
{
    m_reader.start();
    m_producer.start();
    m_producer.wait();
    m_reader.requestStop();
    m_reader.wait();

    QVERIFY(m_expected_strings.areAllSucceded());
}

void FileLineReaderTest::cleanupTestCase()
{
    QFile::remove(m_file_path);
}

void FileLineReaderTest::onLineProduced(const QString &line)
{
    m_expected_strings.append(line);
}

void FileLineReaderTest::onLineRead(const QString &line)
{
    QCOMPARE(m_expected_strings.current(), line);
    m_expected_strings.succedOne();
}
