#pragma once

#include "cbase.h"
#include <functional>

#include "TaggedValue.h"

typedef Value (*ScriptBind)(Value args);

class DLL_API IScriptingLanguage
{
	friend class CScriptManager;

public:

	IScriptingLanguage()			{};
	virtual ~IScriptingLanguage()	{};

	virtual void Initialize()=0;
	virtual void Terminate()=0;

	virtual void SetGlobal(const char* name, Value v) = 0;

	// Register a hook
	virtual void AddHook(const char* name, ScriptHook id)=0;

	// Call a hook and coerce its return to a bool
	virtual bool CallHook(ScriptHook id, ...) = 0;

	virtual void AddBind(const char* name, ScriptBind fn) = 0;

	// Amount of memory in use (in bytes)
	virtual size_t GetMemoryUsage()=0;

	virtual const char* GetFileExt() const = 0;

	virtual void DoString(const char* string) = 0;
};

