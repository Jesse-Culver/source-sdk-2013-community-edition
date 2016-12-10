#pragma once

class Entity;

class Component
{
	friend class Entity;
private:
	Entity* entity;
public:
	static void operator delete(void* ptr, std::size_t sz);


	Entity* GetEntity() const { return entity; }
	

};