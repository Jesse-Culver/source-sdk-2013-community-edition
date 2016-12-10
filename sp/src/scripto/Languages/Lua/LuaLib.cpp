#include "cbase.h"
#include "Array.h"
#include "TaggedValue.h"
#include "LuaLib.h"

// push scripto value
void PushValue(lua_State* L, Value v)
{
	switch (v.type)
	{
		case SC_BOOL:
			lua_pushboolean(L, v.b);
			break;
		case SC_INT:
			lua_pushinteger(L, v.i);
			break;
		case SC_FLOAT:
			lua_pushnumber(L, v.f);
			break;
		case SC_NULL:
			lua_pushnil(L);
			break;
		case SC_STRING:
			lua_pushstring(L, v.str);
			break;
			// TODO: other types
		case SC_ARRAY:
		case SC_OBJECT:
		case SC_FUNCTION:
		default:
			break;
	}
}

// internall call function
int _lua_call(lua_State* L)
{
	ScriptBind fn;

	// cast upvals[1] to a function pointer
	// upvals[1] in this case is set in CLuaLanguage::AddBind
	fn = (ScriptBind)(lua_tointeger(L, lua_upvalueindex(1)));

	// number of args is on top of the stack
	int nargs = lua_gettop(L);

	SCArray arr;
	for (int i = 1; i <= nargs; i++)
	{
		switch (lua_type(L, i))
		{
			case LUA_TBOOLEAN:
				arr[i-1] = Value(lua_toboolean(L, i));
				break;
			case LUA_TSTRING:
				arr[i-1] = Value(lua_tostring(L, i));
				break;
			case LUA_TNIL:
				arr[i-1] = Null;
				break;
			case LUA_TNUMBER:
				if (lua_isinteger(L, i))
					arr[i-1] = Value((int)lua_tointeger(L, i));
				else
					arr[i-1] = Value((float)lua_tonumber(L, i));
				break;
				// TODO: other types
			default:
				break;
		}
	}

	Value ret;

	if (nargs == 1)
		ret = fn(arr[0]);
	else
		ret = fn(&arr);

	if (ret.type == SC_NULL) {
		return 0;
	} else if (ret.type == SC_ARRAY) {
		// copy array to stack
		for (uint i = 0; i < ret.arr->Size(); i++)
			PushValue(L, (*ret.arr)[i]);
		// return size
		return ret.arr->Size();
	} else {
		// copy value to stack
		PushValue(L, ret);
		return 1;
	}
}

// standard error()
int _lua_error(lua_State* L)
{
	// The error message is on top of the stack.
	// Fetch it, print it and then pop it off the stack.
	const char* message = luaL_tolstring(L, -1, NULL);

	ScriptError(message);

	return 0;
}


// standard print()
int _lua_print(lua_State *L)
{
	int n = lua_gettop(L);  /* number of arguments */
	int i;
	lua_getglobal(L, "tostring");
	for (i=1; i<=n; i++) {
		const char *s;
		size_t l;
		lua_pushvalue(L, -1);  /* function to be called */
		lua_pushvalue(L, i);   /* value to print */
		lua_call(L, 1, 1);
		s = lua_tolstring(L, -1, &l);  /* get result */
		if (s == NULL)
			return luaL_error(L, "'tostring' must return a string to 'print'");
		if (i>1) lua_writestring("\t", 1);

		ScriptLog(s);

		lua_pop(L, 1);  /* pop result */
	}
	return 0;
}

// standard tostring()
int _lua_tostring(lua_State *L)
{
	luaL_checkany(L, 1);
	luaL_tolstring(L, 1, NULL);
	return 1;
}

// helper function for pairs()
static int pairsmeta(lua_State *L, const char *method, int iszero,
					 lua_CFunction iter)
{
	if (luaL_getmetafield(L, 1, method) == LUA_TNIL) {  /* no metamethod? */
		luaL_checktype(L, 1, LUA_TTABLE);  /* argument must be a table */
		lua_pushcfunction(L, iter);  /* will return generator, */
		lua_pushvalue(L, 1);  /* state, */
		if (iszero) lua_pushinteger(L, 0);  /* and initial value */
		else lua_pushnil(L);
	} else {
		lua_pushvalue(L, 1);  /* argument 'self' to metamethod */
		lua_call(L, 1, 3);  /* get 3 values from metamethod */
	}
	return 3;
}

int _lua_next(lua_State *L)
{
	luaL_checktype(L, 1, LUA_TTABLE);
	lua_settop(L, 2);  /* create a 2nd argument if there isn't one */
	if (lua_next(L, 1))
		return 2;
	else {
		lua_pushnil(L);
		return 1;
	}
}


int _lua_pairs(lua_State *L)
{
	return pairsmeta(L, "__pairs", 0, _lua_next);
}


int _lua_listen(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	ScriptLog("[Lua] Added Listener to Hook %s", name);

	// TODO: Actually add listener
	// use luaL_ref or something

	return 0;
}

luaL_Reg regList[] = {

	{ "tostring", _lua_tostring },
	{ "error", _lua_error },
	{ "print", _lua_print },
	{ "pairs", _lua_pairs },
	{ "next", _lua_next },
	{ "listen", _lua_listen },

	{ "_G", NULL },
	{ "_VERSION", NULL },

	{ NULL, NULL }
};


int luaopen_base_new(lua_State *L) {

	lua_pushglobaltable(L);

	int globals = lua_absindex(L, -1);

	luaL_setfuncs(L, regList, 0);
	
	lua_pushvalue(L, globals);
	lua_setfield(L, globals, "_G");
	
	lua_pushliteral(L, LUA_VERSION);
	lua_setfield(L, globals, "_VERSION");

	return 1;
}