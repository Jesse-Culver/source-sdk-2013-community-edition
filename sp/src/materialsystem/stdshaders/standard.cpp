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
		SHADER_PARAM(bumpmap, SHADER_PARAM_TYPE_TEXTURE, "", "bumpmap help")
	END_SHADER_PARAMS


	SHADER_INIT_PARAMS()
	{
		
	}

	SHADER_FALLBACK
	{
		return 0;
	}

	SHADER_INIT
	{
		
	}

	SHADER_DRAW
	{
		// ----------------------------------------------------------------------------
		// This section is called when the shader is bound for the first time.
		// ----------------------------------------------------------------------------
		SHADOW_STATE
		{
// Shadow State
			// Setup the vertex format.
			int fmt = VERTEX_POSITION | VERTEX_NORMAL | VERTEX_TANGENT_S;
			// 1 texcoord, unspecified texcoord size, empty userdata
			pShaderShadow->VertexShaderVertexFormat(fmt, 1, NULL, 0);
			// TODO: Fog support
			DisableFog();
			// TODO: Blending support
			pShaderShadow->EnableBlending(false);

			// We don't need to write to the depth buffer.
			pShaderShadow->EnableDepthWrites(false);

			// Precache and set the screenspace shader.
// VS
			DECLARE_STATIC_VERTEX_SHADER(standard_vs30);
			SET_STATIC_VERTEX_SHADER_COMBO(FLASHLIGHT, false);
			SET_STATIC_VERTEX_SHADER(standard_vs30);

// PS		
			DECLARE_STATIC_PIXEL_SHADER(standard_ps30);
			SET_STATIC_PIXEL_SHADER(standard_ps30);
		}

		// ----------------------------------------------------------------------------
		// This section is called every frame.
		// ----------------------------------------------------------------------------
		DYNAMIC_STATE
		{
// Dynamic State
			//ITexture* s0 = params[basetexture]->GetTextureValue();
			//BindTexture(SHADER_SAMPLER0, s0);
			pShaderAPI->BindStandardTexture(SHADER_SAMPLER0, TEXTURE_GREY);
			pShaderAPI->BindStandardTexture(SHADER_SAMPLER1, TEXTURE_NORMALMAP_FLAT);

			// TODO: Lightmap support

// VS
			DECLARE_DYNAMIC_VERTEX_SHADER(standard_vs30);
			
			// TODO: set tiling parameter

			SET_DYNAMIC_VERTEX_SHADER_COMBO(COMPRESSED_VERTS, true);
			SET_DYNAMIC_VERTEX_SHADER_COMBO(MORPHING, true);
			SET_DYNAMIC_VERTEX_SHADER_COMBO(SKINNING, true);
			
			SET_DYNAMIC_VERTEX_SHADER(standard_vs30);

			
// PS
			DECLARE_DYNAMIC_PIXEL_SHADER(standard_ps30);

			// TODO: Pass actual number of lights
			SET_DYNAMIC_PIXEL_SHADER_COMBO(NUM_LIGHTS, 1);

			SET_DYNAMIC_PIXEL_SHADER(standard_ps30);
		}


		Draw();
	}


END_SHADER

