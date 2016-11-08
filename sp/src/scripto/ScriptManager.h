#ifndef _SCRIPT_MANAGER_H
#define _SCRIPT_MANAGER_H
#pragma once

#include "cbase.h"

#include <functional>

#include "IScriptingLanguage.h"

//#ifdef SCRIPTO_EXPORTS

template class DLL_API CUtlMemory < IScriptingLanguage* >;
template class DLL_API CUtlMemory < const char* >;

template class DLL_API CUtlVector < IScriptingLanguage* >;
template class DLL_API CUtlVector < const char* >;

//#endif

class DLL_API CScriptManager
{
private:
	
	CUtlVector<IScriptingLanguage*> languages;
	CUtlVector<const char*> hooks;
	
public:
	CScriptManager();
	~CScriptManager() {};

	// Add an IScriptingLanguage to the script manager
	// and return the language's internal ID
	int AddLanguage(IScriptingLanguage* language);
	
	// Gets the IScriptingLanguage at ID for direct use
	IScriptingLanguage* GetLanguage(int id) { return languages[id]; }

	int CountLanguages() { return languages.Count(); }

	// Destroys the script engine.
	void Terminate();

	///////////////////////////////////////////////////////////
	// Hooks:
	//	Script functions that can be called from C++
	///////////////////////////////////////////////////////////

	// Register a hook
	void AddHook(const char* name);
	// Call a  hook
	// Currently only supports boolean return types
	bool CallHook(const char* name, ...);
	// Get a list of all hook names
	CUtlVector<const char*>* GetHooks() { return &hooks; };

	///////////////////////////////////////////////////////////
	// Binds:
	//	C++ functions that can be called from scripts
	///////////////////////////////////////////////////////////

	//template<typename R, typename... Args>
	//void AddBind(const char* name, void* func);
	
	// CUtlVector<const char*> GetBinds();
	
};

#endif