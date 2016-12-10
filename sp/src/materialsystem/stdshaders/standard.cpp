//===================== Copyright (c) Valve Corporation. All Rights Reserved. ======================
//
// Example shader that can be applied to models
//
//==================================================================================================

#include "BaseVSShader.h"
#include "convar.h"
#include "standard_helper.h"


BEGIN_VS_SHADER( Standard, "SourceCE Standard" )

	BEGIN_SHADER_PARAMS
		SHADER_PARAM( BUMPMAP, SHADER_PARAM_TYPE_TEXTURE, "shadertest\bumpy_normal", "" )
		SHADER_PARAM( SPECMAP, SHADER_PARAM_TYPE_TEXTURE, "", "" )
		SHADER_PARAM( GLOSS, SHADER_PARAM_TYPE_BOOL, "0", "" )
		SHADER_PARAM(ENVMAP, SHADER_PARAM_TYPE_TEXTURE, "env_cubemap", "envmap")
	END_SHADER_PARAMS

	void SetupVars( Standard_Vars_t& info )
	{
		info.m_nBaseTexture = BASETEXTURE;
		info.m_nBaseTextureFrame = FRAME;
		info.m_nBaseTextureTransform = BASETEXTURETRANSFORM;

		info.m_nUseGloss = GLOSS;

		info.m_nBumpMap = BUMPMAP;

		info.m_nSpecMap = SPECMAP;
	}

	SHADER_INIT_PARAMS()
	{
		Standard_Vars_t info;
		SetupVars( info );
		Standard_InitParams( this, params, pMaterialName, info );
	}

	SHADER_FALLBACK
	{
		return 0;
	}

	SHADER_INIT
	{
		Standard_Vars_t info;
		SetupVars( info );
		Standard_Init( this, params, info );
	}

	SHADER_DRAW
	{
		Standard_Vars_t info;
		SetupVars( info );
		Standard_Draw( this, params, pShaderAPI, pShaderShadow, info, vertexCompression, pContextDataPtr );
	}

END_SHADER

