#ifndef CUSTOM_HPP_INCLUDED
#define CUSTOM_HPP_INCLUDED

#include <cstdarg>
#include <cstdio>

using namespace std;

static string LOG_FILE = "log.txt";

inline void clearLog()
{
	FILE *log = fopen(LOG_FILE.c_str(), "w");
	fclose(log);
}

inline void log(const char *format, ...)
{
	FILE *log = fopen(LOG_FILE.c_str(), "a");

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
