#pragma once

#include "VMInstruction.h"
#include "VMTypes.h"

#include "tier0/memdbgon.h"

// Created when a function is called
// contains arguments, function info, etc
struct FunctionCall
{
	FunctionCall() {}

	// The function itself
	VMFunction* function;

	// First register for this function to use (as #0)
	unsigned int base;

	// The function that called this function.
	FunctionCall* caller;
};

// Global state
struct DLL_API VMGlobalState
{
	// Table of globals
	VMObject* globals;
	VMArray registry;

	VMGlobalState() { VM_CLASS_CONSTRUCTOR(VMGlobalState); }
	~VMGlobalState() { VM_CLASS_DESTRUCTOR(VMGlobalState); }

	void InitRegistry();
};

// Index of the main thread in the registry
//#define REG_IDX_MAIN_THREAD 0

// Index of the global table in the registry
#define REG_IDX_GLOBALS 0


// 'Per-thread' local state
struct VMState
{
public:
	const FunctionCall* currentFunction;
	const Instruction* PC;

	VMState() { VM_CLASS_CONSTRUCTOR(VMState); }
	~VMState() { VM_CLASS_DESTRUCTOR(VMState); }

};