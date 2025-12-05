#ifndef IO_H
#define IO_H
#include <stddef.h>

void print(const char *str);
void print_num(long num);
char *readline(char *buf, size_t bufSize);
#endif