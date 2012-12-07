#ifndef COMMON_PARSER_H
#define COMMON_PARSER_H

#include <QThread>
#include "file.h"

class CommonParser : public QThread
{
    Q_OBJECT
public:
    explicit CommonParser(QObject *parent = 0);
    
    void stop();

protected:
    void run();

    virtual int fileDescriptor() = 0;
    virtual void readLine(int fd, char* line, int lineLen, int offset, RL_STAT* stat) = 0;
    virtual void parseString(const QString& str) = 0;

private:
    bool m_doRun;
};

#endif // COMMON_PARSER_H
