#include "common_parser.h"
#include "str.h"

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
    m_doRun=true;

    while(m_doRun)
    {
        readLine(fd, line, lineLen, offset, &stat);
        if (stat.finished == false)
        {
            offset += stat.length;
            usleep(300*1000);
        } else {
            offset = 0;
            STR::nullTermitate(line);
            qline = QString(line);
            parseString(qline);
        }
    }
}
