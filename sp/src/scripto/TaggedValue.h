/**************************************************
	TaggedValue.h
		Interlingual tagged value type.
**************************************************/

#pragma once

class SCArray;
struct SCFunction;
struct SCObject;

/****************************************
Tagged Values
****************************************/

enum TypeTag {
	SC_NULL, SC_INT, SC_BOOL, SC_FLOAT, SC_STRING, SC_FUNCTION, SC_ARRAY, SC_OBJECT
};

static const char* SCTypeNames[] = { "NULL", "INT", "BOOL", "FLOAT", "STRING", "FUNCTION", "ARRAY", "OBJECT" };

struct Value
{
	TypeTag type;

	union {
		int i;
		bool b;
		float f;
		const char* str;

		SCArray* arr;
		SCFunction* func;
		SCObject* obj;
	};

	Value() : type(SC_NULL) {}
	Value(int i) : type(SC_INT), i(i) {}
	Value(bool b) : type(SC_BOOL), b(b) {}
	Value(float f) : type(SC_FLOAT), f(f) {} 
	Value(const char* str) : type(SC_STRING), str(str) {}

	Value(SCArray* arr) : type(SC_ARRAY), arr(arr) {}
	Value(SCFunction* func) : type(SC_FUNCTION), func(func) {}
	Value(SCObject* obj) : type(SC_OBJECT), obj(obj) {}

	const char* GetTypeName() {return SCTypeNames[type];}
};

const Value Null;