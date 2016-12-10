// cbase.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#ifdef SCRIPTO_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

// standard libs
#include <cstdarg>

// tier1
#include <Color.h>

#include "tier1\utlvector.h"

#ifndef SOURCE_ENGINE
typedef unsigned int uint;
#endif 




void _Msg(const Color& clr, const char* pMsg, char* buffer);

#include "util.h"

//
//	DEFINES
//

#define COLOR_RED		Color(255, 64, 64, 255)
#define COLOR_BLUE		Color(153, 204, 255, 255)
#define COLOR_YELLOW	Color(255, 178, 0, 255)
#define COLOR_GREEN		Color(153, 255, 153, 255)
#define COLOR_GREY		Color(204, 204, 204, 255)
#define COLOR_WHITE		Color(255, 255, 255, 255)
#define COLOR_BLACK		Color(0, 0, 0, 255)
#define COLOR_CYAN		Color(0, 255, 255, 255)
#define COLOR_ORANGE	Color(255, 127, 0, 255)

typedef int ScriptHook;