#ifndef LOGGER_FILE_LOGGER_H
#define LOGGER_FILE_LOGGER_H

#include "logger.h"
#include <QFile>
#include <QTextStream>
#include <QStack>

class FileLogger : public QObject, public Logger
{
    Q_OBJECT
public:
    FileLogger(QString filename);
    ~FileLogger();

public slots:
    void taskNew(QString str);
    void taskDone();
    void taskFail();

    void msgDebug(QString str);
    void msgInfo(QString str);
    void msgWarning(QString str);
    void msgError(QString str);

private:
    void printStr(const QString& prefix, const QString& str);

    QFile* file;
    QTextStream* stream;
    QStack<QString> stack;
    QString outFormat;
};

#endif // LOGGER_FILE_LOGGER_H
