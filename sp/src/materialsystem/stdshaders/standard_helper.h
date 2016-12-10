//===================== Copyright (c) Valve Corporation. All Rights Reserved. ======================
//
// Example shader that can be applied to models
//
//==================================================================================================

#ifndef STANDARD_HELPER_H
#define STANDARD_HELPER_H

#include <string.h>

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class CBaseVSShader;
class IMaterialVar;
class IShaderDynamicAPI;
class IShaderShadow;

//-----------------------------------------------------------------------------
// Init params/ init/ draw methods
//-----------------------------------------------------------------------------
struct Standard_Vars_t
{
	Standard_Vars_t() { memset( this, 0xFF, sizeof(*this) ); }

	int m_nBaseTexture;
	int m_nBaseTextureFrame;
	int m_nBaseTextureTransform;

	int m_nUseGloss;

	int m_nBumpMap;
	int m_nSpecMap;
	int m_nEnvMap;
};

void Standard_InitParams( CBaseVSShader *pShader, IMaterialVar** params,
						 const char *pMaterialName, Standard_Vars_t &info );

void Standard_Init( CBaseVSShader *pShader, IMaterialVar** params, 
				   Standard_Vars_t &info );

void Standard_Draw( CBaseVSShader *pShader, IMaterialVar** params, IShaderDynamicAPI *pShaderAPI,
				   IShaderShadow* pShaderShadow,
				   Standard_Vars_t &info, VertexCompressionType_t vertexCompression,
				   CBasePerMaterialContextData **pContextDataPtr );

#endif // EXAMPLE_MODEL_DX9_HELPER_H
