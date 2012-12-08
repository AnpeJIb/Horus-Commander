#ifndef CONSOLE_PARSER_H
#define CONSOLE_PARSER_H

#include "common_parser.h"

class ConsoleParser : public CommonParser
{
public:
    ConsoleParser();

protected:
    int fileDescriptor();
    void readLine(int fd, char* line, int lineLen, int offset, RL_STAT* stat);
    void parseString(const QString& str);
};

#endif // CONSOLE_PARSER_H
