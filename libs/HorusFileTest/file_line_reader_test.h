#ifndef FILE_LINE_READER_TEST_H
#define FILE_LINE_READER_TEST_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

#include "file_line_reader.h"
#include "expected_strings.h"

class FileLineProducer: public QThread
{
    Q_OBJECT
public:
    explicit FileLineProducer(){}

    void configure(const QString& file_path)
    {
        m_file_path = file_path;

        m_file.setFileName(m_file_path);
        m_file.open(QIODevice::ReadWrite | QIODevice::Text);
        m_out.setDevice(&m_file);
    }

signals:
    void lineProduced(QString line);

protected:
    void run()
    {
        msleep(500);

        produceNewLine();
        msleep(500);

        produceNewLine();
        produceNewLine();
        msleep(50);

        produceNewLine();
        msleep(400);

        produceNewLine();
        produceNewLine();
        produceNewLine();
        produceNewLine();
        produceNewLine();

        msleep(50);

        m_file.close();
    }

private:
    void produceNewLine()
    {
        QString line = newStringValue();
        emit lineProduced(line);
        m_out << line << endl;
        m_out.flush();
    }

    QString newStringValue() const
    {
        return QString::number(QDateTime::currentMSecsSinceEpoch());
    }

    QString m_file_path;
    QFile m_file;
    QTextStream m_out;
};

class FileLineReaderTest: public QObject
{
    Q_OBJECT
public:
    explicit FileLineReaderTest(QObject *parent = 0);
    
public slots:
    void onLineProduced(const QString& line);
    void onLineRead(const QString& line);

private slots:
    void initTestCase();
    void testLineReader();
    void cleanupTestCase();

private:
    QString m_file_path;
    FileLineProducer m_producer;
    FileLineReader m_reader;

    ExpectedStrings m_expected_strings;
};

#endif // FILE_LINE_READER_TEST_H
