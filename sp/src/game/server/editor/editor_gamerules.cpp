//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: The Half-Life 2 game rules, such as the relationship tables and ammo
//			damage cvars.
//
//=============================================================================

#include "cbase.h"
#include "editor_gamerules.h"
#include "ammodef.h"
#include "hl2_shareddefs.h"

#ifdef CLIENT_DLL

#else
#include "player.h"
#include "game.h"
#include "gamerules.h"
#include "teamplay_gamerules.h"
#include "hl2_player.h"
#include "voice_gamemgr.h"
#include "globalstate.h"
#include "ai_basenpc.h"
#include "weapon_physcannon.h"
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


REGISTER_GAMERULES_CLASS(CEditorRules);

BEGIN_NETWORK_TABLE_NOBASE(CEditorRules, DT_HL2GameRules)

END_NETWORK_TABLE()


LINK_ENTITY_TO_CLASS(hl2_gamerules, CEditorRulesProxy);
IMPLEMENT_NETWORKCLASS_ALIASED(EditorRulesProxy, DT_HalfLife2Proxy)


#ifdef CLIENT_DLL
void RecvProxy_HL2GameRules(const RecvProp *pProp, void **pOut, void *pData, int objectID)
{
	CEditorRules *pRules = HL2GameRules();
	Assert(pRules);
	*pOut = pRules;
}

BEGIN_RECV_TABLE(CEditorRulesProxy, DT_HalfLife2Proxy)
RecvPropDataTable("hl2_gamerules_data", 0, 0, &REFERENCE_RECV_TABLE(DT_HL2GameRules), RecvProxy_HL2GameRules)
END_RECV_TABLE()
#else
void* SendProxy_HL2GameRules(const SendProp *pProp, const void *pStructBase, const void *pData, CSendProxyRecipients *pRecipients, int objectID)
{
	CEditorRules *pRules = HL2GameRules();
	Assert(pRules);
	pRecipients->SetAllRecipients();
	return pRules;
}

BEGIN_SEND_TABLE(CEditorRulesProxy, DT_HalfLife2Proxy)
SendPropDataTable("hl2_gamerules_data", 0, &REFERENCE_SEND_TABLE(DT_HL2GameRules), SendProxy_HL2GameRules)
END_SEND_TABLE()
#endif

ConVar  physcannon_mega_enabled("physcannon_mega_enabled", "0", FCVAR_CHEAT | FCVAR_REPLICATED);

// Controls the application of the robus radius damage model.
ConVar	sv_robust_explosions("sv_robust_explosions", "1", FCVAR_REPLICATED);

// Damage scale for damage inflicted by the player on each skill level.
ConVar	sk_dmg_inflict_scale1("sk_dmg_inflict_scale1", "1.50", FCVAR_REPLICATED);
ConVar	sk_dmg_inflict_scale2("sk_dmg_inflict_scale2", "1.00", FCVAR_REPLICATED);
ConVar	sk_dmg_inflict_scale3("sk_dmg_inflict_scale3", "0.75", FCVAR_REPLICATED);

// Damage scale for damage taken by the player on each skill level.
ConVar	sk_dmg_take_scale1("sk_dmg_take_scale1", "0.50", FCVAR_REPLICATED);
ConVar	sk_dmg_take_scale2("sk_dmg_take_scale2", "1.00", FCVAR_REPLICATED);
#ifdef HL2_EPISODIC
ConVar	sk_dmg_take_scale3("sk_dmg_take_scale3", "2.0", FCVAR_REPLICATED);
#else
ConVar	sk_dmg_take_scale3("sk_dmg_take_scale3", "1.50", FCVAR_REPLICATED);
#endif//HL2_EPISODIC

ConVar	sk_allow_autoaim("sk_allow_autoaim", "1", FCVAR_REPLICATED | FCVAR_ARCHIVE_XBOX);

