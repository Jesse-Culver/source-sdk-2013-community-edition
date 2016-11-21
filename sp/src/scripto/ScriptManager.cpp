#include "cbase.h"
#include "ScriptManager.h"

// For-Each Language (i) In (languages)
#define INVOKE for (int i = 0; i < languages.Count(); i++)


CScriptManager::CScriptManager()
{
	
}

void CScriptManager::Terminate()
{
	INVOKE {
		languages[i]->Terminate();
	}
}

int CScriptManager::AddLanguage(IScriptingLanguage* language)
{
	languages.AddToTail(language);
	language->Initialize();
	return languages.Count();
}


void CScriptManager::SetGlobal(const char* name, int i)
{ INVOKE { languages[i]->SetGlobal(name, i); } }



void CScriptManager::AddHook(const char* name)
{
	ScriptLog("Added Hook: %s", name);

	hooks.AddToTail(name);

	INVOKE {
		languages[i]->AddHook(name);
	}
}

bool CScriptManager::CallHook(const char* name, ...)
{
	// TODO: System to pass all vargs

	va_list args;
	va_start(args, name);

	bool ret = true;

	INVOKE {
		ret &= languages[i]->CallHook(name, args);
	}
	
	va_end(args);
	
	return ret;
}