#include "event_file_logger.h"

#include <QDateTime>

void EventFileLogger::logEvent(const QString &str, bool long_format)
{
    m_mutex.lock();

    QDateTime dt = QDateTime::currentDateTime();

    m_stream << "[";

    if (long_format)
        m_stream << dt.toString("MMM d, yyyy ");

    m_stream << dt.toString("h:mm:ss AP");

    m_stream << "] ";
    m_stream << str;
    m_stream.flush();

    m_mutex.unlock();
}

void EventFileLogger::setup(const QString& file_name)
{
    m_file.setFileName(file_name);
    m_file.open(QIODevice::ReadWrite);
    m_stream.setDevice(&m_file);
}

void EventFileLogger::tearDown()
{
    m_file.remove();
    m_file.close();
}
