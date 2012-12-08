#ifndef GS_FILE_H
#define GS_FILE_H

#include <QString>

typedef struct
{
	int length;
    bool finished;
    bool isEOF;
} RL_STAT;

#ifdef _WIN32_
    #include <windows.h>
    void hnd_line_rd(HANDLE hFile, char* line, int size, int offset, RL_STAT* stat);
#endif

void line_rd(int fd, char* line, int size, int offset, RL_STAT* stat);
void line_wr(int fd, const char *line, int size);

void rmDoubleSymbInFile(QString fPath, char symb);

#endif // GS_FILE_H
