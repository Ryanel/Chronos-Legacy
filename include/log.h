#ifndef LOG_H
#define LOG_H
#ifdef DEBUG
#include <chronos/display/textmode.h>
inline void debug_printf(const char *format, ...)
{
	
	static char buf [1024];
	va_list args;
	int i;
	va_start(args, format);
	i = vsprintf(buf,format,args);
	va_end(args);
	buf[i] = '\0';
	tm_print(buf);
	
}
#else
inline void debug_printf(const char *format, ...)
{
	
	static char buf [1024];
	va_list args;
	int i;
	va_start(args, format);
	i = vsprintf(buf,format,args);
	va_end(args);
	buf[i] = '\0';
	
}
#endif
#endif
