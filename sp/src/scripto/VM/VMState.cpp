#include "cbase.h"
#include "VMState.h"


void VMGlobalState::InitRegistry()
{
	registry = VMArray();
	globals = new VMObject();
	


}