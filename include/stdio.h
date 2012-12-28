#ifndef STDIO_H
#define STDIO_H
#include <stdarg.h>
//Constants
#define EOF -1

//Printing and display
int vsprintf(char *buf, const char *fmt, va_list args);
void printf (const char *fmt, ...);

#endif
