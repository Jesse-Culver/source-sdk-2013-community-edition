#pragma once

#include "TaggedValue.h"
#include "VMInstruction.h"

// Macros to log when objects are created and destroyed
#define VM_CLASS_CONSTRUCTOR(type) {ScriptLog("New " ## #type " created at 0x%X.", this);}
#define VM_CLASS_DESTRUCTOR(type) {ScriptLog("Destroyed " ## #type " at 0x%X.", this);}



/****************************************
	VMArray
		Numerically Indexed Array
****************************************/
class DLL_API VMArray
{
private:
	Value* values;

	// Size
	unsigned int size;

	// Allocated Size
	unsigned int capacity;
public:
	

/// Constructors ///

	VMArray(unsigned int size = 2);
	~VMArray();

/// Mutators ///

	void Set(unsigned int idx, const Value value);

/// Inspectors / Accessors ///

	inline const Value& Get(unsigned idx) const { return idx < size - 1 ? values[idx] : Null; }

	// Constant VMArray[i]
	const Value& operator[](unsigned int i) const { return Get(i); };

	// Unsafe VMArray[i]
	Value& operator[](unsigned i) { return values[i]; };


	inline const unsigned int Size() const { return size; }
	inline const unsigned int Capacity() const { return capacity; }
};


/****************************************
	VM Function
****************************************/
struct VMFunction
{
	// Pointer to the first instruction.
	Instruction* code;

	// Array of all constants within this function
	VMArray constants;
};



/****************************************
	VM Object
****************************************/
struct VMObject
{

};


