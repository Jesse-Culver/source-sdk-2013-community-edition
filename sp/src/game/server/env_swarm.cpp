#include "cbase.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

class CEnvSwarm : public CBaseAnimating
{
public:
	DECLARE_CLASS(CEnvSwarm, CBaseAnimating);
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();

	void Precache();
	void Spawn();
	
	void Think();

};

LINK_ENTITY_TO_CLASS(env_swarm, CEnvSwarm);

BEGIN_DATADESC(CEnvSwarm)
	DEFINE_THINKFUNC(Think)
END_DATADESC()

IMPLEMENT_SERVERCLASS_ST(CEnvSwarm, DT_EnvSwarm)
END_SEND_TABLE()

void CEnvSwarm::Precache()
{
	PrecacheModel("models/crow.mdl");

	BaseClass::Precache();
}

void CEnvSwarm::Spawn()
{
	Precache();

	SetSolid(SOLID_NONE);
	SetModel("models/crow.mdl");

	BaseClass::Spawn();
}

void CEnvSwarm::Think()
{
	BaseClass::Think();
}