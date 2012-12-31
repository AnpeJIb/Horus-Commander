#include "file_logger.h"
#include <QDateTime>

#include "log_config.h"
#include "bitwise.h"

#include <iostream>
using namespace std;

FileLogger::FileLogger(QString filename)
    : Logger(Config::Log::LOG_FILE),
      outFormat("hh:mm:ss/d.MM.yy")
{
    stream = NULL;

    file = new QFile(filename);

    if (file->open(QFile::WriteOnly | QFile::Truncate))
        stream = new QTextStream(file);
}

FileLogger::~FileLogger()
{
    if (stream!=NULL)
    {
        stream->device()->close();
        delete stream;
    }

    delete file;
}

void FileLogger::taskNew(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_TASKS)==0) return;
    stack.push(str);
    printStr("BUSY", str);
}

void FileLogger::taskDone()
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_TASKS)==0) return;
    printStr("DONE", stack.pop());
}

void FileLogger::taskFail()
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_TASKS)==0) return;
    printStr("FAIL", stack.pop());
}

void FileLogger::msgDebug(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_DEBUG)==0) return;
    printStr("DBG ", str);
}

void FileLogger::msgInfo(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_INFO)==0) return;
    printStr("INFO", str);
}

void FileLogger::msgWarning(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_WARNING)==0) return;
    printStr("WARN", str);
}

void FileLogger::msgError(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_ERROR)==0) return;
    printStr("ERR ", str);
}

void FileLogger::printStr(const QString &prefix, const QString &str)
{
    *stream << "["
            << prefix
            << " : "
            << QDateTime::currentDateTime().toString(outFormat)
            << "] "
            << str
            << endl;
    stream->flush();
}
