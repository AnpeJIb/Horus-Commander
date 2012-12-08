#ifndef STR_H
#define STR_H

namespace STR
{

void nullTermitate(char* str);
int copySymbols(char* src, int src_len, int max_count, int offset, char* dst, int dst_len);
void escapeUnicode(char* src, int src_len, char* dst, int dst_len);
void rmDoubleSymb(char* src, char *dst, char symb);

}

#endif // STR_H
