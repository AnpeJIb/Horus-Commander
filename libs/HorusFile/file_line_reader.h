#ifndef FILE_LINE_READER_H
#define FILE_LINE_READER_H

#include <QThread>
#include <QMutex>
#include <QString>

class FileLineReader: public QThread
{
    Q_OBJECT
public:
    FileLineReader();

    void configure(const QString& file_path);
    void requestStop();

signals:
    void lineRead(QString line);

protected:
    void run();

private:
    bool isStopRequested();

    QString m_file_path;

    QMutex m_mutex;
    bool m_stop_requested;
};

#endif // FILE_LINE_READER_H
