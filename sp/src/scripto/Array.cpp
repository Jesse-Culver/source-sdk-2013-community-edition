
#include "cbase.h"
#include "Array.h"

SCArray::SCArray(unsigned int size) : size(size), capacity(0)
{
	values = new Value[capacity];
	for (unsigned int i = 0; i < size; i++) { values[i] = Value(); }
}

SCArray::~SCArray()
{
	delete[] values;
}

void SCArray::Set(unsigned idx, Value value)
{
	if (size == capacity)
	{
		capacity *= 2;
		Value* newArray = new Value[capacity];

		for (unsigned int i = 0; i < size; i++) { newArray[i] = values[i]; }
		delete[] values;

		values = newArray;

	}
	values[idx] = value;
	size++;
}
