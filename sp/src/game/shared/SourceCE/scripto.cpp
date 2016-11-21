#include "cbase.h"
#include "scripto.h"

CScriptManager g_scriptManager;

using namespace scripto;

CVirtualMachine* scripto::vm;

void Scripto_Init()
{

	//g_scriptManager.AddLanguage(new CLuaLanguage());

	//vm = new CVirtualMachine();
	//g_scriptManager.AddLanguage(vm);

	g_scriptManager.AddHook("DLLInit");
	g_scriptManager.AddHook("PostInit");
	g_scriptManager.AddHook("GameInit");
	g_scriptManager.AddHook("LevelInit");

	g_scriptManager.AddHook("ClientConnect");
	g_scriptManager.AddHook("ClientActive");

	g_scriptManager.AddHook("GameShutdown");
	g_scriptManager.AddHook("LevelShutdown");
	g_scriptManager.AddHook("DLLShutdown");
}