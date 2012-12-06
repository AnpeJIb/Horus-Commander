#include "str.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void STR::escapeUnicode(char* src, int src_len, char* dst, int dst_len)
{
    char* s_end = src+src_len;
    char* d_end = dst+dst_len;

    int code_len = 4;
    char code[code_len+1];
    memset(&code, '\0', code_len+1);

    while((src < s_end) && (dst < d_end))
    {
        if ((unsigned char)*src < 0x80){
            *(dst++) = *(src++);
        } else {
            if (dst >= (d_end-code_len-2)) break;
            *(dst++) = '\\';
            *(dst++) = 'u';
            sprintf(code, "%04x",                   // from sequence
                    (                               // AAAxxxxx BByyyyyy
                        ((*(src) & 0x1F) << 6) |	// cut AAA by 0x1F
                        ((*(src+1)) & 0x3F)			// cut BB  by 0x3F
                     )								// and get xxxxxyyyyyy
                    );
            src += 2;

            *(dst++) = *code;
            *(dst++) = *(code+1);
            *(dst++) = *(code+2);
            *(dst++) = *(code+3);
        }
    }
    *dst = '\0';
}

void STR::rmDoubleSymb(char* src, char *dst, char symb)
{
    char* end = src+strlen(src);

    while (1)
    {
        if (src == NULL) break;
        if (src != end)
            if (((*src)==symb) && ((*(src+1))==symb))
                src++;

        (*dst) = (*src);

        if (src == end) break;
        src++;
        dst++;
    }

    *(dst++) = '\0';
}