#ifndef GSCOMMAND_H
#define GSCOMMAND_H

#include <QString>

class GsCommands
{
public:
    static QString get_GC();
    static QString get_RUN_FILE(QString relativePath);
    static QString get_TIMEOUT(int secondsDelay, QString cmd);
    static QString get_EXIT();
};

#endif // GSCOMMAND_H
