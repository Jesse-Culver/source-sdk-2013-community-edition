#include "shaderlib/cshader.h"
class standard_ps30_Static_Index
{
private:
	int m_nDIFFUSE;
#ifdef _DEBUG
	bool m_bDIFFUSE;
#endif
public:
	void SetDIFFUSE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDIFFUSE = i;
#ifdef _DEBUG
		m_bDIFFUSE = true;
#endif
	}
	void SetDIFFUSE( bool i )
	{
		m_nDIFFUSE = i ? 1 : 0;
#ifdef _DEBUG
		m_bDIFFUSE = true;
#endif
	}
private:
	int m_nSPECULAR;
#ifdef _DEBUG
	bool m_bSPECULAR;
#endif
public:
	void SetSPECULAR( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nSPECULAR = i;
#ifdef _DEBUG
		m_bSPECULAR = true;
#endif
	}
	void SetSPECULAR( bool i )
	{
		m_nSPECULAR = i ? 1 : 0;
#ifdef _DEBUG
		m_bSPECULAR = true;
#endif
	}
private:
	int m_nFLASHLIGHT;
#ifdef _DEBUG
	bool m_bFLASHLIGHT;
#endif
public:
	void SetFLASHLIGHT( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nFLASHLIGHT = i;
#ifdef _DEBUG
		m_bFLASHLIGHT = true;
#endif
	}
	void SetFLASHLIGHT( bool i )
	{
		m_nFLASHLIGHT = i ? 1 : 0;
#ifdef _DEBUG
		m_bFLASHLIGHT = true;
#endif
	}
private:
	int m_nHALFLAMBERT;
#ifdef _DEBUG
	bool m_bHALFLAMBERT;
#endif
public:
	void SetHALFLAMBERT( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nHALFLAMBERT = i;
#ifdef _DEBUG
		m_bHALFLAMBERT = true;
#endif
	}
	void SetHALFLAMBERT( bool i )
	{
		m_nHALFLAMBERT = i ? 1 : 0;
#ifdef _DEBUG
		m_bHALFLAMBERT = true;
#endif
	}
private:
	int m_nGLOSS;
#ifdef _DEBUG
	bool m_bGLOSS;
#endif
public:
	void SetGLOSS( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nGLOSS = i;
#ifdef _DEBUG
		m_bGLOSS = true;
#endif
	}
	void SetGLOSS( bool i )
	{
		m_nGLOSS = i ? 1 : 0;
#ifdef _DEBUG
		m_bGLOSS = true;
#endif
	}
public:
	standard_ps30_Static_Index( )
	{
#ifdef _DEBUG
		m_bDIFFUSE = false;
#endif // _DEBUG
		m_nDIFFUSE = 0;
#ifdef _DEBUG
		m_bSPECULAR = false;
#endif // _DEBUG
		m_nSPECULAR = 0;
#ifdef _DEBUG
		m_bFLASHLIGHT = false;
#endif // _DEBUG
		m_nFLASHLIGHT = 0;
#ifdef _DEBUG
		m_bHALFLAMBERT = false;
#endif // _DEBUG
		m_nHALFLAMBERT = 0;
#ifdef _DEBUG
		m_bGLOSS = false;
#endif // _DEBUG
		m_nGLOSS = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bDIFFUSE && m_bSPECULAR && m_bFLASHLIGHT && m_bHALFLAMBERT && m_bGLOSS;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 5 * m_nDIFFUSE ) + ( 10 * m_nSPECULAR ) + ( 20 * m_nFLASHLIGHT ) + ( 40 * m_nHALFLAMBERT ) + ( 80 * m_nGLOSS ) + 0;
	}
};
#define shaderStaticTest_standard_ps30 psh_forgot_to_set_static_DIFFUSE + psh_forgot_to_set_static_SPECULAR + psh_forgot_to_set_static_FLASHLIGHT + psh_forgot_to_set_static_HALFLAMBERT + psh_forgot_to_set_static_GLOSS + 0
class standard_ps30_Dynamic_Index
{
private:
	int m_nNUM_LIGHTS;
#ifdef _DEBUG
	bool m_bNUM_LIGHTS;
#endif
public:
	void SetNUM_LIGHTS( int i )
	{
		Assert( i >= 0 && i <= 4 );
		m_nNUM_LIGHTS = i;
#ifdef _DEBUG
		m_bNUM_LIGHTS = true;
#endif
	}
	void SetNUM_LIGHTS( bool i )
	{
		m_nNUM_LIGHTS = i ? 1 : 0;
#ifdef _DEBUG
		m_bNUM_LIGHTS = true;
#endif
	}
public:
	standard_ps30_Dynamic_Index()
	{
#ifdef _DEBUG
		m_bNUM_LIGHTS = false;
#endif // _DEBUG
		m_nNUM_LIGHTS = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllDynamicVarsDefined = m_bNUM_LIGHTS;
		Assert( bAllDynamicVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nNUM_LIGHTS ) + 0;
	}
};
#define shaderDynamicTest_standard_ps30 psh_forgot_to_set_dynamic_NUM_LIGHTS + 0
