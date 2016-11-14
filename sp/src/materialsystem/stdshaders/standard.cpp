//==================================================================================================//
//
// Standard Shader
//
//==================================================================================================

#include "BaseVSShader.h"
#include "example_model_dx9_helper.h"

// HLSL -> CPP: Auto-Generated Headers
#include "standard_ps30.inc"
#include "standard_vs30.inc"


BEGIN_VS_SHADER(Standard, "Help for SourceCE Standard")


	BEGIN_SHADER_PARAMS
		// $color, $alpha, $basetexture, $frame, and $basetexturetransform
		// are already defined
		//SHADER_PARAM(bumpmap, SHADER_PARAM_TYPE_TEXTURE, "", "bumpmap help")
		SHADER_PARAM(color3, SHADER_PARAM_TYPE_COLOR, "[1 0 0 1]", "color3 help")
	END_SHADER_PARAMS


	SHADER_INIT_PARAMS()
	{
		if( !params[color3]->IsDefined() )
		{
			// Set to red error color.
			params[color3]->SetVecValue( 1.0f, 0.0f, 0.0f, 1.0f );
		}

	}

	SHADER_FALLBACK
	{
		return 0;
	}

	SHADER_INIT
	{
		
	}

	void OnDrawElements(
		IMaterialVar **params,
		IShaderShadow* pShaderShadow,
		IShaderDynamicAPI* pShaderAPI,
		VertexCompressionType_t vertexCompression,
		CBasePerMaterialContextData **pContextDataPtr)
	{
		// Shadow State (Init)
		if (pShaderShadow)
		{
			int fmt = VERTEX_POSITION | VERTEX_NORMAL | VERTEX_TANGENT_S;
			// 1 texcoord, unspecified texcoord size, empty userdata
			pShaderShadow->VertexShaderVertexFormat(fmt, 1, NULL, 0);


			DisableFog(); // TODO: Fog
			pShaderShadow->EnableBlending(false); // TODO: Blending

			pShaderShadow->EnableDepthWrites(false);

			
// VS - Static //
			DECLARE_STATIC_VERTEX_SHADER(standard_vs30);

				SET_STATIC_VERTEX_SHADER_COMBO(FLASHLIGHT, false);

			SET_STATIC_VERTEX_SHADER(standard_vs30);

// PS - Static //	
			DECLARE_STATIC_PIXEL_SHADER(standard_ps30);



			SET_STATIC_PIXEL_SHADER(standard_ps30);
		}

		// Dynamic State (Frame)
		if (pShaderAPI)
		{
			
			
			//pShaderAPI->BindStandardTexture(SHADER_SAMPLER0, TEXTURE_GREY);
			//pShaderAPI->BindStandardTexture(SHADER_SAMPLER1, TEXTURE_NORMALMAP_FLAT);

			// TODO: Lightmap support

// VS - Dynamic //
			DECLARE_DYNAMIC_VERTEX_SHADER(standard_vs30);
			
				//float c0[4];
				//params[color3]->GetVecValue(c0, 4);
				//pShaderAPI->SetPixelShaderConstant(0, c0, ARRAYSIZE(c0) / 4);
				
			BindTexture(SHADER_SAMPLER0, BASETEXTURE, FRAME);
				
				SET_DYNAMIC_VERTEX_SHADER_COMBO(COMPRESSED_VERTS, true);
				SET_DYNAMIC_VERTEX_SHADER_COMBO(MORPHING, false);
				SET_DYNAMIC_VERTEX_SHADER_COMBO(SKINNING, false);
			
			SET_DYNAMIC_VERTEX_SHADER(standard_vs30);

			
// PS - Dynamic //
			DECLARE_DYNAMIC_PIXEL_SHADER(standard_ps30);

			
				//pShaderAPI->GetCurrentLightCombo();
				SET_DYNAMIC_PIXEL_SHADER_COMBO(NUM_LIGHTS, 1);

			SET_DYNAMIC_PIXEL_SHADER(standard_ps30);
		}

		// Draw Call
		Draw();
	}


END_SHADER

