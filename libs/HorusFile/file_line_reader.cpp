#include "file_line_reader.h"

#include <QMutexLocker>
#include <QFile>
#include <QTextStream>
#include <iostream>

const unsigned long MILLIS_TO_WAIT_ON_EMPTY_LINE = 300;

FileLineReader::FileLineReader()
    : m_stop_requested(false)
{
}

void FileLineReader::configure(const QString &file_path)
{
    m_file_path = file_path;
}

void FileLineReader::run()
{
    QFile file(m_file_path);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text) == false)
    {
        std::cerr << qPrintable(tr("Cannot open file for writing: "))
                  << qPrintable(file.errorString())
                  << std::endl;
        return;
    }

    QTextStream in(&file);

    forever
    {
        if (isStopRequested()) break;

        while (in.atEnd() == false)
        {
              QString line = in.readLine();
              emit lineRead(line);
        }

        msleep(MILLIS_TO_WAIT_ON_EMPTY_LINE);
    }
}

bool FileLineReader::isStopRequested()
{
    QMutexLocker locker(&m_mutex);
    return m_stop_requested;
}

void FileLineReader::requestStop()
{
    QMutexLocker locker(&m_mutex);
    m_stop_requested = true;
}
