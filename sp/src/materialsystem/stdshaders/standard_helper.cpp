
#include "BaseVSShader.h"
#include "standard_helper.h"
#include "convar.h"
#include "cpp_shader_constant_register_map.h"

#include "standard_vs30.inc"
#include "standard_ps30.inc"

#include "commandbuilder.h"


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static ConVar mat_fullbright("mat_fullbright", "0", FCVAR_CHEAT);
static ConVar r_lightwarpidentity("r_lightwarpidentity", "0", FCVAR_CHEAT);
static ConVar r_rimlight("r_rimlight", "1", FCVAR_CHEAT);

static ConVar mat_diffuse("mat_diffuse", "1");
static ConVar mat_specular("mat_specular", "1");

#define CHECK_TEXTURE(tex) (tex != -1) && params[tex]->IsTexture()

#define SM_BASEMAP SHADER_SAMPLER0
#define SM_BUMPMAP SHADER_SAMPLER3
#define SM_SPECMAP SHADER_SAMPLER4
#define SM_CUBEMAP SHADER_SAMPLER5


//-----------------------------------------------------------------------------
// InitParams
//-----------------------------------------------------------------------------
void Standard_InitParams(CBaseVSShader *pShader, IMaterialVar** params, const char *pMaterialName, Standard_Vars_t &info)
{

	SET_FLAGS2(MATERIAL_VAR2_LIGHTING_VERTEX_LIT);
	SET_FLAGS2(MATERIAL_VAR2_DIFFUSE_BUMPMAPPED_MODEL);
	//SET_FLAGS2(MATERIAL_VAR2_USES_ENV_CUBEMAP);
	SET_FLAGS2(MATERIAL_VAR2_SUPPORTS_HW_SKINNING);
	SET_FLAGS2(MATERIAL_VAR2_NEEDS_TANGENT_SPACES);	
}

//-----------------------------------------------------------------------------
// Init
//-----------------------------------------------------------------------------
void Standard_Init(CBaseVSShader *pShader, IMaterialVar** params, Standard_Vars_t &info)
{
	// $basetexture
	if (params[info.m_nBaseTexture]->IsDefined())
		pShader->LoadTexture(info.m_nBaseTexture, TEXTUREFLAGS_SRGB);

	// $bumpmap
	if (params[info.m_nBumpMap]->IsDefined())
		pShader->LoadBumpMap(info.m_nBumpMap);

	// $specmap
	if (params[info.m_nSpecMap]->IsDefined())
		pShader->LoadTexture(info.m_nSpecMap, TEXTUREFLAGS_SRGB);

	if (info.m_nEnvMap != -1 && params[info.m_nEnvMap]->IsDefined())
	{
		if (!IS_FLAG_SET(MATERIAL_VAR_ENVMAPSPHERE))
			pShader->LoadCubeMap(info.m_nEnvMap, g_pHardwareConfig->GetHDRType() == HDR_TYPE_NONE ? TEXTUREFLAGS_SRGB : 0);
		else
			pShader->LoadTexture(info.m_nEnvMap, g_pHardwareConfig->GetHDRType() == HDR_TYPE_NONE ? TEXTUREFLAGS_SRGB : 0);

		if (!g_pHardwareConfig->SupportsCubeMaps())
			SET_FLAGS(MATERIAL_VAR_ENVMAPSPHERE);
	}

}

inline void DrawStatic(IShaderShadow* pShaderShadow, CBaseVSShader *pShader, IMaterialVar** params, Standard_Vars_t &info)
{
	bool bHalfLambert = IS_FLAG_SET(MATERIAL_VAR_HALFLAMBERT);

	// Enable Textures

	pShaderShadow->EnableTexture(SM_BASEMAP, true);		// Base Texture
	pShaderShadow->EnableSRGBRead(SM_BASEMAP, true);

	pShaderShadow->EnableTexture(SM_BUMPMAP, true);		// Normal map

	pShaderShadow->EnableTexture(SM_SPECMAP, true);	// Roughness Map
	pShaderShadow->EnableSRGBRead(SM_SPECMAP, true);

	pShaderShadow->EnableTexture(SM_CUBEMAP, true); // Cube Map
	if (g_pHardwareConfig->GetHDRType() == HDR_TYPE_NONE)
		pShaderShadow->EnableSRGBRead(SHADER_SAMPLER1, true);

	// Settings
	pShaderShadow->EnableAlphaTest(false);
	pShaderShadow->EnableSRGBWrite(true);

	unsigned int flags = VERTEX_POSITION | VERTEX_NORMAL | VERTEX_FORMAT_COMPRESSED;
	
	int pTexCoordDim[] = { 2 };
	int nTexCoordCount = 1;	// UV
	int userDataSize = 4;	// Tangent S

	pShaderShadow->VertexShaderVertexFormat(flags, nTexCoordCount, pTexCoordDim, userDataSize);


	DECLARE_STATIC_VERTEX_SHADER(standard_vs30);
	SET_STATIC_VERTEX_SHADER(standard_vs30);

	DECLARE_STATIC_PIXEL_SHADER(standard_ps30);
	SET_STATIC_PIXEL_SHADER_COMBO(FLASHLIGHT, false);
	SET_STATIC_PIXEL_SHADER_COMBO(DIFFUSE, mat_diffuse.GetBool());
	SET_STATIC_PIXEL_SHADER_COMBO(SPECULAR, mat_specular.GetBool());
	SET_STATIC_PIXEL_SHADER_COMBO(HALFLAMBERT, bHalfLambert);
	SET_STATIC_PIXEL_SHADER_COMBO(GLOSS, params[info.m_nUseGloss]->GetIntValue());
	SET_STATIC_PIXEL_SHADER(standard_ps30);

	
}

