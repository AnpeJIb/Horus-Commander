#include "common_parser.h"

#include <time.h>
#include <unistd.h>

CommonParser::CommonParser(QObject *parent) :
    QThread(parent)
{
}

void CommonParser::stop()
{
    m_doRun=false;
    wait();
}

void CommonParser::run()
{
    int lineLen = 2048;
    char line[lineLen];
    int offset = 0;
    RL_STAT stat;
    QString qline;

    int fd = fileDescriptor();

    while(m_doRun)
    {
        readLine(fd, line, lineLen, offset, &stat);
        if (stat.finished == false)
        {
            offset += stat.length;
            usleep(300*1000);
        } else {
            offset = 0;
            qline = QString(line);
            parseString(qline);
        }
    }
}
