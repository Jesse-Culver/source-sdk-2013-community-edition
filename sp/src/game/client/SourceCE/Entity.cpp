#include "cbase.h"
#include "Entity.h"



Entity::Entity()
{
	components[0] = new Transform();
}

Entity::~Entity()
{

}

void Entity::RemoveComponent(Component* comp)
{
	
}