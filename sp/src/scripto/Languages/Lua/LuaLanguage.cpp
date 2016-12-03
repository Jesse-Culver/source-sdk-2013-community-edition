#include "cbase.h"
#include "LuaLanguage.h"
#include "TaggedValue.h"
#include "Array.h"
#include "LuaLib.h"

#include "tier1\utlvector.h"
#include "tier0\memdbgon.h"

#define LUA_GLOBALNAME "_G"



luaL_Reg libs[] = {
	{ "_G", luaopen_base_new },
	//{ LUA_LOADLIBNAME, luaopen_package },
	//{ LUA_COLIBNAME, luaopen_coroutine },
	//{ LUA_TABLIBNAME, luaopen_table },
	//{ LUA_IOLIBNAME, luaopen_io },
	//{ LUA_OSLIBNAME, luaopen_os },
	//{ LUA_STRLIBNAME, luaopen_string },
	//{ LUA_MATHLIBNAME, luaopen_math },
	//{ LUA_UTF8LIBNAME, luaopen_utf8 },
	//{ LUA_DBLIBNAME, luaopen_debug },
	{ NULL, NULL }
};

CLuaLanguage::CLuaLanguage()
{
	ScriptLog("Added Language: Lua");
}

void CLuaLanguage::Initialize()
{
	ScriptLog("Added Language: Lua");

	L = luaL_newstate();
	lua_atpanic(L, _lua_error);
	
	const luaL_Reg *lib;

	// "require" functions from 'loadedlibs' and set results to global table
	for (lib = libs; lib->func; lib++) {
		ScriptLog("[Lua] Added Library: %s", lib->name);

		luaL_requiref(L, lib->name, lib->func, 1);
		lua_pop(L, 1);
	}
}

void CLuaLanguage::Terminate()
{
	lua_close(L);
}

void CLuaLanguage::SetGlobal(const char* name, Value v)
{
	PushValue(L, v);
	lua_setglobal(L, name);
}

int CLuaLanguage::RegHook(lua_State* L)
{
	return 0;
}

void CLuaLanguage::AddHook(const char* name, ScriptHook id)
{
	hooks[id] = 0;
}

bool CLuaLanguage::CallHook(ScriptHook id, ...)
{
	ScriptLog("[Lua] Hook Called: [#%i]", id);

	if (id >= sizeof(hooks)) {
		ScriptError("[Lua] Hook is out of bounds.");
		return true;
	}

	int hookIndex = hooks[id];

	if (!hookIndex) {
		ScriptError("[Lua] Hook is empty.");
		return true;
	}

	// registry[hookIdx]
	lua_rawgeti(L, LUA_REGISTRYINDEX, hookIndex);

	if (lua_isfunction(L, -1))
		lua_call(L, 0, 0);

	return true;
}

void CLuaLanguage::AddBind(const char* name, ScriptBind fn)
{
	// push the function address onto the stack
	lua_pushinteger(L, (long)fn);

	// push _lua_call onto the stack
	// with one associated value 
	// (that we just pushed onto the stack)
	lua_pushcclosure(L, _lua_call, 1);

	lua_setglobal(L, name);
}

size_t CLuaLanguage::GetMemoryUsage()
{
	// kb to b
	return lua_gc(L, LUA_GCCOUNT, NULL) * 1000;
}

void CLuaLanguage::DoString(const char* str)
{
	luaL_dostring(L, str);
}