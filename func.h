#pragma once
// engine.h: interface for the engine class.
//
//////////////////////////////////////////////////////////////////////
/*
#if !defined(AFX_ENGINE_H__EB604380_F9F3_11D3_9282_A0A449C10801__INCLUDED_)
#define AFX_ENGINE_H__EB604380_F9F3_11D3_9282_A0A449C10801__INCLUDED_

#if _MSC_VER > 1000
#endif // _MSC_VER > 1000
*/
#define D3D_OVERLOADS
#include <ddraw.h>
#include <d3d.h>
#include <d3dx.h>
#include <dinput.h>
#include <stdio.h>

/*
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>*/


#pragma comment(lib, "d3dx.lib")
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput.lib")



	struct D3DDEVICE
	{
	// D3D Device info
		CHAR           strDesc[40];
		//GUID*          pDeviceGUID;
		D3DDEVICEDESC7 ddDeviceDesc;
		//BOOL           bHardware;
	};

	struct D3DDEVICEINFO
	{
		CHAR           nimi[100];
		
		D3DDEVICE d3device[100];
 
		// DDraw Driver info
		GUID*          pDriverGUID;
		DDCAPS         ddDriverCaps;
		DDCAPS         ddHELCaps;
 
		// DDraw Mode Info
		DDSURFACEDESC2 ddsdMode;
		BOOL           bFullscreen;
 
		// For internal use (apps should not need these)
		GUID           guidDevice;
		GUID           guidDriver;
		DDSURFACEDESC2 ddsdModes[100];
		INT          dwNumModes;
		DWORD          dwCurrentMode;
		BOOL           bDesktopCompatible;
	};


	bool viivaviiva(bool *osuma,float *osumax,float *osumaz,float piste1x,float piste1z,float piste2x,float piste2z,float piste3x,float piste3z,float piste4x,float piste4z);//does a line collide with another
	LPDIRECTDRAWSURFACE7 lataakuva(LPDIRECTDRAW7 m_pDD, char nimi[200], BOOL hardware);
	LPDIRECTDRAWSURFACE7 lataatekstuuri(int screenmode,D3DDEVICEINFO info, LPDIRECT3DDEVICE7 *m_pDevice,LPDIRECTDRAW7 m_pDD,char nimi[200], BOOL hardware);
	int randInt( int low, int high );
	float randDouble( float low, float high );
	bool intersect(RECT eka,RECT toka);
	char *stripped_fgets(char *s, int n, FILE *f);	
	D3DMATRIX IdentityMatrix();
	D3DMATRIX ZeroMatrix(void);
	D3DMATRIX MatrixMult(const D3DMATRIX a, const D3DMATRIX b);
	D3DMATRIX ViewMatrix(const D3DVECTOR from,const D3DVECTOR at, const D3DVECTOR world_up, const float roll);	
	D3DMATRIX ProjectionMatrix(const float near_plane, const float far_plane, const float fov);



	






//};

/*#endif // !defined(AFX_ENGINE_H__EB604380_F9F3_11D3_9282_A0A449C10801__INCLUDED_)
*/
