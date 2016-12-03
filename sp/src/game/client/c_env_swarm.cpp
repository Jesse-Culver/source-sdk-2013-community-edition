#include "cbase.h"
#include "debugoverlay_shared.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"



struct SwarmUnit_t
{
	Vector origin;
	QAngle angles;

	CountdownTimer turnTimer;	// countdown till next turn

	float distance;
	float h;
	float v;
	

	SwarmUnit_t()
	{
		static int counter;
		
		distance = RandomFloat(10.f, 150.f);
		angles = RandomAngle(0.f, 360.f);

		//DevMsg("Created swarm unit #%d\n", counter);

		counter++;
	}
};

class C_EnvSwarm : public C_BaseAnimating
{
public:
	DECLARE_CLASS(C_EnvSwarm, C_BaseAnimating);
	DECLARE_CLIENTCLASS();

	C_EnvSwarm();

	void Spawn();
	void ClientThink();
private:



	SwarmUnit_t* m_pUnits;
	Vector* m_pDirections;

	int m_nUnitCount = 100;


	
};

LINK_ENTITY_TO_CLASS(env_swarm, C_EnvSwarm);

C_EnvSwarm::C_EnvSwarm()
{
	DevMsg("Created swarm with %d units\n", m_nUnitCount);

	m_pUnits = new SwarmUnit_t[m_nUnitCount];

	for (int i = 0; i < m_nUnitCount; i++)
	{
		
	}
}

void C_EnvSwarm::Spawn()
{
	SetNextClientThink(CLIENT_THINK_ALWAYS);
}

void C_EnvSwarm::ClientThink()
{
	Vector rPos = GetRenderOrigin();
	for (int i = 0; i < m_nUnitCount; i++)
	{
		
		
		
	}
}

IMPLEMENT_CLIENTCLASS_DT(C_EnvSwarm, DT_EnvSwarm, CEnvSwarm)
END_RECV_TABLE()