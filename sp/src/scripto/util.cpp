#include "cbase.h"
#include "util.h"

#include <cstdio>

void ScriptLog(const char* msg, ...)
{
	char buf[256];

	va_list args;
	va_start(args, msg);
	
	vsprintf(buf, msg, args);

	va_end(args);

	_Msg(COLOR_CYAN, "[Script] %s\n", buf);
}

void ScriptError(const char* msg, ...)
{
	char buf[256];

	va_list args;
	va_start(args, msg);

	vsprintf(buf, msg, args);

	va_end(args);

	_Msg(COLOR_ORANGE, "[Script] %s\n", buf);
}