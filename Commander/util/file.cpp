#include "file.h"

#include <QFile>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "str.h"

#ifdef _WIN32_
void hnd_line_rd(HANDLE hFile, char* line, int size, int offset, RL_STAT* stat)
{
    DWORD readcount = 0;
    BOOL success = FALSE;
    unsigned char c;

    (*stat).finished = false;

    for ((*stat).length = 0; (*stat).length < size-offset-1; (*stat).length++)
    {
        success = ReadFile(hFile, &c, 1, &readcount, NULL);

        if( (success == FALSE) || (readcount == 0) ) return;

        *line = c;
        line++;
        if (c == '\n')
            break;
    }

    (*stat).finished = true;
    *line=0;
}
#endif

void line_rd(int fd, char* line, int size, int offset, RL_STAT* stat)
{
    int readcount = 0;
    unsigned char c;

    (*stat).finished = false;
    (*stat).isEOF = false;

	for ((*stat).length = 0; (*stat).length < size-offset-1; (*stat).length++)
	{
		readcount = read(fd, &c, 1);
		if (readcount == 1)
		{
			*line = c;
			line++;
			if (c == '\n')
				break;
        } else {
            (*stat).isEOF = true;
            return;
        }
	}
    (*stat).finished = true;
    *line=0;
}

void line_wr(int fd, char* line, int size)
{
	int done = 0;
	int tx;
	while (done<size)
	{
		tx = write(fd, line, size);
		if (tx <0 ) break;
		done += tx;
	}
}

void rmDoubleSymbInFile(QString fPath, char symb)
{
    if (QFile(fPath).exists()==false) return;

    QString fPathBak = fPath+".bak";

    /** Create temporary file */

    QFile fBak(fPathBak);
    fBak.open(QIODevice::WriteOnly);
    fBak.close();

    int line_len = 255;
    char lineIn[line_len];
    char lineOut[line_len];

    int offset = 0;
    RL_STAT stat;

    int streamIn    = open(fPath.toStdString().c_str(),     O_RDONLY);
    int streamOut   = open(fPathBak.toStdString().c_str(),  O_RDWR);

    /** Do work */

    while(1)
    {
        line_rd(streamIn, lineIn, line_len, offset, &stat);

        if (stat.finished == false)
        {
            offset += stat.length;
        } else {
            offset = 0;
            STR::rmDoubleSymb(lineIn, lineOut, symb);
            line_wr(streamOut, lineOut, strlen(lineOut));
        }

        if (stat.isEOF) break;
    }

    close(streamIn);
    close(streamOut);

    /** Replace original with temporary file */

    QFile::remove(fPath);
    QFile::rename(fPathBak,fPath);
}
