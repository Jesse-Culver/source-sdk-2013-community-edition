#pragma once

#include "lua/lua.hpp"
#include "../../IScriptingLanguage.h"

class DLL_API CLuaLanguage : public IScriptingLanguage
{
private:

	lua_State* L;

	// TODO: this limits our # of hooks
	int hooks[128];

public:
	CLuaLanguage();
	~CLuaLanguage()	{};

	void Initialize();
	void Terminate();

	void SetGlobal(const char* name, Value v);

	void AddHook(const char* name, ScriptHook id);
	bool CallHook(ScriptHook id, ...);

	void AddBind(const char* name, ScriptBind fn);

	const char* GetFileExt() const {return "lua";}

	size_t GetMemoryUsage();


	void DoString(const char* string);


	// Lua Specific

private:
	int RegHook(lua_State* L);
};

