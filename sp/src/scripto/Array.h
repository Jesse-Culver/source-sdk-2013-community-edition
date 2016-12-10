
#pragma once
#include "cbase.h"

#include "TaggedValue.h"

/****************************************
 SCArray
	Numerically Indexed Array
****************************************/
class DLL_API SCArray
{
private:
	Value* values;

	// Size
	uint size;

	// Allocated Size
	uint capacity;
public:


	/// Constructors ///

	SCArray(uint size = 2);
	~SCArray();

	/// Mutators ///

	void Set(uint idx, const Value value);

	/// Inspectors / Accessors ///

	// Constant Reference to VMArray[i]
	inline const Value& Get(uint idx) const { return idx < size - 1 ? values[idx] : Null; }

	// Constant Reference to VMArray[i]
	const Value& operator[](uint i) const { return Get(i); };

	// Unsafe Reference to VMArray[i]
	Value& operator[](uint i) { return values[i]; };


	inline const uint Size() const { return size; }
	inline const uint Capacity() const { return capacity; }
};