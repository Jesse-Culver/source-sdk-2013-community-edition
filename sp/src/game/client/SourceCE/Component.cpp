#include "cbase.h"
#include "Entity.h"
#include "Component.h"

void Component::operator delete(void* ptr, std::size_t sz)
{
	// TODO maybe check for nullptr
	Component* comp = (Component*)ptr;
	comp->entity->RemoveComponent(comp);

	::operator delete(ptr);
}
