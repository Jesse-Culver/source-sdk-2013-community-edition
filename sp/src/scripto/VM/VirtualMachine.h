// Scripto Virtual Machine CONCEPT
// Based off of Lua VM

#pragma once

#include "../IScriptingLanguage.h"

#include "VMInstruction.h"
#include "VMTypes.h"
#include "VMState.h"


class DLL_API CVirtualMachine : public IScriptingLanguage
{
private:
	
public:
	VMGlobalState G;

	CVirtualMachine() 
	{
		VM_CLASS_CONSTRUCTOR(CVirtualMachine);
	}

	~CVirtualMachine()
	{
		VM_CLASS_DESTRUCTOR(CVirtualMachine);
	}
	
	void Initialize()
	{
		G.InitRegistry();
	}

	void Terminate()
	{
		
	}

	void AddHook(const char* name) {}
	bool CallHook(const char* name, ...) {return true;}

	size_t GetMemoryUsage()
	{
		return 0;
	}

	// Execute from PC to next return
	void Exexcute(VMState* S);


};