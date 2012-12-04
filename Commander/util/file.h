#ifndef GS_FILE_H
#define GS_FILE_H

typedef struct
{
	int length;
    bool finished;
} RL_STAT;

#ifdef _WIN32_
    #include <windows.h>
    void hnd_line_rd(HANDLE hFile, char* line, int size, int offset, RL_STAT* stat);
#endif

void line_rd(int fd, char* line, int size, int offset, RL_STAT* stat);
void line_wr(int fd, char* line, int size);

#endif // GS_FILE_H
