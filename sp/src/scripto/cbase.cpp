// cbase.cpp : source file that includes just the standard includes
// Scripto.pch will be the pre-compiled header
// cbase.obj will contain the pre-compiled type information

#include "cbase.h"

#include <tier0/dbg.h>

void _Msg(const Color& clr, const char* pMsg, char* buffer)
{
	
#ifdef SOURCE_ENGINE
	ConColorMsg(clr, pMsg, buffer);
#else
	printf(pMsg, buffer);
#endif
}