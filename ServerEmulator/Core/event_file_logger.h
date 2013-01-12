#ifndef EVENTS_FILE_LOGGER_H
#define EVENTS_FILE_LOGGER_H

#include <QFile>
#include <QMutex>
#include <QString>
#include <QTextStream>

class EventFileLogger
{
public:
    explicit EventFileLogger(){}
    ~EventFileLogger(){tearDown();}

    void setup(const QString& file_name);
    void tearDown();

    void logEvent(const QString& str, bool long_format = false);

private:
    QMutex m_mutex;
    QFile m_file;
    QTextStream m_stream;
};

#endif // EVENTS_FILE_LOGGER_H
