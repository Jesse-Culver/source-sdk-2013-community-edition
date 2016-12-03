#pragma once

#include "LuaLanguage.h"

#define LUA_FUNC(name)	int name(lua_State* L)

// Internal
LUA_FUNC(_lua_call);

LUA_FUNC(_lua_error);
LUA_FUNC(_lua_print);
LUA_FUNC(_lua_tostring);
LUA_FUNC(_lua_pairs);
LUA_FUNC(_lua_next);
LUA_FUNC(_lua_hook_add);

void PushValue(lua_State* L, Value v);

int luaopen_base_new(lua_State* L);