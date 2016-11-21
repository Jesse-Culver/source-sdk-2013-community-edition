#pragma once

#include "convar.h"


extern ConVar r_flashlightdepthtexture;

void r_newflashlightCallback_f( IConVar *pConVar, const char *pOldString, float flOldValue );

extern ConVar r_flashlightdrawfrustum;// ("r_flashlightdrawfrustum", "0");
extern ConVar r_flashlightmodels;// ("r_flashlightmodels", "1");
extern ConVar r_shadowrendertotexture;// ("r_shadowrendertotexture", "0");
extern ConVar r_flashlight_xbox;// ("r_flashlight_version2", "0", FCVAR_CHEAT | FCVAR_DEVELOPMENTONLY, "Xbox 360 Flashlight Optimization");

extern ConVar r_flashlightdepthres;

extern ConVar r_newflashlight;
extern ConVar r_swingflashlight;
extern ConVar r_flashlightlockposition;
extern ConVar r_flashlightfov;
extern ConVar r_flashlightoffsetx;
extern ConVar r_flashlightoffsety;
extern ConVar r_flashlightoffsetz;
extern ConVar r_flashlightnear;
extern ConVar r_flashlightfar;
extern ConVar r_flashlightconstant;
extern ConVar r_flashlightlinear;
extern ConVar r_flashlightquadratic;
extern ConVar r_flashlightvisualizetrace;
extern ConVar r_flashlightambient;
extern ConVar r_flashlightshadowatten;
extern ConVar r_flashlightladderdist;
extern ConVar mat_slopescaledepthbias_shadowmap;
extern ConVar mat_depthbias_shadowmap;
extern ConVar mat_shadow_filter;
