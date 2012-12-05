#include "file.h"

void printFile(QString fPath)
{
    QString cmd;

#ifdef _WIN32_
    cmd = "type";
#else
    cmd = "cat";
#endif
    cmd.append(" \"").append(fPath).append("\"");

    int i = system(cmd.toStdString().c_str());
    Q_UNUSED(i)
}
