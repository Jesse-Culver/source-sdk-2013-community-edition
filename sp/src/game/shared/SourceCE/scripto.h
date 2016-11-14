#pragma once

#include "scripto/scripto.h"
#include "scripto/lua.h"
#include "scripto/vm.h"

extern CScriptManager g_scriptManager;

namespace scripto
{
	extern CVirtualMachine* vm;
}

void Scripto_Init();