#pragma once

// Public Headers
#include <utlvector.h>
#include <iclientunknown.h>
#include <iclientthinkable.h>


#include "client_thinklist.h"

#include "Component.h"
#include "Transform.h"


class Entity : public IClientUnknown, public IClientThinkable
{
	friend class Component;
private:
	CBaseHandle refEHandle;
	ClientThinkHandle_t hThink = INVALID_THINK_HANDLE;

	CUtlVector<Component*> components;
public:

private:

	void RemoveComponent(Component* comp);

public:
	Entity();
	~Entity();

	Transform* GetTransform() const { return static_cast<Transform*>(components[0]); }


	


// IHandleEntity
	void SetRefEHandle(const CBaseHandle &handle) { refEHandle = handle; }
	const CBaseHandle& GetRefEHandle() const { return refEHandle; }

// IClientThinkable
	virtual void				ClientThink() {}

	// Called when we're added to the think list.
	virtual ClientThinkHandle_t	GetThinkHandle() { return hThink; }
	virtual void				SetThinkHandle(ClientThinkHandle_t thinkHandle) { hThink = thinkHandle; }

	// Called by the client when it deletes the entity.
	virtual void				Release() = 0;

// Conversion Methods
	virtual IClientUnknown*		GetIClientUnknown() { return this; }
	virtual ICollideable*		GetCollideable() = 0;
	virtual IClientNetworkable*	GetClientNetworkable() = 0;
	virtual IClientRenderable*	GetClientRenderable() = 0;
	virtual IClientEntity*		GetIClientEntity() = 0;
	virtual C_BaseEntity*		GetBaseEntity() = 0;
	virtual IClientThinkable*	GetClientThinkable() { return this; };
};