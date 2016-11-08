#include "cbase.h"
#include "scripto.h"

#include "tier0/memdbgon.h"

using namespace scripto;

CON_COMMAND(scripto_status, "")
{
	ScriptLog("[Server]");
	ScriptLog("Langauges: %i", g_scriptManager.CountLanguages());

	
}

CON_COMMAND(vm_test, "")
{
	
}

CON_COMMAND(vm_status, "")
{
	
}

CON_COMMAND(vm_get_reg, "")
{
	if (args.ArgC() > 1)
	{
		int regId = atoi(args[1]);
		ScriptLog("Register #%i: [%s]", regId, VMTypeNames[vm->G.registry.Get(regId).type]);
	}
}

CON_COMMAND(vm_get_reg_glboals, "")
{
	ScriptLog("Globals: R#%i", REG_IDX_GLOBALS);
}