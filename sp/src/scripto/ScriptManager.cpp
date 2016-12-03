#include "cbase.h"
#include "ScriptManager.h"

#include "tier1\utlvector.h"

// For-Each Language (i) In (languages)
#define INVOKE for (int i = 0; i < languages->Count(); i++)


CScriptManager::CScriptManager()
{
	languages = new CUtlVector<IScriptingLanguage*>();
	hooks = new CUtlVector<const char*>();
	bindNames = new CUtlVector<const char*>();
	binds = new CUtlVector<ScriptBind*>();
}

void CScriptManager::Terminate()
{
	INVOKE {
		languages->Element(i)->Terminate();
	}
}

int CScriptManager::AddLanguage(IScriptingLanguage* language)
{
	languages->AddToTail(language);
	language->Initialize();
	return languages->Count();
}


void CScriptManager::SetGlobal(const char* name, Value v)
{
	INVOKE {
		languages->Element(i)->SetGlobal(name, v);
	}
}


ScriptHook CScriptManager::AddHook(const char* name)
{
	ScriptHook id = hooks->AddToTail(name);

	ScriptLog("Added Hook: [#%i] %s", id, name);

	INVOKE {
		languages->Element(i)->AddHook(name, id);
	}

	return id;
}

bool CScriptManager::CallHook(ScriptHook id, Value args)
{
	bool bSuccess = true;

	INVOKE {
		bSuccess &= languages->Element(i)->CallHook(id, args);
	}

	return bSuccess;
}

void CScriptManager::AddBind(const char* name, ScriptBind fn)
{
	ScriptLog("Bound Function: %s", name);

	bindNames->AddToTail(name);
	binds->AddToTail(&fn);

	INVOKE {
		languages->Element(i)->AddBind(name, fn);
	}
}