#include "console_parser.h"
#include "status_print.h"
#include "server_commander.h"

ConsoleParser::ConsoleParser()
{
}

int ConsoleParser::fileDescriptor()
{
    return SC::CONSOLE.socketDescriptor();
}

void ConsoleParser::readLine(int fd, char *line, int lineLen, int offset, RL_STAT *stat)
{
    Q_UNUSED(fd)
    return SC::CONSOLE.console_line_rd(line, lineLen, offset, stat);
}

void ConsoleParser::parseString(const QString &str)
{
    STATUS_PRINT::DEBUG_(str);
}