// Autoaim scale
ConVar	sk_autoaim_scale1("sk_autoaim_scale1", "1.0", FCVAR_REPLICATED);
ConVar	sk_autoaim_scale2("sk_autoaim_scale2", "1.0", FCVAR_REPLICATED);
//ConVar	sk_autoaim_scale3( "sk_autoaim_scale3", "0.0", FCVAR_REPLICATED ); NOT CURRENTLY OFFERED ON SKILL 3

// Quantity scale for ammo received by the player.
ConVar	sk_ammo_qty_scale1("sk_ammo_qty_scale1", "1.20", FCVAR_REPLICATED);
ConVar	sk_ammo_qty_scale2("sk_ammo_qty_scale2", "1.00", FCVAR_REPLICATED);
ConVar	sk_ammo_qty_scale3("sk_ammo_qty_scale3", "0.60", FCVAR_REPLICATED);

ConVar	sk_plr_health_drop_time("sk_plr_health_drop_time", "30", FCVAR_REPLICATED);
ConVar	sk_plr_grenade_drop_time("sk_plr_grenade_drop_time", "30", FCVAR_REPLICATED);

ConVar	sk_plr_dmg_ar2("sk_plr_dmg_ar2", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_ar2("sk_npc_dmg_ar2", "0", FCVAR_REPLICATED);
ConVar	sk_max_ar2("sk_max_ar2", "0", FCVAR_REPLICATED);
ConVar	sk_max_ar2_altfire("sk_max_ar2_altfire", "0", FCVAR_REPLICATED);

ConVar	sk_plr_dmg_alyxgun("sk_plr_dmg_alyxgun", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_alyxgun("sk_npc_dmg_alyxgun", "0", FCVAR_REPLICATED);
ConVar	sk_max_alyxgun("sk_max_alyxgun", "0", FCVAR_REPLICATED);

ConVar	sk_plr_dmg_pistol("sk_plr_dmg_pistol", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_pistol("sk_npc_dmg_pistol", "0", FCVAR_REPLICATED);
ConVar	sk_max_pistol("sk_max_pistol", "0", FCVAR_REPLICATED);

ConVar	sk_plr_dmg_smg1("sk_plr_dmg_smg1", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_smg1("sk_npc_dmg_smg1", "0", FCVAR_REPLICATED);
ConVar	sk_max_smg1("sk_max_smg1", "0", FCVAR_REPLICATED);

// FIXME: remove these
//ConVar	sk_plr_dmg_flare_round	( "sk_plr_dmg_flare_round","0", FCVAR_REPLICATED);
//ConVar	sk_npc_dmg_flare_round	( "sk_npc_dmg_flare_round","0", FCVAR_REPLICATED);
//ConVar	sk_max_flare_round		( "sk_max_flare_round","0", FCVAR_REPLICATED);

ConVar	sk_plr_dmg_buckshot("sk_plr_dmg_buckshot", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_buckshot("sk_npc_dmg_buckshot", "0", FCVAR_REPLICATED);
ConVar	sk_max_buckshot("sk_max_buckshot", "0", FCVAR_REPLICATED);
ConVar	sk_plr_num_shotgun_pellets("sk_plr_num_shotgun_pellets", "7", FCVAR_REPLICATED);

ConVar	sk_plr_dmg_rpg_round("sk_plr_dmg_rpg_round", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_rpg_round("sk_npc_dmg_rpg_round", "0", FCVAR_REPLICATED);
ConVar	sk_max_rpg_round("sk_max_rpg_round", "0", FCVAR_REPLICATED);

ConVar	sk_plr_dmg_sniper_round("sk_plr_dmg_sniper_round", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_sniper_round("sk_npc_dmg_sniper_round", "0", FCVAR_REPLICATED);
ConVar	sk_max_sniper_round("sk_max_sniper_round", "0", FCVAR_REPLICATED);

//ConVar	sk_max_slam				( "sk_max_slam","0", FCVAR_REPLICATED);
//ConVar	sk_max_tripwire			( "sk_max_tripwire","0", FCVAR_REPLICATED);

//ConVar	sk_plr_dmg_molotov		( "sk_plr_dmg_molotov","0", FCVAR_REPLICATED);
//ConVar	sk_npc_dmg_molotov		( "sk_npc_dmg_molotov","0", FCVAR_REPLICATED);
//ConVar	sk_max_molotov			( "sk_max_molotov","0", FCVAR_REPLICATED);

ConVar	sk_plr_dmg_grenade("sk_plr_dmg_grenade", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_grenade("sk_npc_dmg_grenade", "0", FCVAR_REPLICATED);
ConVar	sk_max_grenade("sk_max_grenade", "0", FCVAR_REPLICATED);

#ifdef HL2_EPISODIC
ConVar	sk_max_hopwire("sk_max_hopwire", "3", FCVAR_REPLICATED);
ConVar	sk_max_striderbuster("sk_max_striderbuster", "3", FCVAR_REPLICATED);
#endif

//ConVar sk_plr_dmg_brickbat	( "sk_plr_dmg_brickbat","0", FCVAR_REPLICATED);
//ConVar sk_npc_dmg_brickbat	( "sk_npc_dmg_brickbat","0", FCVAR_REPLICATED);
//ConVar sk_max_brickbat		( "sk_max_brickbat","0", FCVAR_REPLICATED);

ConVar	sk_plr_dmg_smg1_grenade("sk_plr_dmg_smg1_grenade", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_smg1_grenade("sk_npc_dmg_smg1_grenade", "0", FCVAR_REPLICATED);
ConVar	sk_max_smg1_grenade("sk_max_smg1_grenade", "0", FCVAR_REPLICATED);

ConVar	sk_plr_dmg_357("sk_plr_dmg_357", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_357("sk_npc_dmg_357", "0", FCVAR_REPLICATED);
ConVar	sk_max_357("sk_max_357", "0", FCVAR_REPLICATED);

ConVar	sk_plr_dmg_crossbow("sk_plr_dmg_crossbow", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_crossbow("sk_npc_dmg_crossbow", "0", FCVAR_REPLICATED);
ConVar	sk_max_crossbow("sk_max_crossbow", "0", FCVAR_REPLICATED);

ConVar	sk_dmg_sniper_penetrate_plr("sk_dmg_sniper_penetrate_plr", "0", FCVAR_REPLICATED);
ConVar	sk_dmg_sniper_penetrate_npc("sk_dmg_sniper_penetrate_npc", "0", FCVAR_REPLICATED);

ConVar	sk_plr_dmg_airboat("sk_plr_dmg_airboat", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_airboat("sk_npc_dmg_airboat", "0", FCVAR_REPLICATED);

ConVar	sk_max_gauss_round("sk_max_gauss_round", "0", FCVAR_REPLICATED);

// Gunship & Dropship cannons
ConVar	sk_npc_dmg_gunship("sk_npc_dmg_gunship", "0", FCVAR_REPLICATED);
ConVar	sk_npc_dmg_gunship_to_plr("sk_npc_dmg_gunship_to_plr", "0", FCVAR_REPLICATED);

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : iDmgType - 
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
int CEditorRules::Damage_GetTimeBased(void)
{
#ifdef HL2_EPISODIC
	int iDamage = (DMG_PARALYZE | DMG_NERVEGAS | DMG_POISON | DMG_RADIATION | DMG_DROWNRECOVER | DMG_ACID | DMG_SLOWBURN);
	return iDamage;
#else
	return BaseClass::Damage_GetTimeBased();
#endif
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : iDmgType - 
// Output :		bool
//-----------------------------------------------------------------------------
bool CEditorRules::Damage_IsTimeBased(int iDmgType)
{
	// Damage types that are time-based.
#ifdef HL2_EPISODIC
	// This makes me think EP2 should have its own rules, but they are #ifdef all over in here.
	return ((iDmgType & (DMG_PARALYZE | DMG_NERVEGAS | DMG_POISON | DMG_RADIATION | DMG_DROWNRECOVER | DMG_SLOWBURN)) != 0);
#else
	return BaseClass::Damage_IsTimeBased(iDmgType);
#endif
}

#ifdef CLIENT_DLL
#else

#ifdef HL2_EPISODIC
ConVar  alyx_darkness_force("alyx_darkness_force", "0", FCVAR_CHEAT | FCVAR_REPLICATED);
#endif // HL2_EPISODIC

#endif // CLIENT_DLL


#ifdef CLIENT_DLL //{


#else //}{

extern bool		g_fGameOver;

#if !(defined( HL2MP ) || defined( PORTAL_MP ))
class CVoiceGameMgrHelper : public IVoiceGameMgrHelper
{
public:
	virtual bool		CanPlayerHearPlayer(CBasePlayer *pListener, CBasePlayer *pTalker, bool &bProximity)
	{
		return true;
	}
};
CVoiceGameMgrHelper g_VoiceGameMgrHelper;
IVoiceGameMgrHelper *g_pVoiceGameMgrHelper = &g_VoiceGameMgrHelper;
#endif

//-----------------------------------------------------------------------------
// Purpose:
// Input  :
// Output :
//-----------------------------------------------------------------------------
CEditorRules::CEditorRules()
{
	m_bMegaPhysgun = false;

	m_flLastHealthDropTime = 0.0f;
	m_flLastGrenadeDropTime = 0.0f;
}

//-----------------------------------------------------------------------------
// Purpose: called each time a player uses a "cmd" command
// Input  : *pEdict - the player who issued the command
//			Use engine.Cmd_Argv,  engine.Cmd_Argv, and engine.Cmd_Argc to get 
//			pointers the character string command.
//-----------------------------------------------------------------------------
bool CEditorRules::ClientCommand(CBaseEntity *pEdict, const CCommand &args)
{
	if (BaseClass::ClientCommand(pEdict, args))
		return true;

	CHL2_Player *pPlayer = (CHL2_Player *)pEdict;

	if (pPlayer->ClientCommand(args))
		return true;

	return false;
}

//-----------------------------------------------------------------------------
// Purpose: Player has just spawned. Equip them.
//-----------------------------------------------------------------------------
void CEditorRules::PlayerSpawn(CBasePlayer *pPlayer)
{
}

//-----------------------------------------------------------------------------
// Purpose: MULTIPLAYER BODY QUE HANDLING
//-----------------------------------------------------------------------------
class CCorpse : public CBaseAnimating
{
public:
	DECLARE_CLASS(CCorpse, CBaseAnimating);
	DECLARE_SERVERCLASS();

	virtual int ObjectCaps(void) { return FCAP_DONT_SAVE; }

public:
	CNetworkVar(int, m_nReferencePlayer);
};

IMPLEMENT_SERVERCLASS_ST(CCorpse, DT_Corpse)
SendPropInt(SENDINFO(m_nReferencePlayer), 10, SPROP_UNSIGNED)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(bodyque, CCorpse);


CCorpse		*g_pBodyQueueHead;

void InitBodyQue(void)
{
	CCorpse *pEntity = (CCorpse *)CreateEntityByName("bodyque");
	pEntity->AddEFlags(EFL_KEEP_ON_RECREATE_ENTITIES);
	g_pBodyQueueHead = pEntity;
	CCorpse *p = g_pBodyQueueHead;

	// Reserve 3 more slots for dead bodies
	for (int i = 0; i < 3; i++)
	{
		CCorpse *next = (CCorpse *)CreateEntityByName("bodyque");
		next->AddEFlags(EFL_KEEP_ON_RECREATE_ENTITIES);
		p->SetOwnerEntity(next);
		p = next;
	}

	p->SetOwnerEntity(g_pBodyQueueHead);
}

//-----------------------------------------------------------------------------
// Purpose: make a body que entry for the given ent so the ent can be respawned elsewhere
// GLOBALS ASSUMED SET:  g_eoBodyQueueHead
//-----------------------------------------------------------------------------
void CopyToBodyQue(CBaseAnimating *pCorpse)
{
	if (pCorpse->IsEffectActive(EF_NODRAW))
		return;

	CCorpse *pHead	= g_pBodyQueueHead;

	pHead->CopyAnimationDataFrom(pCorpse);

	pHead->SetMoveType(MOVETYPE_FLYGRAVITY);
	pHead->SetAbsVelocity(pCorpse->GetAbsVelocity());
	pHead->ClearFlags();
	pHead->m_nReferencePlayer	= ENTINDEX(pCorpse);

	pHead->SetLocalAngles(pCorpse->GetAbsAngles());
	UTIL_SetOrigin(pHead, pCorpse->GetAbsOrigin());

	UTIL_SetSize(pHead, pCorpse->WorldAlignMins(), pCorpse->WorldAlignMaxs());
	g_pBodyQueueHead = (CCorpse *)pHead->GetOwnerEntity();
}

//------------------------------------------------------------------------------
// Purpose : Initialize all default class relationships
// Input   :
// Output  :
//------------------------------------------------------------------------------
void CEditorRules::InitDefaultAIRelationships(void)
{
}


//------------------------------------------------------------------------------
// Purpose : Return classify text for classify type
// Input   :
// Output  :
//------------------------------------------------------------------------------
const char* CEditorRules::AIClassText(int classType)
{
	return "UNKNOWN_AI_CLASS";
}

void CEditorRules::PlayerThink(CBasePlayer *pPlayer)
{
	// TODO: change player class instead of doing this
	if (pPlayer->GetMoveType() != MOVETYPE_NOCLIP)
		pPlayer->SetMoveType(MOVETYPE_NOCLIP);
}

void CEditorRules::Think(void)
{
	BaseClass::Think();
}

//-----------------------------------------------------------------------------
// Purpose: Returns how much damage the given ammo type should do to the victim
//			when fired by the attacker.
// Input  : pAttacker - Dude what shot the gun.
//			pVictim - Dude what done got shot.
//			nAmmoType - What been shot out.
// Output : How much hurt to put on dude what done got shot (pVictim).
//-----------------------------------------------------------------------------
float CEditorRules::GetAmmoDamage(CBaseEntity *pAttacker, CBaseEntity *pVictim, int nAmmoType)
{
	return 0.0f;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CEditorRules::AllowDamage(CBaseEntity *pVictim, const CTakeDamageInfo &info)
{
	return false;
}

//-----------------------------------------------------------------------------
// Purpose: Whether or not the NPC should drop a health vial
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CEditorRules::NPC_ShouldDropHealth(CBasePlayer *pRecipient)
{
	return false;
}

//-----------------------------------------------------------------------------
// Purpose: Whether or not the NPC should drop a health vial
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CEditorRules::NPC_ShouldDropGrenade(CBasePlayer *pRecipient)
{
	return false;
}

//-----------------------------------------------------------------------------
// Purpose: Update the drop counter for health
//-----------------------------------------------------------------------------
void CEditorRules::NPC_DroppedHealth(void)
{
}

//-----------------------------------------------------------------------------
// Purpose: Update the drop counter for grenades
//-----------------------------------------------------------------------------
void CEditorRules::NPC_DroppedGrenade(void)
{
}

#endif //} !CLIENT_DLL


// ------------------------------------------------------------------------------------ //
// Shared CEditorRules implementation.
// ------------------------------------------------------------------------------------ //
bool CEditorRules::ShouldCollide(int collisionGroup0, int collisionGroup1)
{
	return BaseClass::ShouldCollide(collisionGroup0, collisionGroup1);
}

#ifndef CLIENT_DLL
//---------------------------------------------------------
//---------------------------------------------------------
void CEditorRules::AdjustPlayerDamageTaken(CTakeDamageInfo *pInfo)
{
}

//---------------------------------------------------------
//---------------------------------------------------------
float CEditorRules::AdjustPlayerDamageInflicted(float damage)
{
	return damage;
}
#endif//CLIENT_DLL

//---------------------------------------------------------
//---------------------------------------------------------
bool CEditorRules::ShouldUseRobustRadiusDamage(CBaseEntity *pEntity)
{
#ifdef CLIENT_DLL
	return false;
#endif

	if (!sv_robust_explosions.GetBool())
		return false;

	if (!pEntity->IsNPC())
	{
		// Only NPC's
		return false;
	}

#ifndef CLIENT_DLL
	CAI_BaseNPC *pNPC = pEntity->MyNPCPointer();
	if (pNPC->CapabilitiesGet() & bits_CAP_SIMPLE_RADIUS_DAMAGE)
	{
		// This NPC only eligible for simple radius damage.
		return false;
	}
#endif//CLIENT_DLL

	return true;
}

#ifndef CLIENT_DLL
//---------------------------------------------------------
//---------------------------------------------------------
bool CEditorRules::ShouldAutoAim(CBasePlayer *pPlayer, edict_t *target)
{
	return sk_allow_autoaim.GetBool() != 0;
}

//---------------------------------------------------------
//---------------------------------------------------------
float CEditorRules::GetAutoAimScale(CBasePlayer *pPlayer)
{
#ifdef _X360
	return 1.0f;
#else
	switch (GetSkillLevel())
	{
		case SKILL_EASY:
			return sk_autoaim_scale1.GetFloat();

		case SKILL_MEDIUM:
			return sk_autoaim_scale2.GetFloat();

		default:
			return 0.0f;
	}
#endif
}

//---------------------------------------------------------
//---------------------------------------------------------
float CEditorRules::GetAmmoQuantityScale(int iAmmoIndex)
{
	switch (GetSkillLevel())
	{
		case SKILL_EASY:
			return sk_ammo_qty_scale1.GetFloat();

		case SKILL_MEDIUM:
			return sk_ammo_qty_scale2.GetFloat();

		case SKILL_HARD:
			return sk_ammo_qty_scale3.GetFloat();

		default:
			return 0.0f;
	}
}

void CEditorRules::LevelInitPreEntity()
{
	// Remove this if you fix the bug in ep1 where the striders need to touch
	// triggers using their absbox instead of their bbox
#ifdef HL2_EPISODIC
	if (!Q_strnicmp(gpGlobals->mapname.ToCStr(), "ep1_", 4))
	{
		// episode 1 maps use the surrounding box trigger behavior
		CBaseEntity::sm_bAccurateTriggerBboxChecks = false;
	}
#endif
	BaseClass::LevelInitPreEntity();
}

//-----------------------------------------------------------------------------
// Returns whether or not Alyx cares about light levels in order to see.
//-----------------------------------------------------------------------------
bool CEditorRules::IsAlyxInDarknessMode()
{
#ifdef HL2_EPISODIC
	if (alyx_darkness_force.GetBool())
		return true;

	return (GlobalEntity_GetState("ep_alyx_darknessmode") == GLOBAL_ON);
#else
	return false;
#endif // HL2_EPISODIC
}


//-----------------------------------------------------------------------------
// This takes the long way around to see if a prop should emit a DLIGHT when it
// ignites, to avoid having Alyx-related code in props.cpp.
//-----------------------------------------------------------------------------
bool CEditorRules::ShouldBurningPropsEmitLight()
{
#ifdef HL2_EPISODIC
	return IsAlyxInDarknessMode();
#else
	return false;
#endif // HL2_EPISODIC
}


#endif//CLIENT_DLL

// ------------------------------------------------------------------------------------ //
// Global functions.
// ------------------------------------------------------------------------------------ //

#ifndef HL2MP
#ifndef PORTAL

// shared ammo definition
// JAY: Trying to make a more physical bullet response
#define BULLET_MASS_GRAINS_TO_LB(grains)	(0.002285*(grains)/16.0f)
#define BULLET_MASS_GRAINS_TO_KG(grains)	lbs2kg(BULLET_MASS_GRAINS_TO_LB(grains))

// exaggerate all of the forces, but use real numbers to keep them consistent
#define BULLET_IMPULSE_EXAGGERATION			3.5
// convert a velocity in ft/sec and a mass in grains to an impulse in kg in/s
#define BULLET_IMPULSE(grains, ftpersec)	((ftpersec)*12*BULLET_MASS_GRAINS_TO_KG(grains)*BULLET_IMPULSE_EXAGGERATION)


CAmmoDef *GetAmmoDef()
{
	static CAmmoDef def;

	return &def;
}

#endif
#endif