inline void DrawDynamic(IShaderDynamicAPI* pShaderAPI, CBaseVSShader *pShader, IMaterialVar** params, Standard_Vars_t &info, VertexCompressionType_t vertexCompression)
{
	bool bHasBaseTexture =	CHECK_TEXTURE(info.m_nBaseTexture);
	bool bHasBumpMap =		CHECK_TEXTURE(info.m_nBumpMap);
	bool bHasSpecMap =		CHECK_TEXTURE(info.m_nSpecMap);
	bool bHasEnvMap =		CHECK_TEXTURE(info.m_nEnvMap);
	bool bLightingOnly = mat_fullbright.GetInt() == 2 && !IS_FLAG_SET(MATERIAL_VAR_NO_DEBUG_OVERRIDE);

	// Bind Textures
	
	// $basetexture
	if (bHasBaseTexture && !bLightingOnly)
		pShader->BindTexture(SM_BASEMAP, info.m_nBaseTexture, info.m_nBaseTextureFrame);
	else
		pShaderAPI->BindStandardTexture(SM_BASEMAP, TEXTURE_GREY);

	// $bumpmap
	if (bHasBumpMap)
		pShader->BindTexture(SM_BUMPMAP, info.m_nBumpMap, info.m_nBaseTextureFrame);
	else
		pShaderAPI->BindStandardTexture(SM_BUMPMAP, TEXTURE_NORMALMAP_FLAT);

	// $roughmap
	if (bHasSpecMap)
		pShader->BindTexture(SM_SPECMAP, info.m_nSpecMap);
	else
		pShaderAPI->BindStandardTexture(SM_SPECMAP, TEXTURE_WHITE);

	// $envmap

	if (bHasEnvMap)
		pShader->BindTexture(SM_CUBEMAP, info.m_nEnvMap);
	else
		pShaderAPI->BindStandardTexture(SM_CUBEMAP, TEXTURE_BLACK);
	// Query Light State

	LightState_t lightState = { 0, false, false };
	pShaderAPI->GetDX9LightState(&lightState);

	int numBones = pShaderAPI->GetCurrentNumBones();

	float eyePos[4];
	pShaderAPI->GetWorldSpaceCameraPosition(eyePos);

	DECLARE_DYNAMIC_VERTEX_SHADER(standard_vs30);
	SET_DYNAMIC_VERTEX_SHADER_COMBO(SKINNING, numBones > 0);
	SET_DYNAMIC_VERTEX_SHADER_COMBO(LIGHTING_PREVIEW, pShaderAPI->GetIntRenderingParameter(INT_RENDERPARM_ENABLE_FIXED_LIGHTING)!=0);
	SET_DYNAMIC_VERTEX_SHADER_COMBO(COMPRESSED_VERTS, (int)vertexCompression);
	SET_DYNAMIC_VERTEX_SHADER_COMBO(NUM_LIGHTS, lightState.m_nNumLights);
	SET_DYNAMIC_VERTEX_SHADER(standard_vs30);

	pShader->SetVertexShaderTextureTransform(VERTEX_SHADER_SHADER_SPECIFIC_CONST_0, info.m_nBaseTextureTransform);
	pShader->SetModulationPixelShaderDynamicState_LinearColorSpace(1);
	pShader->SetAmbientCubeDynamicStateVertexShader();

	DECLARE_DYNAMIC_PIXEL_SHADER(standard_ps30);
	SET_DYNAMIC_PIXEL_SHADER_COMBO(NUM_LIGHTS, lightState.m_nNumLights);
	SET_DYNAMIC_PIXEL_SHADER(standard_ps30);

	//pShaderAPI->SetPixelShaderConstant(5, params[info.m_nRoughness]->GetVecValue());
	pShaderAPI->SetPixelShaderStateAmbientLightCube(PSREG_AMBIENT_CUBE, !lightState.m_bAmbientLight);	// Force to black if not bAmbientLight
	pShaderAPI->CommitPixelShaderLighting(PSREG_LIGHT_INFO_ARRAY);
	
	
	
	pShaderAPI->SetPixelShaderConstant(PSREG_EYEPOS_SPEC_EXPONENT, eyePos);


}

void Standard_Draw_Internal(
		CBaseVSShader *pShader,
		IMaterialVar** params,
		IShaderDynamicAPI *pShaderAPI,
		IShaderShadow* pShaderShadow,
		bool bHasFlashlight,
		Standard_Vars_t &info,
		VertexCompressionType_t vertexCompression,
		CBasePerMaterialContextData **pContextDataPtr
	)
{
	SHADOW_STATE
	{
		DrawStatic(pShaderShadow, pShader, params, info);
	}

	DYNAMIC_STATE
	{
		DrawDynamic(pShaderAPI, pShader, params, info, vertexCompression);
	}

	pShader->Draw();
}


//-----------------------------------------------------------------------------
// Draw
//-----------------------------------------------------------------------------
void Standard_Draw(
		CBaseVSShader *pShader,
		IMaterialVar** params,
		IShaderDynamicAPI *pShaderAPI,
		IShaderShadow* pShaderShadow,
		Standard_Vars_t &info,
		VertexCompressionType_t vertexCompression,
		CBasePerMaterialContextData **pContextDataPtr
	)

{
	bool bHasFlashlight = pShader->UsingFlashlight(params);
	if (bHasFlashlight)
	{
		Standard_Draw_Internal(pShader, params, pShaderAPI, pShaderShadow, false, info, vertexCompression, pContextDataPtr++);
		if (pShaderShadow)
		{
			pShader->SetInitialShadowState();
		}
	}


	Standard_Draw_Internal(pShader, params, pShaderAPI, pShaderShadow, bHasFlashlight, info, vertexCompression, pContextDataPtr);
}
