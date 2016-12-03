#ifndef _SCRIPT_MANAGER_H
#define _SCRIPT_MANAGER_H
#pragma once

#include "cbase.h"

#include "IScriptingLanguage.h"
#include "TaggedValue.h"


//#pragma warning (disable : 4251)

/*template class DLL_API CUtlMemory < IScriptingLanguage* >;
template class DLL_API CUtlMemory < const char* >;
template class DLL_API CUtlMemory < ScriptBind* >;

template class DLL_API CUtlVector < IScriptingLanguage* >;
template class DLL_API CUtlVector < const char* >;
template class DLL_API CUtlVector < ScriptBind* >;*/



class DLL_API CScriptManager
{
private:
	
	CUtlVector<IScriptingLanguage*>* languages;
	CUtlVector<const char*>* hooks;
	
	// parallel lists of bound functions
	CUtlVector<const char*>* bindNames;
	CUtlVector<ScriptBind*>* binds;
	
public:
	CScriptManager();
	~CScriptManager() {Terminate();}

	// Add an IScriptingLanguage to the script manager
	// and return the language's internal ID
	int AddLanguage(IScriptingLanguage* language);
	
	// Gets the IScriptingLanguage at ID for direct use
	IScriptingLanguage* GetLanguage(int id) { return languages->Element(id); }

	int CountLanguages() { return languages->Count(); }

	// Destroys the script engine.
	void Terminate();

	/************************************************************
		Globals
	************************************************************/

	void SetGlobal(const char* name, Value v);

	/************************************************************
	 Hooks:
		Script functions that can be called from C++
	************************************************************/

	// Register a hook
	ScriptHook AddHook(const char* name);

	// Call a hook, args are typically passed as an array
	// returns a true or false coerced from all of the hook returns

	// TODO: Calling hooks by name is inefficient and can cause severe
	// problems if a hook that doesn't exist is called (especially in Lua)
	bool CallHook(ScriptHook id, Value args = Null);

	// Get a list of all hook names
	CUtlVector<const char*>* GetHooks() { return hooks; }

	/************************************************************
	 Binds:
		C++ functions that can be called from scripts
	************************************************************/

	void AddBind(const char* name, ScriptBind fn);
	
	CUtlVector<const char*>* GetBinds() { return bindNames; }
	
};

#endif