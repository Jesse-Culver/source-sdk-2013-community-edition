#include "cbase.h"
#include "scripto.h"
#include "tier1\utlvector.h"
#include "filesystem.h"
#include "utlbuffer.h"

#include "tier0\memdbgon.h"

CScriptManager g_scriptManager;
IScriptingLanguage* lua;

void DoFile(IScriptingLanguage* lang, const char* pFullPath)
{
	CUtlBuffer buf;
	if (filesystem->ReadFile(pFullPath, "GAME", buf))
	{
		ScriptLog("Including: %s", pFullPath);

		char* file = new char[buf.Size() + 1];
		buf.GetString(file);
		file[buf.Size()] = 0;

		lua->DoString(file);

		delete[] file;
	}
}



void Scripto_Register()
{
	lua = new CLuaLanguage();
	g_scriptManager.AddLanguage(lua);

	g_scriptManager.AddHook("DLLInit");
	g_scriptManager.AddHook("PostInit");
	g_scriptManager.AddHook("GameInit");
	g_scriptManager.AddHook("LevelInit");

	g_scriptManager.AddHook("ClientConnect");
	g_scriptManager.AddHook("ClientActive");

	g_scriptManager.AddHook("GameShutdown");
	g_scriptManager.AddHook("LevelShutdown");
	g_scriptManager.AddHook("DLLShutdown");



	char* scriptPath = "scripts/scripts/init/*.lua";

	FileFindHandle_t findHandle;

	const char *pFilename = filesystem->FindFirstEx(scriptPath, "GAME", &findHandle);
	while (pFilename) {

		char pFullPath[MAX_PATH] = "scripts/scripts/init/";

		V_strcat(pFullPath, pFilename, MAX_PATH);

		CUtlBuffer buf;
		if (filesystem->ReadFile(pFullPath, "GAME", buf))
		{
			ScriptLog("Including: %s", pFullPath);

			char* file = new char[buf.Size() + 1];
			buf.GetString(file);
			file[buf.Size()] = 0;

			lua->DoString(file);

			delete[] file;
		}

		
		pFilename = filesystem->FindNext(findHandle);
	}

	filesystem->FindClose(findHandle);
}


#ifndef CLIENT_DLL

CON_COMMAND(script_list_hooks, "")
{
	CUtlVector<const char*>* hooklist = g_scriptManager.GetHooks();

	for (int i = 0; i < hooklist->Size(); i++)
		ScriptLog(hooklist->Element(i));
}

CON_COMMAND(script_list_binds, "")
{
	CUtlVector<const char*>* list = g_scriptManager.GetBinds();

	for (int i = 0; i < list->Size(); i++)
		ScriptLog(list->Element(i));
}


static void _lua(const CCommand &args)
{
	lua->DoString(args.ArgS());
}
static ConCommand lua_command("lua", _lua, "");

CON_COMMAND(lua_dofile, "")
{
	DoFile(lua, args.ArgS());
}


#endif