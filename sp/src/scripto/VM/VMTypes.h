#pragma once

#include "VMInstruction.h"

#include "tier0/memdbgon.h"

// Macros to log when objects are created and destroyed
#define VM_CLASS_CONSTRUCTOR(type) {ScriptLog("New " ## #type " created at 0x%X.", this);}
#define VM_CLASS_DESTRUCTOR(type) {ScriptLog("Destroyed " ## #type " at 0x%X.", this);}

class VMArray;
struct VMFunction;
struct VMObject;

/****************************************
Tagged Values
****************************************/

enum VMType {
	VM_NULL, VM_INT, VM_BOOL, VM_FLOAT, VM_STRING, VM_FUNCTION, VM_ARRAY, VM_OBJECT
};

static const char* VMTypeNames[] = { "NULL", "INT", "BOOL", "FLOAT", "STRING", "FUNCTION", "ARRAY", "OBJECT" };

struct Value
{
	VMType type;

	union {
		int i;
		bool b;
		float f;
		const char* str;

		VMArray* arr;
		VMFunction* func;
		VMObject* obj;
	};

	Value() : type(VM_NULL) {}
	Value(bool b) : type(VM_BOOL), b(b) {}

	Value(VMArray* arr) : type(VM_ARRAY), arr(arr) {}
	Value(VMFunction* func) : type(VM_FUNCTION), func(func) {}
	Value(VMObject* obj) : type(VM_OBJECT), obj(obj) {}
};

const Value Null;

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


