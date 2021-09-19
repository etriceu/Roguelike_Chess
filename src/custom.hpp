#ifndef CUSTOM_HPP_INCLUDED
#define CUSTOM_HPP_INCLUDED

#include <cstdarg>
#include <cstdio>

using namespace std;

#define LEN(arr) ((size_t) (sizeof(arr)/sizeof(arr)[0]))
#define LOG_FILE "log.txt"

inline void clearLog()
{
	FILE *log = fopen(LOG_FILE, "w");
	fclose(log);
}

inline void log(const char *format, ...)
{
	FILE *log = fopen(LOG_FILE, "a");

	va_list arg;
	va_start(arg, format);
	vfprintf(stdout, format, arg);
	va_end (arg);
	va_start(arg, format);
	vfprintf(log, format, arg);
	va_end (arg);
	fclose(log);
}

#endif // CUSTOM_HPP_INCLUDED
