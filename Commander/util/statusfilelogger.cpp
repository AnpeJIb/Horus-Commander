#include "statusfilelogger.h"
#include <QDateTime>

#include <iostream>
using namespace std;

StatusFileLogger::StatusFileLogger(QString filename)
{
    stream = NULL;

    file = new QFile(filename);

    if (file->open(QFile::WriteOnly | QFile::Truncate))
        stream = new QTextStream(file);
}

StatusFileLogger::~StatusFileLogger()
{
    if (stream!=NULL)
    {
        stream->device()->close();
        delete stream;
    }

    delete file;
}

void StatusFileLogger::statusNew(QString str)
{
    if ((level & StatusPrinter::TASKS)==0) return;
    stack.push(str);
    printStr(tr("BUSY"), str);
}

void StatusFileLogger::statusDone()
{
    if ((level & StatusPrinter::TASKS)==0) return;
    printStr(tr("DONE"), stack.pop());
}

void StatusFileLogger::statusFail()
{
    if ((level & StatusPrinter::TASKS)==0) return;
    printStr(tr("FAIL"), stack.pop());
}

void StatusFileLogger::msgInfo(QString str)
{
    if ((level & StatusPrinter::INFO)==0) return;
    printStr(tr("INFO"), str);
}

void StatusFileLogger::msgWarn(QString str)
{
    if ((level & StatusPrinter::WARNING)==0) return;
    printStr(tr("WARN"), str);
}

void StatusFileLogger::msgErr(QString str)
{
    if ((level & StatusPrinter::ERROR)==0) return;
    printStr(tr("ERR "), str);
}

void StatusFileLogger::printStr(const QString &prefix, const QString &str)
{
    *stream << "["
            << prefix
            << " : "
            << QDateTime::currentDateTime().toString()
            << "] "
            << str
            << endl;
    stream->flush();
}
