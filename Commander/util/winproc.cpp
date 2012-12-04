#include "winproc.h"
#include <windows.h>

void waitpid_win(int pid)
{
    HANDLE hProc;
    if ( (hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid)) )
    {
        WaitForSingleObject(hProc, INFINITE);
        CloseHandle(hProc);
    }
}
