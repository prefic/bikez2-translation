// bikez2.cpp : Defines the entry point for the application.
//

//#include "stdafx.h"
#include "resource.h"
#include "bikez2.h"

int numkuvia=6;

const int objnum0=6; //obj1 - bike
const int objnum1=8; //map0
const int objnum2=18; //obj2 - bullets
const int objnum3=11; //ukko0 (character0)
const int objnum4=11; //ukko1
const int objnum5=11; //ukko2
const int objnum6=3; //obj3 - bike2
const int objnum7=11; //ukko3
const int objnum8=11; //ukko4
const int objnum9=3; //obj4 - bike3
const int objnum10=11; //ukko5


#define MAX_LOADSTRING 100
#define RELEASE(x) if (x) {x->Release(); x=NULL;}
#define sqr(x)				((x)*(x))
static const float pi = 3.1415926535897932384626433832795f;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
HWND hWnd;
LPD3DXCONTEXT dxctx;             // Direct3DX context handle.

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int sub(int test){
	int age = 33;
	return age*test;

}


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hInstNULL, LPSTR lpszCmdLine, int nCmdShow){
	startApplication(hInstance);	
}

void startApplication(HINSTANCE hInstance)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BIKEZ2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, 1)) 
	{
		return;
	}

	init();
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_BIKEZ2);
/*
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}*/

	
BOOL bGotMsg;    
//MSG  msg;
	m_LastTime = GetTickCount(); //reset timer
	bool g_bReady=true;  
	bool g_bActive=true;
	PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );
	while( WM_QUIT != msg.message  )    
	{
        // Use PeekMessage() if the app is active, so we can use idle time to
        // render the scene. Else, use GetMessage() to avoid eating CPU time.
        if( g_bActive )
            bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );
        else
            bGotMsg = GetMessage( &msg, NULL, 0U, 0U );
		if( bGotMsg )
        {                
			TranslateMessage( &msg );
            DispatchMessage( &msg );
        }        
		else        
		{
            // Render a frame during idle time (no messages are waiting)
            if( g_bActive && g_bReady )
			{   


				readkeyb();
				if(!quittaos)
				{
					Render();
					dxctx->UpdateFrame(0);
					//m_pPrimary->Flip(NULL,DDFLIP_WAIT);
					
				}
				else{
					break;
				}
			}
        }    
	}

}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= (LPCSTR)IDC_BIKEZ2;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON1);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   //HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   //hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   hWnd=CreateWindow(
    szWindowClass,
    szTitle,
    WS_POPUPWINDOW|WS_VISIBLE,
    CW_USEDEFAULT,
    0,
    1026,
    770,
    NULL,
    NULL,
    hInstance,
    NULL);

    /*hWnd = CreateWindow(szWindowClass, szTitle, WS_EX_TOPMOST,//WS_EX_TOPMOST WS_OVERLAPPEDWINDOW
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);*/

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//int wmId, wmEvent;
	//PAINTSTRUCT ps;
	//HDC hdc;
	//TCHAR szHello[MAX_LOADSTRING];
	//LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{				
		case WM_ACTIVATE:
			{
				if (g_pMouse)
					{
					g_pMouse->Acquire();
					}
				if (g_lpDIDevice)
					{
					g_lpDIDevice->Acquire();
					}
			}
			break;		
		case WM_CHAR:	//read keys for input name	
			{
				if(pelivaihe==4)
				if(pelivaihe2==3)
				if(keytimer<0){
					keytimer=25;
					bug1=bug1+1;

				switch (wParam) {                  
                case 0x0A:break;  // linefeed  
                case 0x1B:break;  // escape  
                case 0x09:break;  // tab  
                case 0x0D:break;  // carriage return 
                 
				case 0x08:  // backspace 				
					kirjaintanimessa=kirjaintanimessa-1;
					if(kirjaintanimessa<0)kirjaintanimessa=0;					
					savenimi[kirjaintanimessa]=NULL;
				break;
 
                default: 
					char che=(char)wParam;
					savenimi[kirjaintanimessa]=che;					
					kirjaintanimessa=kirjaintanimessa+1;
					if(kirjaintanimessa>49)kirjaintanimessa=49;
				}
				}
			}
			break;
		case WM_DESTROY:
			CleanUp();
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
/*
// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
*/

void SetupPixelFog(DWORD dwColor, DWORD dwMode)
{
    float fStart = maxvisible-5000,    // for linear mode
          fEnd   = maxvisible,
          fDensity = 0.66f;  // for exponential modes
 
	fStart=0.5f;
	fEnd=1.0f;
    // Enable fog blending.
    m_pDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, TRUE);
 
    // Set the fog color.
    m_pDevice->SetRenderState(D3DRENDERSTATE_FOGCOLOR, dwColor);
    
    // Set fog parameters.
    if(D3DFOG_LINEAR == dwMode)
    {
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGTABLEMODE, dwMode);
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGSTART, *(DWORD *)(&fStart));
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGEND,   *(DWORD *)(&fEnd));
    }
    else
    {
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGTABLEMODE, dwMode);
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGDENSITY, *(DWORD *)(&fDensity));
    }
 
}

void SetupVertexFog(float fStart, float fEnd, DWORD dwColor, DWORD dwMode, BOOL fUseRange, FLOAT fDensity)
{
    

	
 
    // Enable fog blending.
    m_pDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, TRUE);
 
    // Set the fog color.
    m_pDevice->SetRenderState(D3DRENDERSTATE_FOGCOLOR, dwColor);
    
    // Set fog parameters.
    if(D3DFOG_LINEAR == dwMode)
    {
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGVERTEXMODE, dwMode);
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGSTART, *(DWORD *)(&fStart));
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGEND,   *(DWORD *)(&fEnd));
    }
    else
    {
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGSTART, *(DWORD *)(&fStart));
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGEND,   *(DWORD *)(&fEnd));
		m_pDevice->SetRenderState(D3DRENDERSTATE_FOGVERTEXMODE, dwMode);
        m_pDevice->SetRenderState(D3DRENDERSTATE_FOGDENSITY, *(LPDWORD)(&fDensity));
    }

    // Enable range-based fog if desired (only supported for vertex fog).
    // For this example, it is assumed that fUseRange is set to a nonzero value
    // only if the driver exposes the D3DPRASTERCAPS_FOGRANGE capability.
    // 
    // Note: this is slightly more performance intensive
    //       than non-range-based fog.
    if(fUseRange)
        m_pDevice->SetRenderState(
                       D3DRENDERSTATE_RANGEFOGENABLE,
                       TRUE);
}


//Program initialization
void init(void)
{
	int q;
	RECT rcSource, rcDest;
	
	bool osuma=false;
	keytimer=0;
	
	//randomgenerator(i didnt find command for this)	
	for (q=0; q<(int)GetTickCount()/100; q++){		
		rand();
	}
	
	SOUNDS_ON=true;
	SOUNDS_LOADED=false;

	
	//initializez 3d	
	D3DXInitialize();
	ShowCursor(false);	
	SetCursor(NULL);
	LoadCursor(NULL, IDC_ARROW);
	initkeyb();
	createscreen();
	readpictures();
	cfg_load();
	//background image
	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0xFFFFFFFF, 0, 0 );
	rcSource.top = 0; 
	rcSource.left = 0;
	rcSource.bottom = 132;
	rcSource.right = 351;
	rcDest.top = (int)((SCREEN_HEIGHT-132)/2); 
	rcDest.left = (int)((SCREEN_WIDTH-351)/2);
	rcDest.bottom = rcDest.top+132; 
	rcDest.right = rcDest.left+351; 
	/*if(rcDest.top<0)rcDest.top=0;
	if(rcDest.left<0)rcDest.left=0;
	if(rcDest.bottom>SCREEN_HEIGHT)rcDest.bottom=SCREEN_HEIGHT;
	if(rcDest.right>SCREEN_WIDTH)rcDest.right=SCREEN_WIDTH;*/

	taka->Blt(&rcDest,
					kuvia[5],
					&rcSource,DDBLT_WAIT  ,NULL);	
	//m_pPrimary->Flip(NULL,DDFLIP_WAIT);
	dxctx->UpdateFrame(0);

	int t1=timeGetTime();
	while(timeGetTime()-t1<3000){
		int test=0;
	}

	plusmiinus=0;

		// Initialize and set the matrices
	m_World = IdentityMatrix();
	m_View = ViewMatrix(D3DVECTOR(0,0,0), D3DVECTOR(0,0,1), D3DVECTOR(0,1,0), 0);
	
	//m_Projection = ProjectionMatrix(50.0f, 12000.0f, (float)(80*pi/180)); // 60 vision field
	m_Projection = ProjectionMatrix(100.0f, maxvisible, (float)(80*pi/180)); // 60 vision field
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &m_World);
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);

	// Set the render states
	//m_pDevice->SetRenderState(D3DRENDERSTATE_ANTIALIAS,D3DANTIALIAS_SORTDEPENDENT );//ota DDSCAPS2_HINTANTIALIASING pois jos poistat		
	
	//sumut
	if((desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGVERTEX)&&(!(desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGRANGE)))
		SetupVertexFog(maxvisible-5000,maxvisible,0x004C4C4C, D3DFOG_LINEAR  , FALSE, 0);//sumu
	if((desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGVERTEX)&&(desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGRANGE))
		SetupVertexFog(maxvisible-5000,maxvisible,0x004C4C4C, D3DFOG_LINEAR  , TRUE, 0);//sumu
	/*if(desc3d.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_FOGTABLE)
		SetupPixelFog(0x004C4C4C, D3DFOG_LINEAR);*/

 
	m_pDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE,TRUE);
	m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE,D3DSHADE_GOURAUD);	
	m_pDevice->SetRenderState(D3DRENDERSTATE_CULLMODE,D3DCULL_CCW);//D3DCULL_CCW
	m_pDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);

	
	//m_pDevice->SetTextureStageState(0,D3DTSS_MAGFILTER, D3DTFG_LINEAR);  
	//m_pDevice->SetTextureStageState(0,D3DTSS_MINFILTER, D3DTFN_LINEAR);
	
	//first linear filter
	if(desc3d.dpcTriCaps.dwTextureFilterCaps&D3DPTFILTERCAPS_MAGFLINEAR)	
		m_pDevice->SetTextureStageState(0,D3DTSS_MAGFILTER, D3DTFG_LINEAR);		
	if(desc3d.dpcTriCaps.dwTextureFilterCaps&D3DPTFILTERCAPS_MINFLINEAR)	
		m_pDevice->SetTextureStageState(0,D3DTSS_MINFILTER, D3DTFG_LINEAR);		
	
	//then anistropic filter
	if(desc3d.dpcTriCaps.dwTextureFilterCaps&D3DPTFILTERCAPS_MAGFANISOTROPIC)	
		m_pDevice->SetTextureStageState(0,D3DTSS_MAGFILTER, D3DTFG_ANISOTROPIC);
	if(desc3d.dpcTriCaps.dwTextureFilterCaps&D3DPTFILTERCAPS_MINFANISOTROPIC)		
		m_pDevice->SetTextureStageState(0,D3DTSS_MINFILTER, D3DTFN_ANISOTROPIC);	

	
	m_pDevice->SetTextureStageState(0,D3DTSS_MAXANISOTROPY,2);
	

	m_pDevice->SetTextureStageState(0,D3DTSS_ADDRESS,D3DTADDRESS_MIRROR); 
	
	m_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, 
                                   D3DTTFF_COUNT2 //| D3DTTFF_PROJECTED 
								   );
		
	m_pDevice->SetRenderState( D3DRENDERSTATE_LIGHTING,TRUE);

	//set mouse center
	mousex=(float)(SCREEN_WIDTH/2);
	mousey=(float)(SCREEN_HEIGHT/2);
	
	//load missions
	luemissiot();

	//load textures
	loadtext();
	DDCOLORKEY color;	
	color.dwColorSpaceHighValue=0x000000;//CLR_INVALID is top corner
	color.dwColorSpaceLowValue=0x000000;
	//color.dwColorSpaceHighValue=CLR_INVALID;//CLR_INVALID is top corner
	//color.dwColorSpaceLowValue=CLR_INVALID;

	tausta[15]->SetColorKey(DDCKEY_SRCBLT,&color);

	//load objects //remember to add mallit[n]
	mallit[0].malli= new obj[objnum0];	
	mallit[1].malli= new obj[objnum1];
	mallit[2].malli= new obj[objnum2];
	mallit[3].malli= new obj[objnum3];
	mallit[4].malli= new obj[objnum4];
	mallit[5].malli= new obj[objnum5];
	mallit[6].malli= new obj[objnum6];
	mallit[7].malli= new obj[objnum7];
	mallit[8].malli= new obj[objnum8];
	mallit[9].malli= new obj[objnum9];
	mallit[10].malli= new obj[objnum10];
	lataa("models/obj1.3dw",	mallit[0].malli,	false,	false);
	lataa("models/map0.3dw",	mallit[1].malli,	false,	false);
	lataa("models/obj2.3dw",	mallit[2].malli,	false,	false);
	lataa("models/ukko0.3dw",	mallit[3].malli,	false,	false);
	lataa("models/ukko1.3dw",	mallit[4].malli,	false,	false);
	lataa("models/ukko2.3dw",	mallit[5].malli,	false,	false);
	lataa("models/obj3.3dw",	mallit[6].malli,	false,	false);
	lataa("models/ukko3.3dw",	mallit[7].malli,	false,	false);
	lataa("models/ukko4.3dw",	mallit[8].malli,	false,	false);
	lataa("models/obj4.3dw",	mallit[9].malli,	false,	false);
	lataa("models/ukko5.3dw",	mallit[10].malli,	false,	false);

/*
	moveparts(3);//moves ukko0 pieces to their places
	moveparts(4);//moves ukko1 pieces to their places
	moveparts(5);//moves ukko1 pieces to their places
*/

	
	//initialize matrix	
	ZeroMemory(&matriisi, sizeof(matriisi));
	D3DXCreateMatrixStack(  0, &matriisi);

	//load walls
	viivagrouppia=2;//remember to add it to the header
	loadwall("models/wall0.3dw",&viivagroup[0],false);//walls of maps(or levels)
	loadwall("models/wall1.3dw",&viivagroup[1],false);//moped

	valittu=false;
	menuvalittu=1;
	menuja[0]=4;
	menuja[1]=13;
	menuja[2]=13;
	menuja[3]=13;
	menuja[4]=13;
	menuja[5]=4;
	menuja[6]=13;

	//character textures	
	ukkotekstuuri[0].osa[0]=10;//torso
	ukkotekstuuri[0].osa[1]=11;//legs
	ukkotekstuuri[0].osa[2]=12;//hand
	ukkotekstuuri[0].osa[3]=14;//face

	ukkotekstuuri[1].osa[0]=28;//torso
	ukkotekstuuri[1].osa[1]=28;//legs
	ukkotekstuuri[1].osa[2]=28;//hand
	ukkotekstuuri[1].osa[3]=29;//face

	ukkotekstuuri[2].osa[0]=49;//torso
	ukkotekstuuri[2].osa[1]=51;//legs
	ukkotekstuuri[2].osa[2]=50;//hand
	ukkotekstuuri[2].osa[3]=48;//face

	ukkotekstuuri[3].osa[0]=53;//torso
	ukkotekstuuri[3].osa[1]=55;//legs
	ukkotekstuuri[3].osa[2]=54;//hand
	ukkotekstuuri[3].osa[3]=52;//face

	ukkotekstuuri[4].osa[0]=57;//torso
	ukkotekstuuri[4].osa[1]=59;//legs
	ukkotekstuuri[4].osa[2]=58;//hand
	ukkotekstuuri[4].osa[3]=56;//face

	sounds_start();
	

	//weapons 
	//weapons could be loaded from a file.
	q=0;
	ase[q].kuva=0;//machine gun
	ase[q].nopeus=70;
	ase[q].hajonta=0.2f;
	ase[q].ampumanopeus=30;
	ase[q].monttukuva=0;
	ase[q].panoskuva=0;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.00001f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=3;
	ase[q].vahinko=0.4f;
	ase[q].haku=false;	
	ase[q].savukoko=1.0f;
	ase[q].pvahinko=1;
	ase[q].pnopeus=5;
	ase[q].pampumanopeus=9;	
	ase[q].hauleja=1;
	ase[q].tyyppi=4;


	q=1;
	ase[q].kuva=1;//homing missile
	ase[q].nopeus=3.7f;
	ase[q].hajonta=0.01f;
	ase[q].ampumanopeus=1000;
	ase[q].monttukuva=1;
	ase[q].panoskuva=1;
	ase[q].savumaahan=2;
	ase[q].savukesto=1000;
	ase[q].paino=0.0f;
	ase[q].pommi=3;
	ase[q].savuvana=10;
	ase[q].kimmokkeita=0;
	ase[q].vahinko=8;
	ase[q].haku=true;
	ase[q].savukoko=1.0f;
	ase[q].pvahinko=10;
	ase[q].pnopeus=1;
	ase[q].pampumanopeus=2;
	ase[q].hauleja=1;
	ase[q].tyyppi=4;
	
	q=2;
	ase[q].kuva=0;//bounce and explode
	ase[q].nopeus=666;//speed=random
	ase[q].hajonta=0.1f;
	ase[q].ampumanopeus=1;
	ase[q].monttukuva=-1;
	ase[q].panoskuva=2;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.01f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=0;
	ase[q].vahinko=1;
	ase[q].haku=false;
	ase[q].pvahinko=2;
	ase[q].pnopeus=2;
	ase[q].pampumanopeus=2;
	ase[q].hauleja=1;
	ase[q].tyyppi=4;

	q=3;
	ase[q].kuva=1;//spark
	ase[q].nopeus=3;
	ase[q].hajonta=0.1f;
	ase[q].ampumanopeus=1;
	ase[q].monttukuva=-1;
	ase[q].panoskuva=2;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.01f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=0;
	ase[q].vahinko=0;
	ase[q].haku=false;
	ase[q].pvahinko=2;
	ase[q].pnopeus=2;
	ase[q].pampumanopeus=2;
	ase[q].hauleja=1;
	ase[q].tyyppi=4;

	q=4;
	ase[q].kuva=1;//blood
	ase[q].nopeus=2;
	ase[q].hajonta=0.4f;
	ase[q].ampumanopeus=1;
	ase[q].monttukuva=-1;
	ase[q].panoskuva=3;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.01f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=0;
	ase[q].vahinko=0;
	ase[q].haku=false;
	ase[q].pvahinko=2;
	ase[q].pnopeus=2;
	ase[q].pampumanopeus=2;
	ase[q].hauleja=1;
	ase[q].tyyppi=4;

	q=5;
	ase[q].kuva=0;//pistole
	ase[q].nopeus=50;
	ase[q].hajonta=0.2f;
	ase[q].ampumanopeus=500;
	ase[q].monttukuva=0;
	ase[q].panoskuva=0;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.00001f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=2;
	ase[q].vahinko=2.1f;
	ase[q].haku=false;
	ase[q].pvahinko=2;
	ase[q].pnopeus=2;
	ase[q].pampumanopeus=2;
	ase[q].hauleja=1;
	ase[q].tyyppi=4;
/*
	q=6;
	ase[q].kuva=0;//mopedweapon0 // mopo ase0
	ase[q].nopeus=45;
	ase[q].hajonta=0.2f;
	ase[q].ampumanopeus=711;
	ase[q].monttukuva=0;
	ase[q].panoskuva=0;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.00001f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=2;
	ase[q].vahinko=0.1f;
	ase[q].haku=false;
	ase[q].pvahinko=2;
	ase[q].pnopeus=2;
	ase[q].pampumanopeus=2;

	q=7;
	ase[q].kuva=0;//mopedweapon1 // mopo ase1
	ase[q].nopeus=45;
	ase[q].hajonta=0.2f;
	ase[q].ampumanopeus=711;
	ase[q].monttukuva=0;
	ase[q].panoskuva=0;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.00001f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=2;
	ase[q].vahinko=0.1f;
	ase[q].haku=false;
	ase[q].pvahinko=2;
	ase[q].pnopeus=2;
	ase[q].pampumanopeus=2;

	q=8;
	ase[q].kuva=0;//mopedweapon2 // mopo ase2
	ase[q].nopeus=45;
	ase[q].hajonta=0.2f;
	ase[q].ampumanopeus=711;
	ase[q].monttukuva=0;
	ase[q].panoskuva=0;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.00001f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=2;
	ase[q].vahinko=0.1f;
	ase[q].haku=false;
	ase[q].pvahinko=2;
	ase[q].pnopeus=2;
	ase[q].pampumanopeus=2;

	q=9;
	ase[q].kuva=0;//mopedweapon3 // mopo ase3
	ase[q].nopeus=45;
	ase[q].hajonta=0.2f;
	ase[q].ampumanopeus=711;
	ase[q].monttukuva=0;
	ase[q].panoskuva=0;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.00001f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=2;
	ase[q].vahinko=0.1f;
	ase[q].haku=false;
	ase[q].pvahinko=2;
	ase[q].pnopeus=2;
	ase[q].pampumanopeus=2;
*/
	q=10;
	ase[q].kuva=0;//police gun 0 pistole
	ase[q].nopeus=70;
	ase[q].hajonta=0.2f;
	ase[q].ampumanopeus=711;
	ase[q].monttukuva=0;
	ase[q].panoskuva=0;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.00001f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=5;
	ase[q].vahinko=5.5f;
	ase[q].haku=false;
	ase[q].savukoko=1.0f;
	ase[q].hauleja=1;
	ase[q].pvahinko=3;
	ase[q].pnopeus=2;
	ase[q].pampumanopeus=2;
	ase[q].tyyppi=4;

	q=11;
	ase[q].kuva=0;//police gun 1 machinegun	
	ase[q].nopeus=70;
	ase[q].hajonta=0.2f;
	ase[q].ampumanopeus=30;
	ase[q].monttukuva=0;
	ase[q].panoskuva=0;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.00001f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=3;
	ase[q].vahinko=0.8f;
	ase[q].haku=false;	
	ase[q].savukoko=1.0f;
	ase[q].hauleja=1;
	ase[q].pvahinko=2;
	ase[q].pnopeus=5;
	ase[q].pampumanopeus=9;
	ase[q].tyyppi=4;

	q=12;
	ase[q].kuva=0;//police gun 2 missile
	ase[q].nopeus=3.7f;
	ase[q].hajonta=0.01f;
	ase[q].ampumanopeus=2000;
	ase[q].monttukuva=1;
	ase[q].panoskuva=1;
	ase[q].savumaahan=2;
	ase[q].savukesto=1000;
	ase[q].paino=0.0f;
	ase[q].pommi=3;
	ase[q].savuvana=10;
	ase[q].kimmokkeita=0;
	ase[q].vahinko=10;
	ase[q].haku=true;
	ase[q].savukoko=1.0f;
	ase[q].hauleja=1;
	ase[q].pvahinko=10;
	ase[q].pnopeus=1;
	ase[q].pampumanopeus=1;
	ase[q].tyyppi=4;
	
	pelivaihe2=0;
	pelivaihe=4;
	elapsed=15;
	for (q=0; q<100; q++){
		elapsed3[q]=15;
	}
	setLights(0,0,0);
	setLights(0,0,0);


}

void moveparts(int q)
{
	//int q;
		//for (q=0; q<1; q++){

				//head
				ukko[q].ruumiinosa[2].x=0;
				ukko[q].ruumiinosa[2].y=37.1f;
				ukko[q].ruumiinosa[2].z=0;

				//torso
				ukko[q].ruumiinosa[1].x=0;
				ukko[q].ruumiinosa[1].y=0;
				ukko[q].ruumiinosa[1].z=0;

				//butt
				ukko[q].ruumiinosa[0].x=0;
				ukko[q].ruumiinosa[0].y=0;
				ukko[q].ruumiinosa[0].z=0;
			
				//upper leg
				ukko[q].ruumiinosa[5].x=-0.8f;
				ukko[q].ruumiinosa[5].y=-3.9f;
				ukko[q].ruumiinosa[5].z=-6.7f;
				ukko[q].ruumiinosa[9].x=-0.8f;
				ukko[q].ruumiinosa[9].y=-3.9f;
				ukko[q].ruumiinosa[9].z=6.7f;

				//lower leg
				ukko[q].ruumiinosa[6].x= 3.2f -ukko[q].ruumiinosa[5].x;
				ukko[q].ruumiinosa[6].y=-26.5f-ukko[q].ruumiinosa[5].y;
				ukko[q].ruumiinosa[6].z=-8.0f-ukko[q].ruumiinosa[5].z;
				ukko[q].ruumiinosa[10].x= 3.2f -ukko[q].ruumiinosa[9].x;
				ukko[q].ruumiinosa[10].y=-26.5f-ukko[q].ruumiinosa[9].y;
				ukko[q].ruumiinosa[10].z=8.0f-ukko[q].ruumiinosa[9].z;
				

				//upper arm
				ukko[q].ruumiinosa[3].x=-1.7f;
				ukko[q].ruumiinosa[3].y=30.15f;
				ukko[q].ruumiinosa[3].z=-14.7f;
				ukko[q].ruumiinosa[8].x=-1.7f;
				ukko[q].ruumiinosa[8].y=30.15f;
				ukko[q].ruumiinosa[8].z=14.7f;
				

				//lower arm
				ukko[q].ruumiinosa[4].x=-3.26f -ukko[q].ruumiinosa[3].x;
				ukko[q].ruumiinosa[4].y=16.3f -ukko[q].ruumiinosa[3].y;
				ukko[q].ruumiinosa[4].z=-16.8f-ukko[q].ruumiinosa[3].z;
				ukko[q].ruumiinosa[7].x=-3.27f -ukko[q].ruumiinosa[8].x;
				ukko[q].ruumiinosa[7].y=16.3f -ukko[q].ruumiinosa[8].y;
				ukko[q].ruumiinosa[7].z=16.8f-ukko[q].ruumiinosa[8].z;


	/*
				//head
				mallit[q].malli[2].x=0;
				mallit[q].malli[2].y=37.1f;
				mallit[q].malli[2].z=0;

				//torso
				mallit[q].malli[1].x=0;
				mallit[q].malli[1].y=0;
				mallit[q].malli[1].z=0;

				//butt
				mallit[q].malli[0].x=0;
				mallit[q].malli[0].y=0;
				mallit[q].malli[0].z=0;
			
				//upper leg
				mallit[q].malli[5].x=-0.8f;
				mallit[q].malli[5].y=-3.9f;
				mallit[q].malli[5].z=-6.7f;
				mallit[q].malli[9].x=-0.8f;
				mallit[q].malli[9].y=-3.9f;
				mallit[q].malli[9].z=6.7f;

				//lower leg
				mallit[q].malli[6].x= 3.2f -mallit[q].malli[5].x;
				mallit[q].malli[6].y=-26.5f-mallit[q].malli[5].y;
				mallit[q].malli[6].z=-8.0f-mallit[q].malli[5].z;
				mallit[q].malli[10].x= 3.2f -mallit[q].malli[9].x;
				mallit[q].malli[10].y=-26.5f-mallit[q].malli[9].y;
				mallit[q].malli[10].z=8.0f-mallit[q].malli[9].z;
				

				//upper arm
				mallit[q].malli[3].x=-1.7f;
				mallit[q].malli[3].y=30.15f;
				mallit[q].malli[3].z=-14.7f;
				mallit[q].malli[8].x=-1.7f;
				mallit[q].malli[8].y=30.15f;
				mallit[q].malli[8].z=14.7f;
				

				//lower arm
				mallit[q].malli[4].x=-3.26f -mallit[q].malli[3].x;
				mallit[q].malli[4].y=16.3f -mallit[q].malli[3].y;
				mallit[q].malli[4].z=-16.8f-mallit[q].malli[3].z;
				mallit[q].malli[7].x=-3.27f -mallit[q].malli[8].x;
				mallit[q].malli[7].y=16.3f -mallit[q].malli[8].y;
				mallit[q].malli[7].z=16.8f-mallit[q].malli[8].z;
				*/
				/*	

				//hand
				mallit[q].malli[5].x=+1.1f-mallit[q].malli[4].x;
				mallit[q].malli[5].y=-3.2f-mallit[q].malli[4].y;
				mallit[q].malli[5].z=15.2f-mallit[q].malli[4].z;
				mallit[q].malli[10].x=+3.4f;//+2.8424f;
				mallit[q].malli[10].y=-11.7593f -(41.2814f-20.8306f);
				mallit[q].malli[10].z=-0.7f;*/
				

}

void initializemopeds(void)//initialize mopeds
{
	int d,a;
	
	d=0;
	mopot[d].etusuunta=0;
	mopot[d].ase[0]=6;
	mopot[d].ase[1]=7;
	mopot[d].ase[2]=8;
	mopot[d].ase[3]=9;
	mopot[d].timesparks=-1;
	mopot[d].mission.suoritettu=3;
	mopot[d].mopona=1;
	mopot[d].numero=d;
	mopot[d].energia=100;
	mopot[d].level=0;
	mopot[d].suunta=pi*0.25f;
	mopot[d].x1=(float)(majaz*8000+2450);
	mopot[d].z1=(float)(majax*8000+2200);
	mopot[d].x2=mopot[d].x1+sinf(mopot[d].suunta)*70;
	mopot[d].z2=mopot[d].z1+cosf(mopot[d].suunta)*70;	
	mopot[d].nopeus=0.00f;	
	mopot[d].sektorix=(int)mopot[d].x1/8000;
	mopot[d].sektoriz=(int)mopot[d].z1/8000;
	mopot[d].pois=false;
	for (a=0; a<100; a++)mopot[d].osuma[a]=false;
	mopot[d].suuntatimer=0;
	mopot[d].visible=true;
	mopot[d].x3=mopot[d].x1;
	mopot[d].z3=mopot[d].z1;
	mopot[d].x4=mopot[d].x2;
	mopot[d].z4=mopot[d].z2;
	mopot[d].rahat=50;


	for (d=1; d<mopoja; d++){	
		arvomopo(d);
	}

}

BOOL loadwall(char nimi[200],linjagroup *kohde,BOOL mirror)
{
	FILE *fil;
	CHAR rivi[300];
	fil = fopen(nimi,"rt");
	int b,a,c;	
	FLOAT groupx,groupy,groupz;

	FLOAT x[2000];
	FLOAT y[2000];
	FLOAT z[2000];

//add mirror properties to both ways

	
	fgets(rivi,sizeof(rivi),fil);//ammount of groups
	kohde->grouppia=atoi(rivi);
	kohde->viivat=new linjat[kohde->grouppia];
	
	for (b=0; b<kohde->grouppia; b++)
	{
		//location of group
		fgets(rivi,sizeof(rivi),fil);
		groupx=(float)atof(rivi);
		fgets(rivi,sizeof(rivi),fil);
		groupy=(float)atof(rivi);
		fgets(rivi,sizeof(rivi),fil);
		groupz=(float)atof(rivi);
		
		fgets(rivi,sizeof(rivi),fil);//ammount of buildings
		kohde->viivat[b].viivaa=atoi(rivi);
		kohde->viivat[b].viiva=new linja[kohde->viivat[b].viivaa];
		for (a=0; a<kohde->viivat[b].viivaa; a++)
		{
			fgets(rivi,sizeof(rivi),fil);//ammount of lines in a building	
			kohde->viivat[b].viiva[a].linjaa=atoi(rivi);
			kohde->viivat[b].viiva[a].piste=new dot[kohde->viivat[b].viiva[a].linjaa];
			for (c=0; c<kohde->viivat[b].viiva[a].linjaa; c++)//read points
			{
				x[c]=(float)atof(fgets(rivi,sizeof(rivi),fil))-groupx;//x
				y[c]=(float)atof(fgets(rivi,sizeof(rivi),fil))-groupy;//y
				z[c]=(float)atof(fgets(rivi,sizeof(rivi),fil))-groupz;//z				
			}
			for (c=0; c<kohde->viivat[b].viiva[a].linjaa-1; c++)//making lines to every except the last one. (NOTE -1)
			{
			kohde->viivat[b].viiva[a].piste[c].x1=x[c];
			kohde->viivat[b].viiva[a].piste[c].y1=y[c];
			kohde->viivat[b].viiva[a].piste[c].z1=z[c];
			kohde->viivat[b].viiva[a].piste[c].x2=x[c+1];
			kohde->viivat[b].viiva[a].piste[c].y2=y[c+1];
			kohde->viivat[b].viiva[a].piste[c].z2=z[c+1];
			}
			c=kohde->viivat[b].viiva[a].linjaa-1;//last line
			kohde->viivat[b].viiva[a].piste[c].x1=x[c];
			kohde->viivat[b].viiva[a].piste[c].y1=y[c];
			kohde->viivat[b].viiva[a].piste[c].z1=z[c];
			kohde->viivat[b].viiva[a].piste[c].x2=x[0];
			kohde->viivat[b].viiva[a].piste[c].y2=y[0];
			kohde->viivat[b].viiva[a].piste[c].z2=z[0];
		}
	}
	
	fclose(fil);

	return true;
}

BOOL lataa(char nimi[200],obj *kohde,BOOL mirror,BOOL miekkakala)
{

	

	FILE *fil;
	CHAR rivi[300];
	//INT faces;
	INT kolme,kolmi;
	FLOAT x[2000];
	FLOAT y[2000];
	FLOAT z[2000];
	FLOAT x1[2000];
	FLOAT y1[2000];
	FLOAT z1[2000];
	FLOAT u[2000];
	FLOAT v[2000];
	FLOAT w[2000];

	INT peili;
	if (mirror) peili=-1; else peili=1;

	FLOAT groupx,groupy,groupz;
	//float g[3];
	//CHAR kuvat[300];//pictures
	
	INT sivu0[2000];
	INT sivu1[2000];
	INT sivu2[2000];
	INT sivu20[2000];
	INT sivu21[2000];
	INT sivu22[2000];
	D3DVECTOR p1;
	D3DVECTOR vNormal;
	INT cur=0;
	INT cura=0;
	//int lootia;//boxes
	//INT kolmion;//triangle's

	INT i,j,b,a,q,faces;
	fil = fopen(nimi,"rt");


	//target = new objekt[lootia];

	
	fgets(rivi,sizeof(rivi),fil); 	
	j=atoi(rivi);
	//lataaapu(j,&kohde); //load help(j,&target);
	//*kohde	= new obj[j];
	

	for (b=0; b<j; b++)
	{
		fgets(rivi,sizeof(rivi),fil); 	
		a=atoi(rivi);

		fgets(rivi,sizeof(rivi),fil);
		groupx=(float)atof(rivi);
		fgets(rivi,sizeof(rivi),fil);
		groupy=(float)atof(rivi);
		fgets(rivi,sizeof(rivi),fil);
		groupz=(float)atof(rivi);
		
//At this point we load the tip of the sword.

		if (miekkakala)//swordfish
			{
			fgets(rivi,sizeof(rivi),fil);
			kohde[b].swordpointx=(float)atof(rivi)-groupx;
			fgets(rivi,sizeof(rivi),fil);
			kohde[b].swordpointy=(float)atof(rivi)-groupy;
			fgets(rivi,sizeof(rivi),fil);
			kohde[b].swordpointz=(float)atof(rivi)-groupz;
			}

		kohde[b].mirror=mirror;
		kohde[b].sisus = new objekt[a];
		kohde[b].count = a;

		for (q=0; q<a; q++)
		{


		fgets(rivi,sizeof(rivi),fil);//666666
		fgets(rivi,sizeof(rivi),fil);//materials
			kohde[b].sisus[q].matsku=atoi(rivi);
		fgets(rivi,sizeof(rivi),fil);//materials second time

			{

				fgets(rivi,sizeof(rivi),fil);
				 //new(INT faces=atoi(rivi));
				kolme=atoi(rivi);
				fgets(rivi,sizeof(rivi),fil);	
				faces=atoi(rivi);
				//D3DVERTEX kolmijako[faces*3];
				//FLOAT new( x[kolme]);
				//x=new(FLOAT[kolme]);
				kohde[b].sisus[q].loota.kolmijako = new vvertex[faces*3];
				kohde[b].sisus[q].loota.vert = faces*3;

				kohde[b].sisus[q].upleft.x=NULL;
				kohde[b].sisus[q].upleft.y=NULL;
				kohde[b].sisus[q].upleft.z=NULL;
				
				kohde[b].sisus[q].downright.x=NULL;
				kohde[b].sisus[q].downright.y=NULL;
				kohde[b].sisus[q].downright.z=NULL;

				for (i=0; i<kolme; i++)
				{
					fgets(rivi,sizeof(rivi),fil);
					x[i]=(((float)atof(rivi))-groupx);
					fgets(rivi,sizeof(rivi),fil);
					y[i]=(((float)atof(rivi))-groupy);
					fgets(rivi,sizeof(rivi),fil);
					z[i]=(((float)atof(rivi))-groupz)*peili;

					//dimensions
					if(x[i]<kohde[b].sisus[q].upleft.x) kohde[b].sisus[q].upleft.x=x[i];
					if(y[i]<kohde[b].sisus[q].upleft.y) kohde[b].sisus[q].upleft.y=y[i];
					if(z[i]<kohde[b].sisus[q].upleft.z) kohde[b].sisus[q].upleft.z=z[i];
					if(x[i]>kohde[b].sisus[q].downright.x) kohde[b].sisus[q].downright.x=x[i];
					if(y[i]>kohde[b].sisus[q].downright.y) kohde[b].sisus[q].downright.y=y[i];
					if(z[i]>kohde[b].sisus[q].downright.z) kohde[b].sisus[q].downright.z=z[i];
				}
				
				for (i=0; i<faces; i++)
				{
					fgets(rivi,sizeof(rivi),fil);
					sivu0[i]=atoi(rivi);
					fgets(rivi,sizeof(rivi),fil);
					sivu1[i]=atoi(rivi);
					fgets(rivi,sizeof(rivi),fil);
					sivu2[i]=atoi(rivi);
				
					
					
				}

				fgets(rivi,sizeof(rivi),fil);
				kolmi=atoi(rivi);
				
				for (i=0; i<kolmi; i++)
				{
					fgets(rivi,sizeof(rivi),fil);
					u[i]=(float)atof(rivi);
					fgets(rivi,sizeof(rivi),fil);
					v[i]=1.0f-(float)atof(rivi);
					fgets(rivi,sizeof(rivi),fil);
					w[i]=(float)atof(rivi);
				}
				
				fgets(rivi,sizeof(rivi),fil);
				kolmi=atoi(rivi);
				for (i=0; i<kolmi; i++)
				{
					fgets(rivi,sizeof(rivi),fil);
					sivu20[i]=atoi(rivi);
					fgets(rivi,sizeof(rivi),fil);
					sivu21[i]=atoi(rivi);
					fgets(rivi,sizeof(rivi),fil);
					sivu22[i]=atoi(rivi);	
				}
				for (i=0; i<(3*faces); i++)
				{
					fgets(rivi,sizeof(rivi),fil);
					x1[i]=((float)atof(rivi));
					fgets(rivi,sizeof(rivi),fil);
					y1[i]=((float)atof(rivi));
					fgets(rivi,sizeof(rivi),fil);
					z1[i]=((float)atof(rivi))*peili;	
				}
			
				for (i=0; i<faces; i++)
				{
					p1.x=x[sivu0[i]];     
					p1.y=y[sivu0[i]];     
					p1.z=z[sivu0[i]];
					vNormal.x=x1[sivu0[i]];
					vNormal.y=y1[sivu0[i]];
					vNormal.z=z1[sivu0[i]]; 
					kohde[b].sisus[q].loota.kolmijako[i*3+0].position=		p1; 
					kohde[b].sisus[q].loota.kolmijako[i*3+0].normal=		vNormal;
					kohde[b].sisus[q].loota.kolmijako[i*3+0].u=			u[sivu20[i]];//w[sivu20[i]];//side
					kohde[b].sisus[q].loota.kolmijako[i*3+0].v=			v[sivu20[i]];//w[sivu20[i]];
					
					
				
					p1.x=x[sivu1[i]];     
					p1.y=y[sivu1[i]];     
					p1.z=z[sivu1[i]];
					vNormal.x=x1[sivu1[i]];
					vNormal.y=y1[sivu1[i]];
					vNormal.z=z1[sivu1[i]];
					kohde[b].sisus[q].loota.kolmijako[i*3+1].position=		p1; 
					kohde[b].sisus[q].loota.kolmijako[i*3+1].normal=		vNormal;
					kohde[b].sisus[q].loota.kolmijako[i*3+1].u=			u[sivu21[i]];//w[sivu21[i]];
					kohde[b].sisus[q].loota.kolmijako[i*3+1].v=			v[sivu21[i]];//w[sivu21[i]];
					
					
				
					p1.x=x[sivu2[i]];     
					p1.y=y[sivu2[i]];     
					p1.z=z[sivu2[i]];
					vNormal.x=x1[sivu2[i]];
					vNormal.y=y1[sivu2[i]];
					vNormal.z=z1[sivu2[i]];
					kohde[b].sisus[q].loota.kolmijako[i*3+2].position=		p1; 
					kohde[b].sisus[q].loota.kolmijako[i*3+2].normal=		vNormal;
					kohde[b].sisus[q].loota.kolmijako[i*3+2].u=			u[sivu22[i]];//w[sivu22[i]];
					kohde[b].sisus[q].loota.kolmijako[i*3+2].v=			v[sivu22[i]];//w[sivu22[i]];
					
					
				}	
				

				fgets(rivi,sizeof(rivi),fil);
				kohde[b].sisus[q].textuuri=atoi(rivi);
				kohde[b].sisus[q].textuuri2=atoi(rivi);
				kohde[b].sisus[q].x=0.0f;
				kohde[b].sisus[q].y=0.0f;
				kohde[b].sisus[q].z=0.0f;
				kohde[b].x=0.0f;
				kohde[b].y=0.0f;
				kohde[b].z=0.0f;
				kohde[b].rx=0.0f;
				kohde[b].ry=0.0f;
				kohde[b].rz=0.0f;
			}
		}
	}


	fclose(fil);

	return true;

}



BOOL loadtext()
{

	FILE *fil;
	CHAR rivi[300];
	CHAR rivit[13];
	CHAR texturenimi[100];
	DWORD x=100;
	DWORD y=100;
	DWORD mipmaps=D3DX_DEFAULT;
	DWORD mipmapping=D3DX_DEFAULT;
	int q;
	fil = fopen("models/mat.3dw","rt");

	fgets(rivi,sizeof(rivi),fil);
	materiaa=atoi(rivi);	
	mat = new D3DMATERIAL7[materiaa];
	tausta = new LPDIRECTDRAWSURFACE7[materiaa];
	bool filter[300];//to filter or not to filter

	for (q=0; q<materiaa; q++)
		filter[q]=false;
/*
	//audience is not filtered
	filter[49]=true;
	filter[50]=true;
*/

	/*for (q=materiaa; q<materiaa+40; q++)
	{
		
		D3DXCreateTexture(
		m_pDevice,
		NULL,
		&x,
		&y,
		NULL,
		NULL,
		&tausta[q],
		NULL
		);

	}*/

	for (q=0; q<materiaa; q++)
	{
		ZeroMemory( &tausta[q], sizeof(tausta[q]) );
		ZeroMemory( &mat[q], sizeof(mat[q]) );
		 
		// Set the RGBA for ambient reflection. 
		fgets(rivi,sizeof(rivi),fil);
		mat[q].dcvAmbient.r = (D3DVALUE)atof(rivi);     
		fgets(rivi,sizeof(rivi),fil);
		mat[q].dcvAmbient.g = (D3DVALUE)atof(rivi); 
		fgets(rivi,sizeof(rivi),fil);
		mat[q].dcvAmbient.b = (D3DVALUE)atof(rivi);     
		mat[q].dcvAmbient.a = (D3DVALUE)1.0;  
		
		// Set the RGBA for diffuse reflection.
		fgets(rivi,sizeof(rivi),fil);
		mat[q].dcvDiffuse.r = (D3DVALUE)atof(rivi);
		fgets(rivi,sizeof(rivi),fil);
		mat[q].dcvDiffuse.g = (D3DVALUE)atof(rivi);     
		fgets(rivi,sizeof(rivi),fil);
		mat[q].dcvDiffuse.b = (D3DVALUE)atof(rivi); 
		mat[q].dcvDiffuse.a = (D3DVALUE)1.0; 

		// Set the color and sharpness of specular highlights. 
		fgets(rivi,sizeof(rivi),fil);
		mat[q].dcvSpecular.r = (D3DVALUE)atof(rivi);     
		fgets(rivi,sizeof(rivi),fil);
		mat[q].dcvSpecular.g = (D3DVALUE)atof(rivi); 
		fgets(rivi,sizeof(rivi),fil);
		mat[q].dcvSpecular.b = (D3DVALUE)atof(rivi);     
		mat[q].dcvSpecular.a =1; 
		mat[q].dvPower = 50;

		fgets(rivit,sizeof(rivit),fil);
		fgets(rivi,sizeof(rivi),fil);

		//itoa(tallennuspaikka,temprivi,10);//(saveplace, templine, 10)
		strcpy(texturenimi,"textures/");
		strcat(texturenimi,rivit);

		//if(atoi(rivi)==155) 
 

		

		//if(atoi(rivi)==255)		

		//tausta[q]=lataakuva(m_pDD,rivit,true);//background[q]loadpicture

		D3DX_SURFACEFORMAT pixel;
		
		if(SCREEN_BITS==32)pixel=D3DX_SF_UNKNOWN; //32
		if(SCREEN_BITS==24)pixel=D3DX_SF_UNKNOWN; //24
		if(SCREEN_BITS==16)pixel=D3DX_SF_UNKNOWN;//16
		/*if(SCREEN_BITS==32)pixel=D3DX_SF_A8R8G8B8 ; //32
		if(SCREEN_BITS==24)pixel=D3DX_SF_R8G8B8; //24
		if(SCREEN_BITS==16)pixel=D3DX_SF_R5G6B5; //16*/
		
		//D3DXCheckTextureRequirements(m_pDevice,NULL,0,0,&pixel);
		

		//tausta[q]=lataatekstuuri(screenmode,info,&m_pDevice,m_pDD,texturenimi,true);//background[q]=loadtexture(screenmode,info,&m_pDevice,m_pDD,texturename,true);
		/*
		D3DXLoadTextureFromFile(
        m_pDevice,
        tausta[q],                       // destination
        D3DX_DEFAULT ,               // all mip levels
        texturenimi,		//texturenimi		        // source
        NULL,                       // entire source
        NULL,                       // entire destination
        D3DX_FT_LINEAR );
*/
	
		if(filter[q])
		D3DXCreateTextureFromFile(
		m_pDevice,
		NULL,
		NULL,
		NULL,
		&pixel,
		NULL,
		&tausta[q],
		NULL,
		texturenimi,
		D3DX_FT_POINT    //D3DX_FT_DEFAULT
		);
		else 
		D3DXCreateTextureFromFile(
		m_pDevice,
		&mipmapping,
		0,
		0,
		&pixel,
		NULL,
		&tausta[q],
		&mipmaps,
		texturenimi,
		D3DX_FT_DEFAULT
		);


	}

	fclose(fil);


	return TRUE;
}

static HRESULT WINAPI EnumZBufferCallback( DDPIXELFORMAT* pddpf, VOID* pddpfDesired )
{
    // For this tutorial, we are only interested in z-buffers, so ignore any
    // other formats (e.g. DDPF_STENCILBUFFER) that get enumerated. An app
    // could also check the depth of the z-buffer (16-bit, etc,) and make a
    // choice based on that, as well. For this tutorial, we'll take the first
    // one we get.
    if( pddpf->dwFlags == DDPF_ZBUFFER )
    if( pddpf->dwZBufferBitDepth >=16)
	{
        memcpy( pddpfDesired, pddpf, sizeof(DDPIXELFORMAT) );
 
        // Return with D3DENUMRET_CANCEL to end the search.
        return D3DENUMRET_CANCEL;
    }
 
    // Return with D3DENUMRET_OK to continue the search.
    return D3DENUMRET_OK;
}

	
bool createscreen(void){


	SCREEN_WIDTH=1024;
	SCREEN_HEIGHT=768;
	SCREEN_BITS=32;

	int fs=0;
	D3DXCreateContext(  
              D3DX_DEFAULT,  
              D3DX_CONTEXT_FULLSCREEN*fs,  //windowed = 0
              hWnd,
              1024,  
              768,  
              &dxctx);
	/*D3DXCreateContextEx(D3DX_DEFAULT,  
						D3DX_CONTEXT_FULLSCREEN*fs,  //windowed = 0
						hWnd,
                        hWnd, 
                        24,
                        0,
                        8,
                        0,
                        1,
                        1024, 
                        768,
                        0,
                        &dxctx);*/
	m_pD3D=dxctx->GetD3D();
	m_pDD=dxctx->GetDD();
	m_pDevice=dxctx->GetD3DDevice();
	//taka=dxctx->GetBackBuffer(0);
	m_pPrimary=dxctx->GetPrimary();
	m_pDevice->GetRenderTarget(&taka);
	

	// Create main DirectDraw object	
	/*if (DirectDrawCreateEx(NULL,(void **)&m_pDD,IID_IDirectDraw7, NULL) != DD_OK)
		return FALSE;
	if (m_pDD->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE ) != DD_OK)
		return FALSE;	
	if (m_pDD->SetDisplayMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITS,0,0))
		return FALSE;

	
	DDSURFACEDESC2 ddsd;	

	// Get the primary display surface
	//TRACE("DrawPrim Demo: Creating the primary surface\n");
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS|DDSD_BACKBUFFERCOUNT;
	//if (hardware) {
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE|DDSCAPS_COMPLEX | DDSCAPS_FLIP | DDSCAPS_3DDEVICE | DDSCAPS_VIDEOMEMORY;
	//ddsd.ddsCaps.dwCaps2 = DDSCAPS2_HINTANTIALIASING ;
	//}
	//else {
	//ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE|DDSCAPS_COMPLEX | DDSCAPS_FLIP | DDSCAPS_3DDEVICE | DDSCAPS_SYSTEMMEMORY;
	//}
	//| DDSCAPS_3DDEVICE
	
	ddsd.dwBackBufferCount = 2;//triplebuffer
	if (m_pDD->CreateSurface(&ddsd, &m_pPrimary, NULL) != DD_OK)
		return FALSE;


	ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER; 
	if (m_pPrimary->GetAttachedSurface(&ddsd.ddsCaps, &taka) != DD_OK)	
		return FALSE; 


	// Query the DirectDraw object to get the D3D object
	//TRACE("DrawPrim Demo: Getting the D3D object\n");
	if (m_pDD->QueryInterface(IID_IDirect3D7, (VOID **)&m_pD3D) != S_OK)
		return FALSE;


	DDPIXELFORMAT ddpfZBuffer;    
	//if (hardware) 
		m_pD3D->EnumZBufferFormats(IID_IDirect3DHALDevice, EnumZBufferCallback, (VOID*)&ddpfZBuffer );
	//else m_pD3D->EnumZBufferFormats( IID_IDirect3DRGBDevice, EnumZBufferCallback, (VOID*)&ddpfZBuffer );

	
	// If we found a good zbuffer format, then the dwSize field will be
    // properly set during enumeration. Else, we have a problem and will exit.
    //if
	( sizeof(DDPIXELFORMAT) != ddpfZBuffer.dwSize );        
	//return E_FAIL; 
    // Get z-buffer dimensions from the render target
    // Setup the surface desc for the z-buffer.
    ddsd.dwFlags        = DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER;
    ddsd.dwWidth        = SCREEN_WIDTH;
    ddsd.dwHeight       = SCREEN_HEIGHT;
    memcpy( &ddsd.ddpfPixelFormat, &ddpfZBuffer, sizeof(DDPIXELFORMAT) ); 
    // For hardware devices, the z-buffer should be in video memory. For
    // software devices, create the z-buffer in system memory
    //if(hardware)
        ddsd.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;    
	//else
    //    ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
    // Create and attach a z-buffer. Real apps should be able to handle an
    // error here (DDERR_OUTOFVIDEOMEMORY may be encountered). For this 
    // tutorial, though, we are simply going to exit ungracefully.
    if (m_pDD->CreateSurface( &ddsd, &zpuskuri, NULL ) != DD_OK ) return FALSE;
	if (taka->AddAttachedSurface(zpuskuri) != DD_OK) return FALSE;
	
	
	// Create the D3D device
	//TRACE("DrawPrim Demo: Creating the device\n");
	//if(hardware) 
	HRESULT res=m_pD3D->CreateDevice(IID_IDirect3DHALDevice, taka, &m_pDevice);
		if (res != D3D_OK)
		return FALSE;
		//m_pD3D->CreateDevice(infot[driver].d3device[device].ddDeviceDesc.deviceGUID, taka, &m_pDevice);
		//RELEASE(m_pDevice);
	//if(!hardware) if (m_pD3D->CreateDevice(IID_IDirect3DRGBDevice, taka, &m_pDevice) != D3D_OK)
		//return FALSE;
*/

	//memset(&m_pViewport, 0, sizeof(D3DVIEWPORT7));    
	D3DVIEWPORT7 m_pViewport;
	m_pViewport.dwX = 0;
    m_pViewport.dwY = 0;    
	m_pViewport.dwWidth  = SCREEN_WIDTH;
    m_pViewport.dwHeight = SCREEN_HEIGHT;    
	m_pViewport.dvMinZ = 0.0f;     
    m_pViewport.dvMaxZ = 1.0f;

	

    m_pDevice->SetViewport( &m_pViewport );
		//!= D3D_OK)
	//return FALSE;
	m_pDevice->GetCaps(&desc3d);
	//desc3d=infot[driver].d3device[device].ddDeviceDesc;
	//info=infot[driver];
	return true;

}

void readkeyb(void)
{
	#define KEYDOWN(name,key) (name[key] & 0x80)  
	int q;
	int down;//wich key is pressed
	
    HRESULT  hr; 

	D3DXVECTOR3 intersect; 
	//int kolmio;//,sisus,q; //==> triangle;//,interrior,q;

	long thistime = GetTickCount();	
	elapsed2=0;
	elapsed3[30]=(float)(thistime - m_LastTime);
	for (q=0; q<30; q++){
		elapsed3[q]=elapsed3[q+1];
		elapsed2=elapsed2+elapsed3[q];
	}
	elapsed=elapsed2/30;
	m_LastTime = thistime;
/*
	elapsed2=elapsed;
	elapsed = (float)((thistime - m_LastTime)+elapsed+elapsed2)/3;
	m_LastTime = thistime;*/

	mousestate2=mousestate;
	hr = g_pMouse->GetDeviceState(sizeof(mousestate),&mousestate);
	if FAILED(hr)     
	{                
		return;     
	}
	

	mousex= mousex + (mousestate.lX+mousestate2.lX)*SCREEN_WIDTH/1024;
	mousey= mousey + (mousestate.lY+mousestate2.lY)*SCREEN_HEIGHT/768;

	//mousex= mousex + mousestate.lX*2;
	//mousey= mousey + mousestate.lY*2;

	if (mousex<0) mousex=0;
	if (mousex>SCREEN_WIDTH) mousex=(float)SCREEN_WIDTH-1;
	if (mousey<0) mousey=0;
	if (mousey>SCREEN_HEIGHT) mousey=(float)SCREEN_HEIGHT-1;

	pressed2=pressed;
	pressed=false;
	for (q=0; q<256; q++){buffer2[q]=buffer[q];}

    
	hr = g_lpDIDevice->GetDeviceState(sizeof(buffer),(LPVOID)&buffer); 
    if FAILED(hr)     
	{ 
         // If it failed, the device has probably been lost. 
         // We should check for (hr == DIERR_INPUTLOST) 
         // and attempt to reacquire it here.          
		return;     
	}
	for (q=0; q<256; q++){if((buffer[q]& 0x80)!=0){pressed=true;down=q;}}
	if((mousestate.rgbButtons[0])||(mousestate.rgbButtons[1]))pressed=true;

	//plusmiinus //plusminus
	if (KEYDOWN(buffer, DIK_SUBTRACT))
		plusmiinus=plusmiinus-0.001f*elapsed*pelinopeus;
	if (KEYDOWN(buffer, DIK_ADD))
		plusmiinus=plusmiinus+0.001f*elapsed*pelinopeus;
	
	
		

	if((!pressed&&!pressed2)&&(pelivaihe!=0))return;

	switch (pelivaihe) 
	{
	case 0:{//game
			readkey_game();
			break;
		   }
	case 1:{//mission assigment
			//accept mission
			if (!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN)){
				if(missionantovaihe==1){
					pelivaihe=0;//back to riding
					SndObjPlay(voices[1], DSBPLAY_LOOPING,options[1]&&SOUNDS_LOADED);
					mopot[0].mission=mopot[0].mission_arvottu;
					//a dude comes aboard
					if(mopot[0].mission.tyyppi==1)
						ukko[mopot->nearestukko].pois=true;
				}
				missionantovaihe=1;//introduction is readed
			}
			break;
		   }	
	case 2:{//workshop
			//pressing esc means escape. 
			if ((!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE))||(!KEYDOWN(buffer,  DIK_F9 )&&KEYDOWN(buffer2,  DIK_F9)))
							{
							pelivaihe2=0;
							pelivaihe=0;
							SndObjPlay(voices[1], DSBPLAY_LOOPING,options[1]&&SOUNDS_LOADED);
							}
			break;
		   }
	case 3:
		break;
	case 4:{
		//pressing esc means escape. 
		if ((!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE))||(!KEYDOWN(buffer,  DIK_F9 )&&KEYDOWN(buffer2,  DIK_F9))){		
			if(pelivaihe2==0)
				SendMessage( hWnd, WM_CLOSE, 0, 0 );
			else {
				//if it came to load from workshop
				if((pelivaihe2==1)||(pelivaihe2==2)){
					if(pelivaihe_oli==2){
					pelivaihe2=0;
					pelivaihe=2;
					}
					if(pelivaihe_oli==4){
					pelivaihe2=0;
					pelivaihe=4;
					}
				}
				else if(pelivaihe2==3)
					pelivaihe2=2;
				else{
					pelivaihe2=0;
					pelivaihe=4;
				}
			
			}
		}
		//down
			if(pelivaihe2!=3)
			if (!KEYDOWN(buffer,  DIK_DOWN )&&KEYDOWN(buffer2,  DIK_DOWN)){
				menuvalittu=menuvalittu+1;
				if(menuvalittu>=menuja[pelivaihe2])menuvalittu=0;
				SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
			}
		//up
			if(pelivaihe2!=3)
			if (!KEYDOWN(buffer,  DIK_UP )&&KEYDOWN(buffer2,  DIK_UP)){
				menuvalittu=menuvalittu-1;
				if(menuvalittu<0)menuvalittu=menuja[pelivaihe2]-1;
				SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
			}

		//changching keys
			if(pelivaihe2==6)
			if((menuvalittu<12)&&(menuvalittu>0)&&(pressed)&&(valittu))
			{	
				key[menuvalittu]=down;
				valittu=false;
				SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
				cfg_save();
			}
		
		//selection pressed			
			if (((mousestate2.rgbButtons[0])&&(!mousestate.rgbButtons[0]))||(!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN))){
				//loading a game
				if(pelivaihe2==1)
				if((menuvalittu<11)&&(menuvalittu>0))
				{
					tallennuspaikka=menuvalittu-1;
					game_load();
					SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
					break;
				}
				//selecting a load
				if(pelivaihe2==2)
				if((menuvalittu<11)&&(menuvalittu>0))
				{
					tallennuspaikka=menuvalittu-1;
					pelivaihe2=3;
					kirjaintanimessa=kirjaintan[tallennuspaikka];	
					strcpy(savenimi,"                                                 ");
					strcpy(savenimi,m_filenames[tallennuspaikka]);
					if(!loadable[tallennuspaikka]){
						kirjaintanimessa=0;					
						strcpy(savenimi,"                                                 ");
					}
					SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
					break;
				}
				//saving a game
				if(pelivaihe2==3)
				if((menuvalittu<11)&&(menuvalittu>0))
				{
					tallennuspaikka=menuvalittu-1;					
					game_save();
					if(pelivaihe_oli==2){
						pelivaihe2=0;
						pelivaihe=2;
					}
					if(pelivaihe_oli==4){
						pelivaihe2=0;
						pelivaihe=4;
					}
					readsaves();
					SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
					break;
				}
				//changching settings
				if(pelivaihe2==4)
				if((menuvalittu<10)&&(menuvalittu>0))
				{
					if(options[menuvalittu])options[menuvalittu]=false;
					else options[menuvalittu]=true;
					options[2]=false;//music permanently off
					cfg_save();
					SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
				}
				
				//changching keys //select a key
				if(pelivaihe2==6)
				if((menuvalittu<12)&&(menuvalittu>0))
				{
					valittu=true;
					SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
				}
				

				switch (menuvalittu){
					case 0:
						if(pelivaihe2==0){//new game
							pelivaihe2=5;							
							SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
							break;
						}
						if(pelivaihe2==5){//difficulty level
							vaikeustaso=0;
							SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
							game_new();
						}						
						break;
					case 1:
						if(pelivaihe2==0){//load
							readsaves(); pelivaihe2=1; pelivaihe_oli=4;
							SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
						}
						if(pelivaihe2==5){//difficulty level
							vaikeustaso=1;
							SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
							game_new();
						}
						break;
					case 2:
						if(pelivaihe2==0){//options
							pelivaihe2=4;
							SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
						}
						if(pelivaihe2==5){//difficulty level
							vaikeustaso=2;
							SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
							game_new();
						}
						break;
					case 3:
						if(pelivaihe2==0){//exit
							SendMessage( hWnd, WM_CLOSE, 0, 0 );
							//SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
						}
						if(pelivaihe2==5){//Back
							pelivaihe2=0;
							SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
						}
						break;
					case 11:
						if(pelivaihe2==4){//set keys
							pelivaihe2=6;
							valittu=false;//key not selected
							SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
						}
						break;
					case 12:
						if((pelivaihe2==1)||(pelivaihe2==2)){//back
							//if it came to load from workshop
							if(pelivaihe_oli==2){
							pelivaihe2=0;
							pelivaihe=2;
							}
							//if it came to load from menu
							if(pelivaihe_oli==4){
							pelivaihe2=0;
							pelivaihe=4;
							}
							SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
						}
						if(pelivaihe2==3){
							pelivaihe2=2;
							SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
						}
						if(pelivaihe2==4){
							pelivaihe2=0;
							SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);
						}
						if(pelivaihe2==6){	
							pelivaihe2=4;
							SndObjPlay(voices[0], NULL,options[1]&&SOUNDS_LOADED);						
						}
						break;
						
				}				
			}
				
		   }
			break; 
		   
	}
}

void calculatebullets(void)//calculate smokes
{
	int a;
	float savunnopeus=0.1f;
	float rotatenopeus=0.001f;
	
	for (a=0; a<maksimisavuja; a++){
		if(savu[a].pois)continue;
		savu[a].aika=savu[a].aika-elapsed*pelinopeus;

		//A smoke disappears if it is too small
		savu[a].koko=savu[a].koko+savu[a].suurenee*elapsed*pelinopeus;
		if(savu[a].koko<=0) {savu[a].aika=-1;}

		/*if(savu[a].aika<0){   //*if(smoke[a].time<0)
			for (q=a; q<savuja; q++){
						savu[q]=savu[q+1];//smoke
			}
			savuja=savuja-1;//smokes
		}*/
		if(savu[a].aika<0){
			savu[a].pois=true;
			continue;
		}

		//smoke[a].w=savu[a].w+rotatenopeus*savu[a].rotate*elapsed*pelinopeus;//smokes are rolling
		
		//smoke[a].koko=savu[a].koko+0.0001f*elapsed*pelinopeus;

		//smokes fly
		if(savu[a].up!=0){
			//	camx,camy,camz) 		
			/*savu[a].q=-atan2f(-kamerax2+kamerax1,-kameraz2+kameraz1);			
			savu[a].w=0;			
			savu[a].e=-atan2f(-kameray2+kameray1,((-kameraz2+kameraz1+0.1f)*(-kamerax2+kamerax1+0.1f)));
			*/
			savu[a].paikka.x=savu[a].paikka.x+savu[a].cos*elapsed*pelinopeus*savunnopeus;
			savu[a].paikka.y=savu[a].paikka.y+savu[a].up*elapsed*pelinopeus*savunnopeus;
			savu[a].paikka.z=savu[a].paikka.z+savu[a].sin*elapsed*pelinopeus*savunnopeus;
		}

	}
}

void fromsmoke(float koko, float suurenee,bool rotate,float savukesto,float x,float y,float z,int tyyppi,float q,float w,float e)//does smokes and explosion
{
	int a,b;	
	/*if(savuja>=maksimisavuja)//Remove a smokes if there are too many
	{
		for (a=randInt(0,savuja); a<savuja; a++){
						savu[a]=savu[a+1];
			}
			savuja=savuja-1;//smokes
	}*/
	//deciding wich bullet is replaced with a new one
			a=0;
			b=0;
					alku1:
					a=randInt(0,maksimisavuja);
					b=b+1;
					if(b>maksimisavuja)savu[a].pois=true;
					if(!savu[a].pois)goto alku1;

	savu[a].pois=false;
	savu[a].paikka.x=x;
	savu[a].paikka.y=y;
	savu[a].paikka.z=z;
	savu[a].tyyppi=tyyppi;
	savu[a].koko=koko+randDouble(-0.2f,0.2f);
	if(koko<0.1f)koko=0.1f;

	//picture for cloud smoke is randomly selected from to pictures.
	if(tyyppi==2)
	savu[a].kuva=randInt(0,2);

	savu[a].q=q;
	savu[a].w=w;
	savu[a].e=e;
	savu[a].suurenee=suurenee;
	
	
	savu[a].aika=randDouble(0,savukesto);	
	savu[a].cos=(float)cos(savu[a].q);
	savu[a].sin=(float)sin(savu[a].q);
	savu[a].up=0;
	if(rotate)
	{
		savu[a].rotate=randDouble(-pi,pi);
		savu[a].up=(float)sin(savu[a].w);
	}
	else savu[a].rotate=0;

}

void calculatebullets(void)//calculates bullets
{
	int j,a,q,q2,d;	
	D3DXVECTOR3 skaalattu;
	float korkeus,kuljettumatka;
	int pommeja=1;//ammount of explosions

	RECT r1;

	bool osuma;
	float osumax,osumaz,wallkulma,osumax2,osumaz2;
	float osuix,osuiz;
	int sektoreita,w[2],b,c;
	int wallhits;
	int negaatio;
	float dq,temp1;
	//int mapx,mapz;

	for (a=0; a<maksimiluoteja; a++){

		if(luoti[a].poista)continue;	
		
		//time
		if(luoti[a].aika<-1)luoti[a].poista=true;
		if(luoti[a].aika!=-1)luoti[a].aika=luoti[a].aika-elapsed*pelinopeus*0.999f;
		if(a>9){//Bullets at the beginning are for mopeds to run over people
			luoti[a].paikkavanha=luoti[a].paikka;//save old place for collisions
			luoti[a].suunta.y=luoti[a].suunta.y-ase[luoti[a].aseesta].paino*elapsed*pelinopeus;//bullet falls down
			D3DXVec3Scale(&skaalattu,&luoti[a].suunta,elapsed*pelinopeus);//liikkuu * elapsed*pelinopeus //moves*elapsed*gamespeed
			D3DXVec3Add(&luoti[a].paikka,&luoti[a].paikka,&skaalattu);		
			luoti[a].distanssi=sqrtf(sqr(luoti[a].paikka.x-mopot[0].x1)+sqr(luoti[a].paikka.z-mopot[0].z1));		
			if(luoti[a].distanssi>20000){luoti[a].poista=true;continue;}
			if((luoti[a].paikka.x<0)||(luoti[a].paikka.z<0)||(luoti[a].paikka.x>mapsx*8000)||(luoti[a].paikka.z>mapsz*8000)){luoti[a].poista=true;continue;}
		}
		luoti[a].sektorix[0]=(int)luoti[a].paikka.x/8000;
		luoti[a].sektoriz[0]=(int)luoti[a].paikka.z/8000;
		luoti[a].sektorix[1]=(int)luoti[a].paikkavanha.x/8000;
		luoti[a].sektoriz[1]=(int)luoti[a].paikkavanha.z/8000;
		/*luoti[a].jaosx=(int)luoti[a].paikka.x/800;
		luoti[a].jaosz=(int)luoti[a].paikka.z/800;*/
		w[1]=maps[luoti[a].sektoriz[1]][luoti[a].sektorix[1]];//define mapsquare 1
		w[0]=maps[luoti[a].sektoriz[0]][luoti[a].sektorix[0]];//define mapsquare 2
		sektoreita=1;
		if(luoti[a].sektorix[0]!=luoti[a].sektorix[1])sektoreita=2;
		if(luoti[a].sektoriz[0]!=luoti[a].sektoriz[1])sektoreita=2;
		
		
		//homing // seeking target
		if((ase[luoti[a].aseesta].haku)&&(luoti[a].kohde!=-6667)){
			if(luoti[a].kohde<=-1){
				//dq=-atan2f(mopot[-luoti[a].kohde-1].z1-luoti[a].paikka.z,mopot[-luoti[a].kohde-1].x1-luoti[a].paikka.x);
				dq=-atan2f(luoti[a].paikka.z-mopot[-luoti[a].kohde-1].z1,luoti[a].paikka.x-mopot[-luoti[a].kohde-1].x1)+pi;
				//dq=atan2f(mopot[d].z1-mopot[0].z1,mopot[d].x1-mopot[0].x1)+pi;
				luoti[a].e=luoti[a].e+atan2f(mopot[-luoti[a].kohde-1].y1-luoti[a].paikka.y,(mopot[-luoti[a].kohde-1].x1-luoti[a].paikka.x)*(mopot[-luoti[a].kohde-1].z1-luoti[a].paikka.z));
			}
			if(luoti[a].kohde>=0){
				//dq=-atan2f(ukko[luoti[a].kohde].z-luoti[a].paikka.z,ukko[luoti[a].kohde].x-luoti[a].paikka.x);
				dq=-atan2f(luoti[a].paikka.z-ukko[luoti[a].kohde].z,luoti[a].paikka.x-ukko[luoti[a].kohde].x)+pi;
				//dq=atan2f(mopot[d].z1-mopot[0].z1,mopot[d].x1-mopot[0].x1)+pi;
				luoti[a].e=luoti[a].e+atan2f(70-luoti[a].paikka.y,(ukko[luoti[a].kohde].x-luoti[a].paikka.x)*(ukko[luoti[a].kohde].z-luoti[a].paikka.z));
			}
/*
			
				if(luoti[a].q<0)luoti[a].q=luoti[a].q+pi*2;
				if(luoti[a].q>2*pi)luoti[a].q=luoti[a].q-pi*2;

				temp1=luoti[a].q;
				if(temp1-dq>pi)temp1=temp1-pi*2;
				if(dq-temp1>pi)dq=dq-pi*2;
				
					negaatio=1;
					if (dq<temp1)
						negaatio=-1;*/

				if(luoti[a].q>pi*2)luoti[a].q=luoti[a].q-pi*2;
				if(luoti[a].q<0)luoti[a].q=luoti[a].q+pi*2;				
				if(dq>pi*2)dq=dq-pi*2;
				if(dq<0)dq=dq+pi*2;
					//does it turn left or rigth
					negaatio=1;
					temp1=(float)fabs(dq-luoti[a].q);					
					if(temp1>pi*2-temp1)						
					{
						negaatio=-1;
					}	
					
				luoti[a].q=luoti[a].q+negaatio*(dq-luoti[a].q)*elapsed*pelinopeus*3*0.001f;								
												
			
			luoti[a].suunta.x=(float)cos(-luoti[a].q)*luoti[a].nopeus;
			luoti[a].suunta.z=(float)sin(-luoti[a].q)*luoti[a].nopeus;
			luoti[a].suunta.y=(float)sin(luoti[a].e)*luoti[a].nopeus;
		}
			


		//smoketrail
		if(ase[luoti[a].aseesta].savuvana>0)//if there is any smoke
		luoti[a].savuvana=luoti[a].savuvana+elapsed*pelinopeus;
		while(luoti[a].savuvana>0){
			luoti[a].savuvana=luoti[a].savuvana-ase[luoti[a].aseesta].savuvana;
			fromsmoke(ase[luoti[a].aseesta].savukoko, 0.0f,true,100,luoti[a].paikka.x,luoti[a].paikka.y,luoti[a].paikka.z,ase[luoti[a].aseesta].savumaahan,randDouble(-luoti[a].q+pi-pi/2,-luoti[a].q+pi+pi/2),(float)fabs(randDouble(0,pi)),randDouble(0,2*pi));			
		}
		
		
		//there is no point about calculating collisions if a bullet is harmless
		if(ase[luoti[a].aseesta].vahinko<=0){if(luoti[a].paikka.y<0)luoti[a].poista=true; continue;}

		//go thruogh all the sectors that a bullet visits
		for (j=0; j<sektoreita; j++){

			//bullet's retangle
			r1.left=(long)luoti[a].paikkavanha.x-luoti[a].sektorix[j]*8000;			
			r1.top=(long)luoti[a].paikkavanha.z-luoti[a].sektoriz[j]*8000;
			r1.right=(long)luoti[a].paikka.x-luoti[a].sektorix[j]*8000;
			r1.bottom=(long)luoti[a].paikka.z-luoti[a].sektoriz[j]*8000;	
			
			if(luoti[a].paikkavanha.x>luoti[a].paikka.x){
				r1.right=(long)luoti[a].paikkavanha.x-luoti[a].sektorix[j]*8000;
				r1.left=(long)luoti[a].paikka.x-luoti[a].sektorix[j]*8000;
			}
			if(luoti[a].paikkavanha.z>luoti[a].paikka.z){
				r1.bottom=(long)luoti[a].paikkavanha.z-luoti[a].sektoriz[j]*8000;

				r1.top=(long)luoti[a].paikka.z-luoti[a].sektoriz[j]*8000;
			}

		
		//does it hit characters
		if(luoti[a].distanssi<13000)//is the bullet too far away				
		{
			
			for (q=0; q<ukkoja; q++){
				if(luoti[a].paikkavanha.y>(130*ukko[q].korkeus))continue;//if not too high
				if(ukko[q].sektorix!=luoti[a].sektorix[j])continue;//sector check
				if(ukko[q].sektoriz!=luoti[a].sektoriz[j])continue;//sector check
				if(luoti[a].kuka==q)continue;//characters cannot shoot them selves
				if(ukko[q].distanssi>10000)continue;//there is no point about calculating if a character is too far
				if(ukko[q].kuole)continue;//continue if it already has hit
				if(ukko[q].pois)continue;//continue if it already has hit
				
				if(sqrtf(sqr(luoti[a].paikka.x-ukko[q].x)+sqr(luoti[a].paikka.z-ukko[q].z))>luoti[a].nopeus*elapsed*pelinopeus+100)
				{continue;}
					
				if(!linecollidesline(&osuma,&osumax,&osumaz,luoti[a].paikkavanha.x-luoti[a].sektorix[j]*8000,luoti[a].paikkavanha.z-luoti[a].sektoriz[j]*8000,luoti[a].paikka.x-luoti[a].sektorix[j]*8000,luoti[a].paikka.z-luoti[a].sektoriz[j]*8000,ukko[q].x-ukko[q].sektorix*8000-40,ukko[q].z-ukko[q].sektoriz*8000-40,ukko[q].x-ukko[q].sektorix*8000+40,ukko[q].z-ukko[q].sektoriz*8000+40))continue;
				if(linecollidesline(&osuma,&osumax,&osumaz,luoti[a].paikkavanha.x-luoti[a].sektorix[j]*8000,luoti[a].paikkavanha.z-luoti[a].sektoriz[j]*8000,luoti[a].paikka.x-luoti[a].sektorix[j]*8000,luoti[a].paikka.z-luoti[a].sektoriz[j]*8000,ukko[q].x-ukko[q].sektorix*8000+40,ukko[q].z-ukko[q].sektoriz*8000+40,ukko[q].x-ukko[q].sektorix*8000-40,ukko[q].z-ukko[q].sektoriz*8000-40))
				{
					kuljettumatka=(float)sqrtf(sqr(osumax+luoti[a].sektorix[j]*8000-luoti[a].paikkavanha.x)+sqr(osumaz+luoti[a].sektoriz[j]*8000-luoti[a].paikkavanha.z))/(luoti[a].nopeus*elapsed*pelinopeus);
					korkeus=luoti[a].paikkavanha.y+kuljettumatka*(luoti[a].paikka.y-luoti[a].paikkavanha.y);
				
					//a passive character may change tacktic if he is being shot
					if(luoti[a].kenen==0)//bullet is not players
					if(ukko[q].puoli==1){
						//character escapes if it doesnt have a gun
						if(ukko[q].aseena==-1)ukko[q].taktiikka=2;
						//character attacks if it has a gun
						if(ukko[q].aseena!=-1)ukko[q].taktiikka=0;
					}

					//reducing energy and removing bullet					
					ukko[q].energia=ukko[q].energia-ase[luoti[a].aseesta].vahinko;
					luoti[a].poista=true;

					//blood
					//if(ase[luoti[a].aseesta].kimmokkeita!=0){
						for (q2=0; q2<50; q2++){
							shoot(-6667,-1,luoti[a].kenen,randDouble(0,250),mopot,4,osumax+luoti[a].sektorix[j]*8000,korkeus,osumaz+luoti[a].sektoriz[j]*8000,luoti[a].q,luoti[a].w,luoti[a].e);
						}					
					//}
					
					//character dies
					if(ukko[q].energia<0){						
						ukko[q].kuole=true;
						//payment for player
						if(luoti[a].kenen==0)//bullet is player's
						mopot[luoti[a].kenen].rahat=mopot[luoti[a].kenen].rahat+1;
						//bodyparts fly
						for (q2=0; q2<11; q2++){
							ukko[q].ruumiinosa[q2].gox=(float)randDouble(-0.3f,0.3f);
							ukko[q].ruumiinosa[q2].goy=(float)randDouble(-0.3f,0.3f);
							ukko[q].ruumiinosa[q2].goz=(float)randDouble(-0.3f,0.3f);

						}
					}

					//smoke to air
					if(ase[luoti[a].aseesta].savumaahan!=0)
						for (q2=0; q2<3; q2++){	
							fromsmoke(ase[luoti[a].aseesta].savukoko, 0.001f,true,ase[luoti[a].aseesta].savukesto+1000,osumax+luoti[a].sektorix[j]*8000,luoti[a].paikka.y,osumaz+luoti[a].sektoriz[j]*8000,ase[luoti[a].aseesta].savumaahan,randDouble(-luoti[a].q+pi-pi/2,-luoti[a].q+pi+pi/2),(float)fabs(randDouble(0,pi)),randDouble(0,2*pi));
						}
					//explosion
					if(ase[luoti[a].aseesta].pommi!=0){
						for (q2=0; q2<ase[luoti[a].aseesta].pommi*30; q2++){
						shoot(-6667,-1,luoti[a].kenen,randDouble(100,300),mopot,2,osumax+luoti[a].sektorix[j]*8000,luoti[a].paikka.y,osumaz+luoti[a].sektoriz[j]*8000,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
						}
						for (q2=0; q2<pommeja; q2++){
							fromsmoke(ase[luoti[a].aseesta].savukoko, 0.004f*ase[luoti[a].aseesta].pommi,true,ase[luoti[a].aseesta].savukesto,osumax+luoti[a].sektorix[j]*8000,luoti[a].paikka.y,osumaz+luoti[a].sektoriz[j]*8000,3,0,0,0);							
						}
						quake=10000/luoti[a].distanssi;
						playsound(8,2,osumax+luoti[a].sektorix[j]*8000,osumaz+luoti[a].sektoriz[j]*8000);
					}
					//sound
					if(ase[luoti[a].aseesta].pommi==0){
						if(ase[luoti[a].aseesta].tyyppi!=4)
						playsound(randInt(13,18),1,osumax+luoti[a].sektorix[j]*8000,osumaz+luoti[a].sektoriz[j]*8000);
					}

				}
			}
		}

	//does it hit a bike
	for (d=0; d<mopoja; d++){
		if(a<10)continue;
		if(mopot[d].pois)continue;
		if(mopot[d].sektorix!=luoti[a].sektorix[j])continue;//sector check
		if(mopot[d].sektoriz!=luoti[a].sektoriz[j])continue;//sector check
				
		if(luoti[a].kenen!=d){//is not player's
		//if it is too close
		if(sqrtf(sqr(mopot[d].x1-luoti[a].paikka.x)+sqr(mopot[d].z1-luoti[a].paikka.z))<60){
			//reducing energy

					mopot[d].energia=mopot[d].energia-ase[luoti[a].aseesta].vahinko;
			//bounce
					if(ase[luoti[a].aseesta].kimmokkeita!=0){
						for (q2=0; q2<ase[luoti[a].aseesta].kimmokkeita; q2++){
							shoot(-6667,-1,luoti[a].kenen,randDouble(0,50),mopot,3,mopot[d].x1,70,mopot[d].z1,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
						}					
					}
			//smoke to air
					if(ase[luoti[a].aseesta].savumaahan!=0)
						for (q=0; q<3; q++){							
							fromsmoke(ase[luoti[a].aseesta].savukoko, 0.001f,true,ase[luoti[a].aseesta].savukesto+1000,mopot[d].x1,70,mopot[d].z1,ase[luoti[a].aseesta].savumaahan,randDouble(-luoti[a].q+pi-pi/2,-luoti[a].q+pi+pi/2),(float)fabs(randDouble(0,pi)),randDouble(0,2*pi));
						}
			//explosion					
					if(ase[luoti[a].aseesta].pommi!=0){
						for (q2=0; q2<ase[luoti[a].aseesta].pommi*30; q2++){
						shoot(-6667,-1,luoti[a].kenen,randDouble(100,300),mopot,3,mopot[d].x1,70,mopot[d].z1,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));						
						}
						for (q2=0; q2<pommeja; q2++){
							fromsmoke(ase[luoti[a].aseesta].savukoko, 0.004f*ase[luoti[a].aseesta].pommi,true,ase[luoti[a].aseesta].savukesto,mopot[d].x1,70,mopot[d].z1,3,0,0,0);													
						}
						quake=10000/luoti[a].distanssi;
						playsound(8,2,osumax+luoti[a].sektorix[j]*8000,osumaz+luoti[a].sektoriz[j]*8000);
					}
			//sound
					if(ase[luoti[a].aseesta].pommi==0){
						if(ase[luoti[a].aseesta].tyyppi!=4)
						playsound(randInt(9,13),1,osumax+luoti[a].sektorix[j]*8000,osumaz+luoti[a].sektoriz[j]*8000);
					}
			//removing bullet
					luoti[a].poista=true;
		}

		//does it collide with lines
		if(linecollidesline(&osuma,&osuix,&osuiz,luoti[a].paikkavanha.x-luoti[a].sektorix[j]*8000,luoti[a].paikkavanha.z-luoti[a].sektoriz[j]*8000,luoti[a].paikka.x-luoti[a].sektorix[j]*8000,luoti[a].paikka.z-luoti[a].sektoriz[j]*8000,	mopot[d].x6-luoti[a].sektorix[j]*8000,mopot[d].z6-luoti[a].sektoriz[j]*8000,mopot[d].x5-luoti[a].sektorix[j]*8000,mopot[d].z5-luoti[a].sektoriz[j]*8000))

		{			
			kuljettumatka=(float)sqrtf(sqr(osuix+luoti[a].sektorix[j]*8000-luoti[a].paikkavanha.x)+sqr(osuiz+luoti[a].sektoriz[j]*8000-luoti[a].paikkavanha.z))/(luoti[a].nopeus*elapsed*pelinopeus);
			korkeus=luoti[a].paikkavanha.y+kuljettumatka*(luoti[a].paikka.y-luoti[a].paikkavanha.y);			
			float xa,za; 
			xa=sqrtf(sqr(osuix-mopot[d].x6+luoti[a].sektorix[j]*8000)+sqr(osuiz-mopot[d].z6+luoti[a].sektoriz[j]*8000));
			za=korkeus;

			wallhits=0;
			//is it inside a sidepicture
			for (b=0; b<viivagroup[1].viivat[0].viivaa; b++){
				for (c=0; c<viivagroup[1].viivat[0].viiva[b].linjaa; c++){									
					if(linecollidesline(&osuma,&osumax,&osumaz,xa,za,xa+1000,za+1000,	viivagroup[1].viivat[0].viiva[b].piste[c].x1,viivagroup[1].viivat[0].viiva[b].piste[c].z1,viivagroup[1].viivat[0].viiva[b].piste[c].x2,viivagroup[1].viivat[0].viiva[b].piste[c].z2))
						wallhits=wallhits+1;
				}
			}
			if((float)wallhits/2*1000!=((int)(wallhits/2))*1000){	
			//reduce energy
					mopot[d].energia=mopot[d].energia-ase[luoti[a].aseesta].vahinko;
			//bounce
					if(ase[luoti[a].aseesta].kimmokkeita!=0){
						for (q2=0; q2<ase[luoti[a].aseesta].kimmokkeita; q2++){
							shoot(-6667,-1,luoti[a].kenen,randDouble(0,50),mopot,3,osuix+luoti[a].sektorix[j]*8000,korkeus,osuiz+luoti[a].sektoriz[j]*8000,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
						}					
					}
			//smoke to air
					if(ase[luoti[a].aseesta].savumaahan!=0)
						for (q=0; q<3; q++){							
							fromsmoke(ase[luoti[a].aseesta].savukoko, 0.001f,true,ase[luoti[a].aseesta].savukesto+1000,osuix+luoti[a].sektorix[j]*8000,korkeus,osuiz+luoti[a].sektoriz[j]*8000,ase[luoti[a].aseesta].savumaahan,randDouble(-luoti[a].q+pi-pi/2,-luoti[a].q+pi+pi/2),(float)fabs(randDouble(0,pi)),randDouble(0,2*pi));
						}
			//explosion				
					if(ase[luoti[a].aseesta].pommi!=0){
						for (q2=0; q2<ase[luoti[a].aseesta].pommi*30; q2++){
						shoot(-6667,-1,luoti[a].kenen,randDouble(100,300),mopot,3,osuix+luoti[a].sektorix[j]*8000,korkeus,osuiz+luoti[a].sektoriz[j]*8000,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));						
						}
						for (q2=0; q2<pommeja; q2++){
							fromsmoke(ase[luoti[a].aseesta].savukoko, 0.004f*ase[luoti[a].aseesta].pommi,true,ase[luoti[a].aseesta].savukesto,osuix+luoti[a].sektorix[j]*8000,korkeus,osuiz+luoti[a].sektoriz[j]*8000,3,0,0,0);													
						}
						quake=10000/luoti[a].distanssi;
						playsound(8,2,osumax+luoti[a].sektorix[j]*8000,osumaz+luoti[a].sektoriz[j]*8000);
					}
			//sound
					if(ase[luoti[a].aseesta].pommi==0){
						if(ase[luoti[a].aseesta].tyyppi!=4)
						playsound(randInt(9,13),1,osumax+luoti[a].sektorix[j]*8000,osumaz+luoti[a].sektoriz[j]*8000);
					}
			//removing bullet
					luoti[a].poista=true;
			}
		}
		}
		
		//}	
		/*	
		matriisi->LoadIdentity();
		matriisi->TranslateLocal(mopot->x6+xa,0+za,mopot->z6);
		matriisi->ScaleLocal(0.2f,0.2f,0.2f);
		drawfast(&mallit[2].malli[5]);

		matriisi->LoadIdentity();
		matriisi->TranslateLocal(mopot->x5,0,mopot->z5);
		matriisi->ScaleLocal(0.2f,0.2f,0.2f);
		drawfast(&mallit[2].malli[5]);

		matriisi->LoadIdentity();
		matriisi->TranslateLocal(mopot->x6,0,mopot->z6);
		matriisi->ScaleLocal(0.2f,0.2f,0.2f);
		drawfast(&mallit[2].malli[5]);
					
pvertex luotitrace[maksimiluoteja*2];	
q=6;
		for (b=0; b<viivagroup[1].viivat[0].viivaa; b++){
		for (c=0; c<viivagroup[1].viivat[0].viiva[b].linjaa; c++){	
		q=q+1;
		matriisi->LoadIdentity();
		matriisi->TranslateLocal(mopot->x6,0,mopot->z6);
		luotitrace[c*2].position.x=viivagroup[1].viivat[0].viiva[b].piste[c].x1;
		luotitrace[c*2].position.y=viivagroup[1].viivat[0].viiva[b].piste[c].z1;
		luotitrace[c*2].position.z=0;
		
		luotitrace[c*2+1].position.x=viivagroup[1].viivat[0].viiva[b].piste[c].x2;
		luotitrace[c*2+1].position.y=viivagroup[1].viivat[0].viiva[b].piste[c].z2;
		luotitrace[c*2+1].position.z=0;

			luotitrace[c*2].u=0;
			luotitrace[c*2].v=0.16f;
			luotitrace[c*2+1].u=1;
			luotitrace[c*2+1].v=0.16f;
			}
		
		m_pDevice->SetMaterial( &mat[30] );
		m_pDevice->SetTexture( 0, tausta[30] );
		m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());		  				
		m_pDevice->DrawPrimitive(D3DPT_LINELIST  ,
			D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,luotitrace,q,NULL);
			
			}
*/
		}

		

	//does it hit a wall
		for (b=0; b<viivagroup[0].viivat[w[j]].viivaa; b++){
			for (c=0; c<viivagroup[0].viivat[w[j]].viiva[b].linjaa; c++){
				
				if(linecollidesline(&osuma,&osumax,&osumaz,luoti[a].paikkavanha.x-luoti[a].sektorix[j]*8000,luoti[a].paikkavanha.z-luoti[a].sektoriz[j]*8000,luoti[a].paikka.x-luoti[a].sektorix[j]*8000,luoti[a].paikka.z-luoti[a].sektoriz[j]*8000,	viivagroup[0].viivat[w[j]].viiva[b].piste[c].x1,viivagroup[0].viivat[w[j]].viiva[b].piste[c].z1,viivagroup[0].viivat[w[j]].viiva[b].piste[c].x2,viivagroup[0].viivat[w[j]].viiva[b].piste[c].z2))
				{
					wallkulma=-atan2f(viivagroup[0].viivat[w[j]].viiva[b].piste[c].z2-viivagroup[0].viivat[w[j]].viiva[b].piste[c].z1,viivagroup[0].viivat[w[j]].viiva[b].piste[c].x2-viivagroup[0].viivat[w[j]].viiva[b].piste[c].x1);
					osumax2=osumax+cosf(-luoti[a].q+pi+pi)*-100;
					osumaz2=osumaz+sinf(-luoti[a].q+pi+pi)*-100;
					//prosentual distance that the bullet has travelled before collision. 
					kuljettumatka=(float)sqrtf(sqr(osumax+luoti[a].sektorix[j]*8000-luoti[a].paikkavanha.x)+sqr(osumaz+luoti[a].sektoriz[j]*8000-luoti[a].paikkavanha.z))/(luoti[a].nopeus*elapsed*pelinopeus);
					korkeus=luoti[a].paikkavanha.y+kuljettumatka*(luoti[a].paikka.y-luoti[a].paikkavanha.y);
					
			
					//bullet hole
					if(ase[luoti[a].aseesta].monttukuva>-1)
					fromsmoke(ase[luoti[a].aseesta].savukoko, 0,false,40000,osumax+luoti[a].sektorix[j]*8000,korkeus,osumaz+luoti[a].sektoriz[j]*8000,ase[luoti[a].aseesta].monttukuva,-wallkulma,randDouble(0,2*pi),0);
					//smoke to air
					if(ase[luoti[a].aseesta].savumaahan!=0)
						for (q=0; q<3; q++){							
							fromsmoke(ase[luoti[a].aseesta].savukoko, 0.001f,true,ase[luoti[a].aseesta].savukesto+1000,osumax2+luoti[a].sektorix[j]*8000,korkeus,osumaz2+luoti[a].sektoriz[j]*8000,ase[luoti[a].aseesta].savumaahan,randDouble(-luoti[a].q+pi-pi/2,-luoti[a].q+pi+pi/2),(float)fabs(randDouble(0,pi)),randDouble(0,2*pi));
						}
					//explosion					
					if(ase[luoti[a].aseesta].pommi!=0){
						for (q2=0; q2<ase[luoti[a].aseesta].pommi*30; q2++){
						shoot(-6667,-1,luoti[a].kenen,randDouble(100,300),mopot,2,osumax+luoti[a].sektorix[j]*8000,korkeus,osumaz+luoti[a].sektoriz[j]*8000,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
						}
						for (q2=0; q2<pommeja; q2++){
							fromsmoke(ase[luoti[a].aseesta].savukoko, 0.004f*ase[luoti[a].aseesta].pommi,true,ase[luoti[a].aseesta].savukesto,osumax+luoti[a].sektorix[j]*8000,korkeus,osumaz+luoti[a].sektoriz[j]*8000,3,0,0,0);							
						}
						quake=10000/luoti[a].distanssi;
						playsound(8,2,osumax+luoti[a].sektorix[j]*8000,osumaz+luoti[a].sektoriz[j]*8000);
					}
					//bounce
					if(ase[luoti[a].aseesta].kimmokkeita>0){
						for (q2=0; q2<ase[luoti[a].aseesta].kimmokkeita; q2++){
							shoot(-6667,-1,luoti[a].kenen,randDouble(0,50),mopot,3,osumax+luoti[a].sektorix[j]*8000,korkeus,osumaz+luoti[a].sektoriz[j]*8000,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
						}
					}
					//sound
					if(ase[luoti[a].aseesta].pommi==0){
						if(ase[luoti[a].aseesta].tyyppi!=4)
						playsound(randInt(9,13),1,osumax+luoti[a].sektorix[j]*8000,osumaz+luoti[a].sektoriz[j]*8000);
					}
					
					

					//light
				//	setLights(osumax2+luoti[a].sektorix*8000,luoti[a].paikka.y,osumaz2+luoti[a].sektoriz*8000);


					luoti[a].poista=true;
				}
			}
		}
		
		

		if(luoti[a].paikka.y<0)//bullet hits the ground
		{
			//smoke to air
					if(ase[luoti[a].aseesta].savumaahan!=0)
						for (q=0; q<3; q++){
							osumax=osumax+cosf(-luoti[a].q+pi+pi)*-100;
							osumaz=osumaz+sinf(-luoti[a].q+pi+pi)*-100;
							fromsmoke(ase[luoti[a].aseesta].savukoko, 0.001f,true,ase[luoti[a].aseesta].savukesto,luoti[a].paikka.x,0,luoti[a].paikka.z,ase[luoti[a].aseesta].savumaahan,randDouble(-luoti[a].q+pi-pi/2,-luoti[a].q+pi+pi/2),(float)fabs(randDouble(0,pi)),randDouble(0,2*pi));
						}
			//explosion				
					if(ase[luoti[a].aseesta].pommi!=0){
						for (q2=0; q2<ase[luoti[a].aseesta].pommi*30; q2++){
						shoot(-6667,-1,luoti[a].kenen,randDouble(100,300),mopot,2,luoti[a].paikka.x,luoti[a].paikka.y,luoti[a].paikka.z,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
						}
						for (q2=0; q2<pommeja; q2++){
							fromsmoke(ase[luoti[a].aseesta].savukoko, 0.004f*ase[luoti[a].aseesta].pommi,true,ase[luoti[a].aseesta].savukesto,luoti[a].paikka.x,0,luoti[a].paikka.z,3,0,0,0);							
						}
						quake=10000/luoti[a].distanssi;
						playsound(8,2,luoti[a].paikka.x,luoti[a].paikka.z);
					}
			//sound
					if(ase[luoti[a].aseesta].pommi==0){
						if(ase[luoti[a].aseesta].tyyppi!=4)
						playsound(randInt(9,13),1,luoti[a].paikka.x,luoti[a].paikka.z);
					}

			luoti[a].poista=true;
		}
		}//j ends
		
		if(luoti[a].paikka.y>2500)luoti[a].poista=true;
	
	}
	
}

void setLights(float x,float y,float z)
{

	int q;
	for (q=0; q<maksimivaloja; q++) if(lamppu[q].on==false) break;//searching for free lightbulb (lamppu = lightbulb)
		if(q>=maksimivaloja)q=randInt(0,maksimivaloja);//if there is no free light bulbs

		
	//if(valoja>=maksimivaloja)removeLight(randInt(0,valoja),&valoja);

			lamppu[q].on=true;				
			lamppu[q].valo.dltType = D3DLIGHT_POINT;	
			lamppu[q].valo.dcvDiffuse.r = 1.0f;    
			lamppu[q].valo.dcvDiffuse.g = 1.0f;
			lamppu[q].valo.dcvDiffuse.b = 1.0f;    
			lamppu[q].valo.dcvAmbient.r = 1.0f;
			lamppu[q].valo.dcvAmbient.g = 1.0f;    
			lamppu[q].valo.dcvAmbient.b = 1.0f;
			lamppu[q].valo.dcvSpecular.r = 1.0f;    
			lamppu[q].valo.dcvSpecular.g = 1.0f;
			lamppu[q].valo.dcvSpecular.b = 1.0f;
			lamppu[q].valo.dvDirection=1.0f; 
			lamppu[q].valo.dvPosition.x = x;
			lamppu[q].valo.dvPosition.y = y;  
			lamppu[q].valo.dvPosition.z = z;
			lamppu[q].valo.dvAttenuation0 = 0.5f;
			lamppu[q].valo.dvAttenuation1=0.0f;	
			lamppu[q].valo.dvAttenuation2=0.0f;
			lamppu[q].valo.dvRange = 500;
			
			m_pDevice->SetLight(q, &lamppu[q].valo);
			m_pDevice->LightEnable(q, TRUE);
}

	
void shoot(int kohde,int kuka, int kenen,float aika,bikebase *mopot, int aseena,float paikkax,float paikkay,float paikkaz,float suuntax,float suuntay,float suuntaz)//shooting
{	
	int a,b,q;
	int d=-1;
	float rekyyli;

	if(paikkax==NULL){//shooting from a bike
		while(mopot->asetime[aseena]>=0){
			mopot->asetime[aseena]=mopot->asetime[aseena]-ase[mopot->ase[aseena]].ampumanopeus;
			for (q=0; q<ase[mopot->ase[aseena]].hauleja; q++){
			//deciding wich bullet is replaced with a new one
			a=10;
			b=0;
					alku1:
					a=randInt(10,maksimiluoteja);
					b=b+1;
					if(b>maksimiluoteja)luoti[a].poista=true;
					if(!luoti[a].poista)goto alku1;
						
			d=a;
			//recoil
			rekyyli=((ase[mopot->ase[aseena]].pvahinko+ase[mopot->ase[aseena]].pnopeus)/ase[mopot->ase[aseena]].pampumanopeus)*0.05f;						
			mopot->nopeus=mopot->nopeus-rekyyli;
			if(mopot->nopeus<-1.5f)mopot->nopeus=-1.5f;

			
			mopot->suuliekki=true;
			luoti[a].poista=false;
			luoti[a].kenen=kenen;
			luoti[a].aseesta=mopot->ase[aseena];
			luoti[a].savuvana=ase[mopot->ase[aseena]].savuvana;
			/*luoti[a].paikka.x=mopot->x1+cosf(mopot->suunta)*15*mopot->nopeus;
			luoti[a].paikka.y=mopot->y1+70;
			luoti[a].paikka.z=mopot->z1+sinf(mopot->suunta)*15*mopot->nopeus;*/
			luoti[a].paikka.x=mopot->piippu.m30;
			luoti[a].paikka.y=mopot->piippu.m31;
			luoti[a].paikka.z=mopot->piippu.m32;

			luoti[a].paikkavanha=luoti[a].paikka;
			luoti[a].q=-mopot->suunta;//-mopeds->frontdirection;
			luoti[a].w=mopot->kulmakallistus;
			luoti[a].e=mopot->kulmakeuliminen;
			luoti[a].aika=aika;
			luoti[a].kuka=kuka;
			//player is target if it is a AI-player's
			if(kenen>0)luoti[a].kohde=-1;
			else luoti[a].kohde=kohde;
			
			//bullet speed
			if(ase[mopot->ase[aseena]].nopeus==666)
				luoti[a].nopeus=randDouble(1.5f,3.5f);
				else luoti[a].nopeus=ase[mopot->ase[aseena]].nopeus;

		
			//speed=random
			if(ase[mopot->ase[aseena]].nopeus==666)
			{
			luoti[a].suunta.x=(float)cos(-luoti[a].q)*luoti[a].nopeus+randDouble(-ase[mopot->ase[aseena]].hajonta,ase[mopot->ase[aseena]].hajonta);
			luoti[a].suunta.z=(float)sin(-luoti[a].q)*luoti[a].nopeus+randDouble(-ase[mopot->ase[aseena]].hajonta,ase[mopot->ase[aseena]].hajonta);
			luoti[a].suunta.y=(float)sin(luoti[a].e)*luoti[a].nopeus+randDouble(-ase[mopot->ase[aseena]].hajonta,ase[mopot->ase[aseena]].hajonta);
			}
			//moving normally
			else
			{
			luoti[a].suunta.x=(float)cos(-luoti[a].q)*luoti[a].nopeus+randDouble(-ase[mopot->ase[aseena]].hajonta,ase[mopot->ase[aseena]].hajonta);
			luoti[a].suunta.z=(float)sin(-luoti[a].q)*luoti[a].nopeus+randDouble(-ase[mopot->ase[aseena]].hajonta,ase[mopot->ase[aseena]].hajonta);
			luoti[a].suunta.y=(float)sin(luoti[a].e)*luoti[a].nopeus+randDouble(-ase[mopot->ase[aseena]].hajonta,ase[mopot->ase[aseena]].hajonta);
			}
			}

		}
	}

	else{//shot from else where
		for (q=0; q<ase[aseena].hauleja; q++){
			//deciding wich bullet is replaced with a new one

			a=10;
			b=0;
					alku2:
					a=randInt(10,maksimiluoteja);
					b=b+1;
					if(b>maksimiluoteja)luoti[a].poista=true;
					if(!luoti[a].poista)goto alku2;
		d=a;

		//mopot->asetime[aseena]=mopot->asetime[aseena]-ase[mopot->ase[aseena]].ampumanopeus;
		luoti[a].poista=false;
		luoti[a].kenen=kenen;
		luoti[a].aseesta=aseena;
		luoti[a].savuvana=ase[aseena].savuvana;
		luoti[a].paikka.x=paikkax;
		luoti[a].paikka.y=paikkay;
		luoti[a].paikka.z=paikkaz;
		luoti[a].paikkavanha=luoti[a].paikka;
		luoti[a].q=suuntax;
		luoti[a].w=suuntay;
		luoti[a].e=suuntaz;
		luoti[a].aika=aika;
		luoti[a].kuka=kuka;
		luoti[a].kohde=kohde;

		//bullet speed
		if((ase[aseena].nopeus==666))
			luoti[a].nopeus=randDouble(1.5f,3.5f);
			else luoti[a].nopeus=ase[aseena].nopeus;

			//voices
			if(ase[luoti[a].aseesta].tyyppi==0)playsound(2,1,luoti[a].paikka.x,luoti[a].paikka.z);
			if(ase[luoti[a].aseesta].tyyppi==1)playsound(5,1,luoti[a].paikka.x,luoti[a].paikka.z);
			if(ase[luoti[a].aseesta].tyyppi==2)playsound(4,1,luoti[a].paikka.x,luoti[a].paikka.z);
			if(ase[luoti[a].aseesta].tyyppi==3)playsound(3,1,luoti[a].paikka.x,luoti[a].paikka.z);


			//speed=random
			if(ase[aseena].nopeus==666)
			{
			luoti[a].suunta.x=(float)cos(-luoti[a].q)*luoti[a].nopeus+randDouble(-ase[aseena].hajonta,ase[aseena].hajonta);
			luoti[a].suunta.z=(float)sin(-luoti[a].q)*luoti[a].nopeus+randDouble(-ase[aseena].hajonta,ase[aseena].hajonta);
			luoti[a].suunta.y=(float)sin(luoti[a].e)*luoti[a].nopeus+randDouble(-ase[aseena].hajonta,ase[aseena].hajonta);
			}
			//moves normally
			else
			{
			luoti[a].suunta.x=(float)cos(-luoti[a].q)*luoti[a].nopeus+randDouble(-ase[aseena].hajonta,ase[aseena].hajonta);
			luoti[a].suunta.z=(float)sin(-luoti[a].q)*luoti[a].nopeus+randDouble(-ase[aseena].hajonta,ase[aseena].hajonta);
			luoti[a].suunta.y=(float)sin(luoti[a].e)*luoti[a].nopeus+randDouble(-ase[aseena].hajonta,ase[aseena].hajonta);
			}	
		}
	}


			//äänet //a= vähän epävarma
	if(d>=0){
			if(ase[luoti[d].aseesta].tyyppi==0)playsound(2,1,luoti[d].paikka.x,luoti[d].paikka.z);
			if(ase[luoti[d].aseesta].tyyppi==1)playsound(5,1,luoti[d].paikka.x,luoti[d].paikka.z);
			if(ase[luoti[d].aseesta].tyyppi==2)playsound(4,1,luoti[d].paikka.x,luoti[d].paikka.z);
			if(ase[luoti[d].aseesta].tyyppi==3)playsound(3,1,luoti[d].paikka.x,luoti[d].paikka.z);			
	}

	
}

void aja(bikebase *mopot)
{
	int q,temp1;
	float temp2;
	float kerroin;
	float tuulenvastus;

	//computers drive slower
	//if(mopot->numero==0)
		tuulenvastus=0.2f;
	//else tuulenvastus=0.2f;

	if(mopot->left||mopot->right)
		tuulenvastus=0.24f;

	
	/*
	float nopeusnyt = mopot->nopeus*elapsed;	
	float nopeus=0;

	mopot->nopeutena[50]=(float)(nopeusnyt - nopeusoli);
	for (q=0; q<50; q++){
		mopot->nopeutena[q]=mopot->nopeutena[q+1];
		nopeus=nopeus+mopot->nopeutena[q];
	}
	nopeus=nopeus/50;
	nopeusoli = nopeusnyt;

	mopot->nopeus=mopot->nopeus*elapsed;
*/

	

	if(!mopot->left&&!mopot->right)mopot->turntime=0;
	else mopot->turntime=mopot->turntime+elapsed*pelinopeus;
	
	// choosing targetted character
	mopot->valittuukko=-6667;
	for (q=0; q<ukkoja; q++){
		if(ukko[q].pois)continue;
		if(ukko[q].kuole)continue;
		//accepted angle is 0.075f
		if(fabs(fabs(ukko[q].kulmamopoon)-fabs(mopot->suunta))<0.08f)//if angle is right
		{
			if(mopot->valittuukko==-6667){mopot->valittuukko=q;continue;}
			if(fabs(fabs(ukko[mopot->valittuukko].kulmamopoon)-fabs(mopot->suunta))<0.075f)//if last angle is rigth
			{
				if(ukko[q].distanssi<ukko[mopot->valittuukko].distanssi)//if last angle is farther
				mopot->valittuukko=q;
			}
			else mopot->valittuukko=q;
		}
	}
	// choosing targetted moped
	temp1=-6667;
	for (q=0; q<mopoja; q++){
		if(q==mopot->numero)continue;
		if(mopot[q].pois)continue;
		//accepted angle is 0.075f
		if(fabs(fabs(mopot[q].kulmamopoon)-fabs(mopot->suunta))<0.1f)//is angle is rigth
		{
			if(temp1==-6667){temp1=q;continue;}
			if(fabs(fabs(mopot[temp1].kulmamopoon)-fabs(mopot->suunta))<0.075f)//if last angle is rigth
			{
				if(mopot[q].distanssi<mopot[temp1].distanssi)//if last angle is farther
				temp1=q;
			}
			else temp1=q;
		}
	}

	//if there is moped front. shoot it instead
	if(temp1!=-6667) mopot->valittuukko=-temp1-1;

					mopot->x3=mopot->x1;
					mopot->y3=mopot->y1;
					mopot->z3=mopot->z1;
					mopot->x4=mopot->x2;
					mopot->y4=mopot->y2;
					mopot->z4=mopot->z2;


	if(mopot->timesparks>=0)mopot->timesparks=mopot->timesparks-elapsed*pelinopeus;
	if(mopot->asetime[0]<0)mopot->asetime[0]=mopot->asetime[0]+elapsed*pelinopeus;
	if(mopot->asetime[1]<0)mopot->asetime[1]=mopot->asetime[1]+elapsed*pelinopeus;
	if(mopot->asetime[2]<0)mopot->asetime[2]=mopot->asetime[2]+elapsed*pelinopeus;
	if(mopot->asetime[3]<0)mopot->asetime[3]=mopot->asetime[3]+elapsed*pelinopeus;



	if((mopot->enter==false) & (mopot->enter2==true))
	{
		//asking for a mission
		if(mopot->mission.suoritettu!=0)//there is no mission
		if(mopot->nearestukko>-1)	
		if(ukko[mopot->nearestukko].puoli==0)
		if(!ukko[mopot->nearestukko].kuole)
			if(fabs(mopot->nopeus)<0.7f){
				arvo_mission(mopot,-1);
				pelivaihe=1;
				SndObjStop(voices[1]);
			}
	}

	if(mopot->up)//throttle
	{
		mopot->kulmakeuliminen=mopot->kulmakeuliminen+2*0.4f*0.001f*elapsed*pelinopeus;
		mopot->nopeus=mopot->nopeus+(0.002f-sqr(mopot->nopeus)*tuulenvastus/1000)*elapsed*pelinopeus;
	}
	else if(mopot->down)//brake
	{
		if(mopot->kulmakeuliminen>0)
			mopot->kulmakeuliminen=mopot->kulmakeuliminen-2*0.3f*0.001f*elapsed*pelinopeus;
		if(mopot->nopeus>0)//while braking
		mopot->nopeus=mopot->nopeus-(0.002f+sqr(mopot->nopeus)*tuulenvastus/1000)*elapsed*pelinopeus;
		else//while reverse
		mopot->nopeus=mopot->nopeus-(0.0005f-sqr(mopot->nopeus)*tuulenvastus/1000)*elapsed*pelinopeus;
	}
	if((!mopot->down)&&(!mopot->up))//no throtle or brake
	{
		if(mopot->nopeus>0)
			mopot->nopeus=mopot->nopeus-(sqr(mopot->nopeus)*tuulenvastus/1000)*elapsed*pelinopeus;
		else
			mopot->nopeus=mopot->nopeus+(sqr(mopot->nopeus)*tuulenvastus/1000)*elapsed*pelinopeus;
	}
	
	//tilting bike
	mopot->kulmakallistus=mopot->etusuunta*sqr(mopot->nopeus);

	//pop a wheelie
	//if(mopot->kulmakeuliminen>0) //if(mopeds->wheelie angle>0)
			mopot->kulmakeuliminen=mopot->kulmakeuliminen-(float)fabs((mopot->nopeus*0.4f+0.2f)*0.001f*elapsed*pelinopeus);
	if(mopot->kulmakeuliminen>pi/4)mopot->kulmakeuliminen=pi/4;
	if(mopot->kulmakeuliminen<0) mopot->kulmakeuliminen=0;

	//if(mopot->kulmakeuliminen>0.5f)	//if(mopeds->wheelie angle>0.5f)
	//if(randInt((int)(mopot->kulmakeuliminen*elapsed),10)==9)			


	//mopeds release smoke
	mopot->savuaika=mopot->savuaika+elapsed*pelinopeus*(mopot->kulmakeuliminen+0.1f);
	while(mopot->savuaika>=0){
	mopot->savuaika=mopot->savuaika-4.0f;
	fromsmoke(1.0f,-0.01f,true,randDouble(200,400),mopot->x2+randDouble(-10,10)-cosf(mopot->suunta)*15,randDouble(0,30),mopot->z2+randDouble(-10,10)-sinf(mopot->suunta)*15,4,randDouble(0,2*pi),0,randDouble(0,2*pi));		
	}
	
	//turning front wheel
	temp2=mopot->nopeus;
	if(temp2==0)temp2=0.01f;
	float maksimi=(0.5f)/(float)fabs(temp2*3.0f);
	if (maksimi>pi/4)maksimi=pi/4;

	//the longer it is pressed the faster it turns
	float turnrate;
	turnrate=mopot->turntime*mopot->turntime*0.666f*0.0001f;
	if(turnrate>1)turnrate=1;

	if(mopot->left)
	{
		mopot->etusuunta=mopot->etusuunta+turnrate*maksimi/0.2f/1000*elapsed*pelinopeus;		
	}
	else if(mopot->right)
	{
		mopot->etusuunta=mopot->etusuunta-turnrate*maksimi/0.2f/1000*elapsed*pelinopeus;
	}
	else
	{
		mopot->etusuunta=mopot->etusuunta-mopot->etusuunta*0.004f*elapsed*pelinopeus;
	}
	if(mopot->etusuunta<0)
	if(mopot->etusuunta<=-maksimi)mopot->etusuunta=-maksimi;
	if(mopot->etusuunta>0)
	if(mopot->etusuunta>=maksimi)mopot->etusuunta=maksimi;
	
	float liike=elapsed*pelinopeus*(mopot->nopeus);


	//fromt wheel moves
	mopot->x1=mopot->x1+(float)cos(mopot->suunta+mopot->etusuunta)*liike;
	mopot->z1=mopot->z1+(float)sin(mopot->suunta+mopot->etusuunta)*liike;
	//handbrake
	if(mopot->space){
		if(mopot->kulmakeuliminen>0)
			mopot->kulmakeuliminen=mopot->kulmakeuliminen-2*0.3f*0.001f*elapsed*pelinopeus;
		if(mopot->nopeus>0)//while braking
			mopot->nopeus=mopot->nopeus-(0.001f+sqr(mopot->nopeus)*tuulenvastus/1000)*elapsed*pelinopeus;
		else//while reverse
		mopot->nopeus=mopot->nopeus+(0.002f+sqr(mopot->nopeus)*tuulenvastus/1000)*elapsed*pelinopeus;
		//stops completely if riding slowly
		if(fabs(mopot->nopeus)<(0.002f+sqr(mopot->nopeus)*tuulenvastus/1000)*elapsed*pelinopeus)
			mopot->nopeus=0;
		else mopot->suunta=mopot->suunta+mopot->etusuunta*-0.7f;
	}
	//rear wheel moves
	mopot->x2=mopot->x2+cosf(mopot->suunta)*liike;
	mopot->z2=mopot->z2+sinf(mopot->suunta)*liike;
	//calculate direction
	mopot->suunta=atan2f(mopot->z1-mopot->z2,mopot->x1-mopot->x2);
	if (mopot->suunta<0)mopot->suunta=mopot->suunta+2*pi;
	if (mopot->suunta>2*pi)mopot->suunta=mopot->suunta-2*pi;
	if(sqrtf(sqr(mopot->z1-mopot->z2)+sqr(mopot->x1-mopot->x2))!=70)
	{
		kerroin=sqrtf(sqr(70)/(sqr(mopot->z1-mopot->z2)+sqr(mopot->x1-mopot->x2)));
		mopot->x2=(mopot->x2-mopot->x1)*kerroin+mopot->x1;
		mopot->z2=(mopot->z2-mopot->z1)*kerroin+mopot->z1;	
	}
	//roll wheels
		//how much it has moved
			float matka=sqrtf((float)sqr(cos(mopot->suunta)*elapsed*pelinopeus*mopot->nopeus)+(float)sqr(sin(mopot->suunta)*elapsed*pelinopeus*mopot->nopeus));
		
			if (mopot->nopeus<0)
			mopot->kulmaetu=mopot->kulmaetu+(matka*2*pi)/(2*pi*20);			
			else
			mopot->kulmaetu=mopot->kulmaetu-(matka*2*pi)/(2*pi*20);

	//mopot->x1=mopot->x1+mopot->nopeus*elapsed*pelinopeus;
	//front wheel front side	
	mopot->x5=mopot->x1+cosf(mopot->suunta)*70.0f;
	mopot->y5=0;
	mopot->z5=mopot->z1+sinf(mopot->suunta)*70.0f;
	//rear wheel rear side
	mopot->x6=mopot->x2-cosf(mopot->suunta)*25.0f;
	mopot->y6=0;
	mopot->z6=mopot->z2-sinf(mopot->suunta)*25.0f;

			
	mopot->suuliekki=false;
	//shooting
	if(mopot->one)
		shoot(mopot->valittuukko,-1,mopot->numero,-1,mopot,0,NULL,NULL,NULL,NULL,NULL,NULL);
	if(mopot->two)
		shoot(mopot->valittuukko,-1,mopot->numero,-1,mopot,1,NULL,NULL,NULL,NULL,NULL,NULL);
	if(mopot->three)
		shoot(mopot->valittuukko,-1,mopot->numero,-1,mopot,2,NULL,NULL,NULL,NULL,NULL,NULL);
	if(mopot->four)
		shoot(mopot->valittuukko,-1,mopot->numero,-1,mopot,3,NULL,NULL,NULL,NULL,NULL,NULL);
	

	//sectors
	mopot->sektorix=(int)mopot->x1/8000;
	mopot->sektoriz=(int)mopot->z1/8000;

	//there is a bullet under a moped
	luoti[mopot->numero].poista=false;
	luoti[mopot->numero].aseesta=5;
	luoti[mopot->numero].kenen=mopot->numero;
	luoti[mopot->numero].aika=-1;
	luoti[mopot->numero].paikka.x=mopot->x5;
	luoti[mopot->numero].paikka.y=50;
	luoti[mopot->numero].paikka.z=mopot->z5;
	luoti[mopot->numero].paikkavanha.x=mopot->x3;
	luoti[mopot->numero].paikkavanha.y=50;
	luoti[mopot->numero].paikkavanha.z=mopot->z3;


	
}

bool Render(void)
{

	m_pDevice->BeginScene();	 

	switch (pelivaihe) 
	{
	case 0:{		
		clearzbuffer();
		render_game();
		break;
		   }
	case 1:{
		
		clearzbuffer();
		render_mission();
		break;
		   }	
	case 2:{
		render_workshop();
		break;
		   }
	case 3:
		break;
	case 4:{
		clearzbuffer();
		if(keytimer>-10*elapsed)keytimer=keytimer-(int)elapsed;
		render_menu();
		break;
		   }
	}

	if(options[1]&&SOUNDS_LOADED){
		int q;
		for (q=0; q<25; q++){
			soundtimer[q]=soundtimer[q]+elapsed*pelinopeus;
		}
	}



	if(plusmiinus!=0){
		CHAR t[100];
		rendertext(10,10,0,"debug mode:");	

		ltoa(bug1,t,10);
		rendertext(10,25,0,t);

		ltoa(bug2,t,10);
		rendertext(10,40,0,t);
		
		ltoa(bug3,t,10);
		rendertext(10,55,0,t);

		ltoa((long)(plusmiinus*1000),t,10);
		rendertext(10,70,0,t);
			
		ltoa((long)(1000/elapsed),t,10);
		rendertext(10,85,0,t);	
	}

	
	
	m_pDevice->EndScene();
	return true;
}

void calculateCollisions(void)//collisions
{
	bool osuma,osuma2;
	float osumax,osumaz;
	float wallkulma;
	float temp1;
	int a,b,c,d;
	int q;
	bool osuu;
	bool turned;
	int wallhits;
	int wallhits2;
	int mapx,mapz,b2,c2;
	float kx,kz;
	
	for (d=0; d<mopoja; d++){
	if(mopot[d].pois)continue;
		osuma=false;
		osuu=false;

	mapx=mopot[d].sektorix;
	mapz=mopot[d].sektoriz;

			//}
		//}
	for (q=99; q>0; q--){
		mopot[d].osuma[q]=mopot[d].osuma[q-1];
	}
		kx=mopot[d].x3;
		kz=mopot[d].z3;
	if(fabs(mopot[d].nopeus)<1.6f){
		kx=mopot[d].x2;
		kz=mopot[d].z2;
	}

	mopot[d].osuma[0]=false;	
	//collisions with walls
	//for (a=0; a<viivagroup[0].grouppia; a++){
	a=maps[mapz][mapx];
		for (b=0; b<viivagroup[0].viivat[a].viivaa; b++){
			for (c=0; c<viivagroup[0].viivat[a].viiva[b].linjaa; c++){	
				if(linecollidesline(&osuma,&osumax,&osumaz,mopot[d].x1-mapx*8000,mopot[d].z1-mapz*8000,kx-mapx*8000,kz-mapz*8000,	viivagroup[0].viivat[a].viiva[b].piste[c].x1,viivagroup[0].viivat[a].viiva[b].piste[c].z1,viivagroup[0].viivat[a].viiva[b].piste[c].x2,viivagroup[0].viivat[a].viiva[b].piste[c].z2))				
					//||(linecollidesline(&osuma,&osumax,&osumaz,mtempx1-mapx*8000,mtempz1-mapz*8000,mtempx2-mapx*8000,mtempz2-mapz*8000,	viivagroup[0].viivat[a].viiva[b].piste[c].x1,viivagroup[0].viivat[a].viiva[b].piste[c].z1,viivagroup[0].viivat[a].viiva[b].piste[c].x2,viivagroup[0].viivat[a].viiva[b].piste[c].z2)))
				{
					//mopot[d].nopeus=-mopot[d].nopeus/3;
					
					mopot[d].osuma[0]=true;	
					//sparks
						if(mopot[d].timesparks<0){
							for (q=0; q<70; q++){							
								shoot(-6667,-1,2,randDouble(100,200),mopot,3,osumax+mapx*8000+randDouble(-20,20),50+randDouble(-20,20),osumaz+mapz*8000+randDouble(-20,20),randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
							}
						mopot[d].timesparks=mopot[d].timesparks+randDouble(100,500);
						}
					playsound(randInt(6,8),(float)fabs(mopot[d].nopeus/3.2f),mopot[d].x1,mopot[d].z1);

					mopot[d].x1=mopot[d].x3;
					mopot[d].y1=mopot[d].y3;
					mopot[d].z1=mopot[d].z3;
					mopot[d].x2=mopot[d].x4;
					mopot[d].y2=mopot[d].y4;
					mopot[d].z2=mopot[d].z4;
					
					wallkulma=atan2f(viivagroup[0].viivat[a].viiva[b].piste[c].z2-viivagroup[0].viivat[a].viiva[b].piste[c].z1,viivagroup[0].viivat[a].viiva[b].piste[c].x2-viivagroup[0].viivat[a].viiva[b].piste[c].x1);
					
					if (wallkulma<0)wallkulma=wallkulma+2*pi;
					
					//rotate wall if angle between it and moped is >90 degrees
					turned=false;
					temp1=(float)fabs(wallkulma-mopot[d].suunta);
					if(temp1>pi)temp1=2*pi-temp1;
					if(temp1>=2*pi)temp1=temp1-2*pi;
					temp1=(float)fabs(temp1);
					if(temp1>pi/2)
					{
						wallkulma=wallkulma-pi;
						turned=true;
					}

					//calculate angle between moped and wall
					temp1=(float)fabs(wallkulma-mopot[d].suunta);
					if(temp1>pi)temp1=2*pi-temp1;
					if(temp1>=2*pi)temp1=temp1-2*pi;
					temp1=(float)fabs(temp1);


					
					mopot[d].etusuunta=0;


					//to same direction as wall
					if(temp1<pi*0.47f){
						if(mopot[d].nopeus>0){
						mopot[d].x1=mopot[d].x2+(float)cos(wallkulma)*70;
						mopot[d].z1=mopot[d].z2+(float)sin(wallkulma)*70;		
						}
						else{
						mopot[d].x2=mopot[d].x1-(float)cos(wallkulma)*70;
						mopot[d].z2=mopot[d].z1-(float)sin(wallkulma)*70;
						}
						
						//re check
						for (b2=0; b2<viivagroup[0].viivat[a].viivaa; b2++){
						for (c2=0; c2<viivagroup[0].viivat[a].viiva[b2].linjaa; c2++){	
						if(linecollidesline(&osuma2,&osumax,&osumaz,mopot[d].x1-mapx*8000,mopot[d].z1-mapz*8000,kx-mapx*8000,kz-mapz*8000,	viivagroup[0].viivat[a].viiva[b2].piste[c2].x1,viivagroup[0].viivat[a].viiva[b2].piste[c2].z1,viivagroup[0].viivat[a].viiva[b2].piste[c2].x2,viivagroup[0].viivat[a].viiva[b2].piste[c2].z2))
						{
							mopot[d].x1=mopot[d].x3;
							mopot[d].y1=mopot[d].y3;
							mopot[d].z1=mopot[d].z3;
							mopot[d].x2=mopot[d].x4;
							mopot[d].y2=mopot[d].y4;
							mopot[d].z2=mopot[d].z4;
							mopot[d].nopeus=-mopot[d].nopeus/3;
							mopot[d].kulmakeuliminen=0;
						}
						}
						}
	
					}
					//backwards from wall
					else{
						mopot[d].nopeus=-mopot[d].nopeus/3;
						mopot[d].kulmakeuliminen=0;
					}

				}
				

				if(osuma)break;
			}
			if(osuma)break;
	//	}
		//if(osuma)break;
	}





	//is it inside a house
	wallhits=0;
	wallhits2=0;
	a=maps[mapz][mapx];
	for (b=0; b<viivagroup[0].viivat[a].viivaa; b++){
			for (c=0; c<viivagroup[0].viivat[a].viiva[b].linjaa; c++){	
				if(linecollidesline(&osuma,&osumax,&osumaz,mopot[d].x1-mapx*8000,mopot[d].z1-mapz*8000,mopot[d].x1-mapx*8000+80000,mopot[d].z1-mapz*8000+80000,	viivagroup[0].viivat[a].viiva[b].piste[c].x1,viivagroup[0].viivat[a].viiva[b].piste[c].z1,viivagroup[0].viivat[a].viiva[b].piste[c].x2,viivagroup[0].viivat[a].viiva[b].piste[c].z2))
					wallhits=wallhits+1;
				if(linecollidesline(&osuma,&osumax,&osumaz,mopot[d].x2-mapx*8000,mopot[d].z2-mapz*8000,mopot[d].x2-mapx*8000+80000,mopot[d].z2-mapz*8000+80000,	viivagroup[0].viivat[a].viiva[b].piste[c].x1,viivagroup[0].viivat[a].viiva[b].piste[c].z1,viivagroup[0].viivat[a].viiva[b].piste[c].x2,viivagroup[0].viivat[a].viiva[b].piste[c].z2))
					wallhits2=wallhits2+1;
			}
	}
	/*if((float)wallhits/2*1000!=((int)(wallhits/2))*1000)
	osuu=true;
	if((float)wallhits2/2*1000!=((int)(wallhits2/2))*1000)
	osuu=true;*/
	if(((float)wallhits/2*1000!=((int)(wallhits/2))*1000)&((float)wallhits2/2*1000!=((int)(wallhits2/2))*1000))
	osuu=true;


			//return old coordinates if it hits
			if(osuu){
				
					mopot[d].osuma[0]=true;

					//return coordinates
					mopot[d].x1=mopot[d].x3;
					mopot[d].y1=mopot[d].y3;
					mopot[d].z1=mopot[d].z3;
					mopot[d].x2=mopot[d].x4;
					mopot[d].y2=mopot[d].y4;
					mopot[d].z2=mopot[d].z4;
			}
	


}  
				
				
}

bool readpictures(void)
{
	DDCOLORKEY color;
	int q;
	kuvia	=	new LPDIRECTDRAWSURFACE7[numkuvia];
/*
	font1=lataakuva(m_pDD,"textures/abc.bmp",false);	
	color.dwColorSpaceHighValue=0xFFFFFF;
	color.dwColorSpaceLowValue=0xFFFFFF;
	font1->SetColorKey(DDCKEY_SRCBLT,&color);
	*/
	
	char rivi[256], temprivi[256];

	for (q=0; q<numkuvia; q++){
		
	strcpy(rivi,"textures/pic");
	itoa(q,temprivi,10);
	strcat(rivi,temprivi);
	strcat(rivi,".bmp");

	kuvia[q]=lataakuva(m_pDD, rivi,false);	
	color.dwColorSpaceHighValue=0x000000;
	color.dwColorSpaceLowValue=0x000000;
	kuvia[q]->SetColorKey(DDCKEY_SRCBLT,&color);
	}

	return true;

}

bool initkeyb(void)
{
	



	HRESULT hr;      
	// Create the DirectInput object. 
    hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, 
                           IID_IDirectInput8, (void**)&g_lpDI, NULL); 
    if FAILED(hr) return FALSE;
	
	//näpiskä //this is some weird slang word. seriously wtf, wille!?
	//keyboard,
				// Retrieve a pointer to an IDirectInputDevice7 interface 
				hr = g_lpDI->CreateDevice(GUID_SysKeyboard, 
						 &g_lpDIDevice,NULL); 
				if FAILED(hr)     
				{         
					deinitkeyb();         
					return FALSE;     
				}  
				// Now that you have an IDirectInputDevice7 interface, get 
				// it ready to use.  
				// Set the data format using the predefined keyboard data 
				// format provided by the DirectInput object for keyboards. 
				hr = g_lpDIDevice->SetDataFormat(&c_dfDIKeyboard);     
				if FAILED(hr)     
				{ 
					deinitkeyb();          
					return FALSE;     
				}  
				// Set the cooperative level 
				hr = g_lpDIDevice->SetCooperativeLevel(hWnd, 
								DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
				if FAILED(hr)     
				{         
					deinitkeyb();         
					return FALSE;     
				}  
				// Get access to the input device.     
				hr = g_lpDIDevice->Acquire(); 
				if FAILED(hr)     
				{         
					deinitkeyb();         
					return FALSE;     
				}
				


	//mouse
				hr = g_lpDI->CreateDevice(GUID_SysMouse, &g_pMouse, NULL); 
				if (FAILED(hr)) 
					{   
						deinitkeyb();
						return FALSE;
					}
				hr = g_pMouse->SetDataFormat(&c_dfDIMouse); 
				if (FAILED(hr)) 
					{   
						deinitkeyb();
						return FALSE;
					}
				hr = g_pMouse->SetCooperativeLevel(hWnd,DISCL_EXCLUSIVE | DISCL_FOREGROUND); 
				if (FAILED(hr)) 
					{
						deinitkeyb();
						return FALSE;
					}
								
				hr = g_pMouse->Acquire();
				if (FAILED(hr)) 
					{
						deinitkeyb();
						return FALSE;
					}

    return TRUE; 


}

bool deinitkeyb(void)
{

	if (g_lpDI)     
	{         
		if (g_lpDIDevice)         
		{             
		 
		//Always unacquire device before calling Release().             
			
				 g_lpDIDevice->Unacquire();
				 g_lpDIDevice->Release();
				 g_lpDIDevice = NULL;         
		}
		g_lpDI->Release();
		g_lpDI = NULL;
		
		if (g_pMouse)         
		{             
		 
		//Always unacquire device before calling Release().             
			
				 g_pMouse->Unacquire();
				 g_pMouse->Release();
				 g_pMouse = NULL;         
		}
	} 
	       
		  
	 
	return true;
}


void removeobj(obj *kohde, int indeksi)
{
	for (int a=0; a<indeksi; a++)
	{
	for (int q=0; q<kohde[a].count; q++)
	delete(kohde[a].sisus[q].loota.kolmijako);
	delete(kohde[a].sisus);
	}
	delete(kohde);
	
}

void CleanUp(void)
{

	int q;

	quittaos=true;
	deinitkeyb();

	//removing walls
	for (int c=0; c<viivagrouppia; c++){
		for (int a=0; a<viivagroup[c].grouppia; a++)
		{
			for (int b=0; b<viivagroup[c].viivat[a].viivaa; b++)
			{				
					delete(viivagroup[c].viivat[a].viiva[b].piste);
			}
			delete(viivagroup[c].viivat[a].viiva);
		}
		delete(viivagroup[c].viivat);
	}

	
	removeobj(mallit[0].malli,	objnum0	);
	removeobj(mallit[1].malli,	objnum1	);
	removeobj(mallit[2].malli,	objnum2	);
	removeobj(mallit[3].malli,	objnum3	);
	removeobj(mallit[4].malli,	objnum4	);
	removeobj(mallit[5].malli,	objnum5	);
	removeobj(mallit[6].malli,	objnum6	);
	removeobj(mallit[7].malli,	objnum7	);
	removeobj(mallit[8].malli,	objnum8	);
	removeobj(mallit[9].malli,	objnum9	);
	removeobj(mallit[10].malli,	objnum10);
	
	delete(tausta);
	//RELEASE(font1);
	for (q=0; q<numkuvia; q++)	RELEASE(kuvia[q]);

	//delete(lamppu);
	delete(mat);

	D3DXUninitialize();

	RELEASE(m_pDevice);
	RELEASE(m_pDD);	

	RELEASE(m_pD3D);
	RELEASE(taka);
	RELEASE(m_pPrimary);
	RELEASE(zpuskuri);

	if(SOUNDS_LOADED){
	for (q=0; q<SAMPLE_NUMBER; q++)
		SndObjDestroy(voices[q]);
	}
	
	if(lpDS)lpDS->Release();
}



BOOL draw(obj *tavara)
{
		
/*
	matriisi->TranslateLocal(tavara->x,tavara->y,tavara->z); //matriisi = matrix
	matriisi->RotateYawPitchRollLocal(tavara->rx,tavara->ry,tavara->rz);	
*/
	//matriisi->TranslateLocal(tavara->x,tavara->y,tavara->z);
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());
	tavara->sijainti=*matriisi->GetTop();	
	if (tavara->mirror) m_pDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_CW);
	else m_pDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_CCW);
/* 
m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
	// Set the source blend state.
m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, 
                            D3DBLEND_ONE); 
// Set the destination blend state.
m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, 
                            D3DBLEND_SRCCOLOR );
*/
	for (INT q=0; q<tavara->count; q++)
	{
		//make reflektions //if steel// (or sword)
		/*if((tavara->sisus[q].matsku==1)||(tavara->sisus[q].matsku==3))
		m_pDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,TRUE);*/
		//else
		//m_pDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,TRUE);


		//matriisi->Push();
		//matriisi->TranslateLocal(tavara->sisus[q].x,tavara->sisus[q].y,tavara->sisus[q].z);
		//matriisi->TranslateLocal(tavara->sisus[q].x,tavara->sisus[q].y,tavara->sisus[q].z);
		//m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());
		m_pDevice->SetMaterial( &mat[tavara->sisus[q].textuuri] );
		m_pDevice->SetTexture( 0, tausta[tavara->sisus[q].textuuri2] );  	
		
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
			D3DFVF_XYZ  | D3DFVF_NORMAL | D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0)//|D3DFVF_TEXCOORDSIZE1(1)  
			,(LPVOID)tavara->sisus[q].loota.kolmijako,tavara->sisus[q].loota.vert,NULL);		
		//matriisi->Pop();
	}
	//m_pDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);
	//m_pDevice->SetTexture( 0, NULL);//tarvitaanko tätä?
	return true;

}


BOOL drawfast(obj *tavara)
{
	

	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());
	//tavara->sijainti=*matriisi->GetTop();	
	//if (tavara->mirror) m_pDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_CW);
	//else m_pDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_CCW);

	for (INT q=0; q<tavara->count; q++)
	{
		//make reflektions //if steel// (or sword)
		//if((tavara->sisus[q].matsku==1)||(tavara->sisus[q].matsku==3))
		//m_pDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,TRUE);
		//else
		//m_pDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,TRUE);


		//matriisi->Push();
		//matriisi->TranslateLocal(tavara->sisus[q].x,tavara->sisus[q].y,tavara->sisus[q].z);
		if(quake>0){
			matriisi->TranslateLocal(randDouble(-quake,quake),randDouble(-quake,quake),randDouble(-quake,quake));		
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());
		}

		m_pDevice->SetMaterial( &mat[tavara->sisus[q].textuuri] );
		m_pDevice->SetTexture( 0, tausta[tavara->sisus[q].textuuri2] );  	
		
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
			D3DFVF_XYZ  | D3DFVF_NORMAL | D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0)//|D3DFVF_TEXCOORDSIZE1(1)  
			,(LPVOID)tavara->sisus[q].loota.kolmijako,tavara->sisus[q].loota.vert,NULL);		
		//matriisi->Pop();
		
		/*m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
			D3DFVF_XYZ  | D3DFVF_NORMAL | D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0)//|D3DFVF_TEXCOORDSIZE1(1)  
			,(LPVOID)tavara->sisus[q].loota.kolmijako,tavara->sisus[q].loota.vert,NULL);		*/
	}
	//m_pDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);
	//m_pDevice->SetTexture( 0, NULL);//tarvitaanko tätä?
	return true;

}

void calculatecharacters(void) //calculatecharacters
{
	int q,mapx,mapz,wallhits;
	int a,b,c;
	bool osuma;
	float osumax,osumaz;
	float cos,sin;
	float MOTION_SPEED=0.1f; 
	int poisko;
	int osumia;
	mopot[0].nearestukko=-1;
	
	for (q=0; q<ukkoja; q++)
	{		
		
		//randomize new character if one is dead
		if(ukko[q].pois){
			arvoukko(q);
		}

		for (a=99; a>0; a--){
			ukko[q].osuma[a]=ukko[q].osuma[a-1];
		}

		ukko[q].x2=ukko[q].x;
		ukko[q].z2=ukko[q].z;
		
		/*//A character will be executed if it too near to edge
		if(ukko[q].sektorix==0) ukko[q].kuole=true;
		if(ukko[q].sektorix==mapsx-1) ukko[q].kuole=true;
		if(ukko[q].sektoriz==0) ukko[q].kuole=true;
		if(ukko[q].sektoriz==mapsz-1) ukko[q].kuole=true;*/
		
		//A character will be executed if it too near to edge
		if(ukko[q].sektorix==-1) ukko[q].kuole=true;
		if(ukko[q].sektorix==mapsx) ukko[q].kuole=true;
		if(ukko[q].sektoriz==-1) ukko[q].kuole=true;
		if(ukko[q].sektoriz==mapsz) ukko[q].kuole=true;

		//legs dont swing if speed is 0
		if(ukko[q].nopeus==0){
			ukko[q].lx=0;
			ukko[q].rx=0;
		}

		/*mapx=(int)ukko[q].x/8000;
		mapz=(int)ukko[q].z/8000;
		w=maps[mapz][mapx];*/

		

		//distance from moped
		ukko[q].distanssi=sqrtf(sqr(ukko[q].x-mopot[0].x1)+sqr(ukko[q].z-mopot[0].z1));		
		
		//is it nearest
		if((ukko[q].distanssi<300)&&(ukko[q].puoli==0))
		//if(ukko[q].aseena==-1)
			if(mopot[0].nearestukko==-1)
				mopot[0].nearestukko=q;			
			else if(ukko[q].distanssi>ukko[mopot[0].nearestukko].distanssi)
				mopot[0].nearestukko=q;

		
		if(ukko[q].kuole){
			ukko[q].nopeus=0;//doesnt move if dead
			poisko=0;
			for (a=0; a<11; a++){
				if(ukko[q].ruumiinosa[a].y<-100)
					poisko=poisko+1;				
				ukko[q].ruumiinosa[a].goy=ukko[q].ruumiinosa[a].goy-elapsed*pelinopeus*0.25f/1000;				
				ukko[q].ruumiinosa[a].x=ukko[q].ruumiinosa[a].x+ukko[q].ruumiinosa[a].gox*elapsed*pelinopeus;			
				ukko[q].ruumiinosa[a].y=ukko[q].ruumiinosa[a].y+ukko[q].ruumiinosa[a].goy*elapsed*pelinopeus;
				ukko[q].ruumiinosa[a].z=ukko[q].ruumiinosa[a].z+ukko[q].ruumiinosa[a].goz*elapsed*pelinopeus;				
			}			
			if(poisko==11)ukko[q].pois=true;
		}
		if(ukko[q].distanssi<15000){
		if(ukko[q].kuole)continue;

			
		cos=cosf(ukko[q].suunta);
		sin=sinf(ukko[q].suunta);

		ukko[q].kulmamopoon=atan2f(mopot[0].z1-ukko[q].z,mopot[0].x1-ukko[q].x)+pi;


		
		/*
		matriisi->Push();q=3;//left upper arm		
		matriisi->Push();q=4;//left lower arm
		matriisi->TranslateLocal(ukko[a].ruumiinosa[q].x,ukko[a].ruumiinosa[q].y,ukko[a].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(ukko[a].ruumiinosa[q].rx,ukko[a].ruumiinosa[q].ry,ukko[a].ruumiinosa[q].rz);
				
		matriisi->Push();q=8;//rigth upper arm
		matriisi->Push();q=7;//rigth lower arm*/

			//reset arms
			ukko[q].ruumiinosa[8].rz=0;
			ukko[q].ruumiinosa[3].rz=0;
			ukko[q].ruumiinosa[7].rz=0;
			ukko[q].ruumiinosa[4].rz=0;
			

		//walks
		if(ukko[q].taktiikka==1){
			
			//arms are swinging
			ukko[q].ruumiinosa[8].rz=(ukko[q].lx*1.2f+0.24f)*ukko[q].nopeus*10;//lift upper arm (rigth)
			ukko[q].ruumiinosa[3].rz=(ukko[q].rx*1.2f+0.24f)*ukko[q].nopeus*10;//lift upper arm (left)	
			ukko[q].ruumiinosa[7].rz=(ukko[q].rx*-0.55f)*ukko[q].nopeus*10;//lift lower arm (rigth)
			ukko[q].ruumiinosa[4].rz=(ukko[q].lx*-0.55f)*ukko[q].nopeus*10;//lift lower arm (left)
			
		}

		//escapes
		if(ukko[q].taktiikka==2){
			
			//arms are swinging
			ukko[q].ruumiinosa[8].rz=(ukko[q].lx*1.2f+0.24f)*ukko[q].nopeus*10;//lift upper arm (rigth)
			ukko[q].ruumiinosa[3].rz=(ukko[q].rx*1.2f+0.24f)*ukko[q].nopeus*10;//lift upper arm (left)	
			ukko[q].ruumiinosa[7].rz=(ukko[q].rx*-0.55f)*ukko[q].nopeus*10;//lift lower arm (rigth)
			ukko[q].ruumiinosa[4].rz=(ukko[q].lx*-0.55f)*ukko[q].nopeus*10;//lift lower arm (left)
			
			ukko[q].suunta=ukko[q].kulmamopoon;
			if(ukko[q].distanssi<1000)ukko[q].nopeus=0.2f;
		}

		//attack
		if(ukko[q].taktiikka==0){
			ukko[q].menoajastin=ukko[q].menoajastin-elapsed*pelinopeus;
			if(ukko[q].distanssi<5000)
			{
				ukko[q].suunta=atan2f(mopot[0].z1-sinf(mopot[0].suunta)*randDouble(30,mopot[0].nopeus*30+30)-ukko[q].z,mopot[0].x1-cosf(mopot[0].suunta)*randDouble(30,mopot[0].nopeus*30+30)-ukko[q].x);
				ukko[q].ruumiinosa[8].rz=1.5f;
				ukko[q].ruumiinosa[3].rz=1.5f;
				ukko[q].ruumiinosa[8].rx=0.4f;
				ukko[q].ruumiinosa[3].rx=-0.4f;
				//doesnt go too close
				if(ukko[q].distanssi<200) ukko[q].nopeus=0.0f;
				if(ukko[q].distanssi>800) ukko[q].nopeus=0.2f;

			}

			if(ukko[q].menoajastin<0)
			{
				ukko[q].menoajastin=ukko[q].menoajastin+2000;
				ukko[q].menossa=1;
				
				if(ukko[q].distanssi<1000){					
					if(randInt(0,2)==0)
					ukko[q].menossa=-1;
				}
			}
			if(ukko[q].distanssi<200){
				ukko[q].menoajastin=2000;
				ukko[q].menossa=-1;
			}

			if(ukko[q].menossa==1)
				ukko[q].nopeus=0.2f;
			if(ukko[q].menossa==-1)
				ukko[q].nopeus=-0.2f;

			//character shoots
			if(ukko[q].asetime<0)ukko[q].asetime=ukko[q].asetime+elapsed*pelinopeus;
			//if((ukko[q].distanssi<1000)|(randInt(0,(int)(elapsed*pelinopeus*300))==0)){
			if(randInt(0,(int)(elapsed*pelinopeus*ukko[q].distanssi*ukko[q].distanssi*ase[ukko[q].aseena].ampumanopeus*0.02f*0.000001f+1))<=1){
				if(ukko[q].kuole!=true)
					if(ukko[q].aseena!=-1){					
						while(ukko[q].asetime>=0){
							ukko[q].asetime=ukko[q].asetime-ase[ukko[q].aseena].ampumanopeus;				
							shoot(-1,q,-1,-1,mopot,ukko[q].aseena,ukko[q].x+cos*33,92*ukko[q].korkeus,ukko[q].z+sin*33,-ukko[q].suunta,randDouble(-0.03f,0.03f),randDouble(-0.03f,0.03f));
							//shoot(q,2,-1,mopot,ukko[q].aseena,ukko[q].x+cos*33,85,ukko[q].z+sin*33,-ukko[q].suunta,0,0); //shoot
						}
					}
			}
		}



		ukko[q].sektorix=(int)ukko[q].x/8000;
		ukko[q].sektoriz=(int)ukko[q].z/8000;
		ukko[q].jaosx=(int)ukko[q].x/800;
		ukko[q].jaosz=(int)ukko[q].z/800;


		//move forward
		if((ukko[q].nopeus!=0))//||(ukko[q].kulku==-1))
		{
					
	ukko[q].ruumiinosa[9].rz=(ukko[q].rx*1.2f+0.24f)*ukko[q].nopeus*10;//lift upper leg (rigth)
	ukko[q].ruumiinosa[5].rz=(ukko[q].lx*1.2f+0.24f)*ukko[q].nopeus*10;//lift upper leg (left)	
	ukko[q].ruumiinosa[10].rz=(ukko[q].rx*-0.2f-0.15f)*ukko[q].nopeus*10;//lift lower leg (rigth)
	ukko[q].ruumiinosa[6].rz=(ukko[q].lx*-0.2f-0.15f)*ukko[q].nopeus*10;//lift lower leg (left)


			

			//does it collide with walls
			mapx=ukko[q].sektorix;
			mapz=ukko[q].sektoriz;
			a=maps[mapz][mapx];
			wallhits=0;
			for (b=0; b<viivagroup[0].viivat[a].viivaa; b++){
					for (c=0; c<viivagroup[0].viivat[a].viiva[b].linjaa; c++){	
						if(linecollidesline(&osuma,&osumax,&osumaz,ukko[q].x+cos*100*ukko[q].menossa-mapx*8000,ukko[q].z+sin*100*ukko[q].menossa-mapz*8000,ukko[q].x+cos*100*ukko[q].menossa+8000-mapx*8000,ukko[q].z+sin*100*ukko[q].menossa-mapz*8000,	viivagroup[0].viivat[a].viiva[b].piste[c].x1,viivagroup[0].viivat[a].viiva[b].piste[c].z1,viivagroup[0].viivat[a].viiva[b].piste[c].x2,viivagroup[0].viivat[a].viiva[b].piste[c].z2))
							wallhits=wallhits+1;
					}
			}
			ukko[q].osuma[0]=false;
			if((float)wallhits/2*1000!=((int)(wallhits/2))*1000){
			ukko[q].rx=0;
			ukko[q].lx=0;
			ukko[q].ruumiinosa[9].rz=0;
			ukko[q].ruumiinosa[5].rz=0;
			ukko[q].ruumiinosa[10].rz=0;
			ukko[q].ruumiinosa[6].rz=0;
			ukko[q].nopeus=0;
			ukko[q].x=ukko[q].x2;
			ukko[q].z=ukko[q].z2;
			ukko[q].osuma[0]=true;
			}
			

		
			//legs are swingin
			if(ukko[q].nopeus!=0){
					if (ukko[q].jalka){									
										ukko[q].lx=ukko[q].lx-MOTION_SPEED*0.015f*elapsed*pelinopeus;
										if (ukko[q].lx<-0.6f) 
										{ukko[q].jalka=false;
										/*q=randInt(0,3);
										if(q==1)svolume(voices[14+q],(int)-distanssi ,SOUNDS_ON);
										else svolume(voices[14+q],0 ,SOUNDS_ON);
										SndObjPlay(voices[14+q], NULL,SOUNDS_ON);*/
										}
					if (ukko[q].rx<= 0.20f)	ukko[q].rx=ukko[q].rx+MOTION_SPEED*0.015f*elapsed*pelinopeus;
					}

					else{
										ukko[q].rx=ukko[q].rx-MOTION_SPEED*0.015f*elapsed*pelinopeus;
										if (ukko[q].rx<-0.6f)	
										{ukko[q].jalka=true;
										/*q=randInt(0,3);
										if(q==1)svolume(voices[14+q],(int)-distanssi ,SOUNDS_ON);
										else svolume(voices[14+q],0 ,SOUNDS_ON);
										SndObjPlay(voices[14+q], NULL,SOUNDS_ON);*/
										}
					if (ukko[q].lx<= 0.20f)	ukko[q].lx=ukko[q].lx+MOTION_SPEED*0.015f*elapsed*pelinopeus;
					}
			}
					
					/*if (distanssi<100) ukko[q].kulku=-1;//is not allowed to go too close	

					ukko[q].ux=ukko[q].ux+(float)cos(ukko[q].kulma)*elapsed*pelinopeus*UKON_NOPEUS*ukko[q].kulku;
					ukko[q].uz=ukko[q].uz+(float)sin(ukko[q].kulma)*elapsed*pelinopeus*UKON_NOPEUS*ukko[q].kulku;
					*/
					
					ukko[q].x=ukko[q].x+cos*ukko[q].nopeus*elapsed*pelinopeus;
					ukko[q].z=ukko[q].z+sin*ukko[q].nopeus*elapsed*pelinopeus;
		}
		if(ukko[q].nopeus==0)
		{
					
					
					BOOL eteen=false;
					if(ukko[q].jalka) if (ukko[q].lx< 0.10f)	{ukko[q].lx=ukko[q].lx+MOTION_SPEED*0.02f*elapsed*pelinopeus;eteen=true;}
					if(!ukko[q].jalka) if (ukko[q].rx< 0.10f)	{ukko[q].rx=ukko[q].rx+MOTION_SPEED*0.02f*elapsed*pelinopeus;eteen=true;}

					//deciding new direction
					if((ukko[q].taktiikka!=0)&&(!ukko[q].visible)){
						ukko[q].suunta=randDouble(-pi,pi);
							//does it collide with walls
							cos=cosf(ukko[q].suunta);
							sin=sinf(ukko[q].suunta);
							mapx=ukko[q].sektorix;
							mapz=ukko[q].sektoriz;
							a=maps[mapz][mapx];
							wallhits=0;
							for (b=0; b<viivagroup[0].viivat[a].viivaa; b++){
									for (c=0; c<viivagroup[0].viivat[a].viiva[b].linjaa; c++){	
										if(linecollidesline(&osuma,&osumax,&osumaz,ukko[q].x+cos*100-mapx*8000,ukko[q].z+sin*100-mapz*8000,ukko[q].x+cos*100+8000-mapx*8000,ukko[q].z+sin*100-mapz*8000,	viivagroup[0].viivat[a].viiva[b].piste[c].x1,viivagroup[0].viivat[a].viiva[b].piste[c].z1,viivagroup[0].viivat[a].viiva[b].piste[c].x2,viivagroup[0].viivat[a].viiva[b].piste[c].z2))
											wallhits=wallhits+1;
									}
							}
							if((float)wallhits/2*1000==((int)(wallhits/2))*1000){
								ukko[q].nopeus=randDouble(0.05f,0.1f);
							}
					}
					/*
					if (eteen)
					{
					ukko[q].ux=ukko[q].ux+(float)cos(ukko[q].kulma)*elapsed*pelinopeus*UKON_NOPEUS*ukko[q].edkulku;
					ukko[q].uz=ukko[q].uz+(float)sin(ukko[q].kulma)*elapsed*pelinopeus*UKON_NOPEUS*ukko[q].edkulku;
					}
					*/
		}

	}
		
		osumia=0;
		//if can get out of the wall
		for (a=0; a<100; a++){
			if(ukko[q].osuma[a])
			osumia=osumia+1;
		}
		if((osumia>40)&&(ukko[q].visible==false)){	
				for (a=0; a<100; a++){
					ukko[q].osuma[a]=false;
				}

				laskekoordinaatit(&ukko[q].x,&ukko[q].z);
		}

		

		
	}

	}

void rendercharacters(void){
	int q,a,d;
	
	
	

	//rendering humans -characters (ukko)
	
	for (q=0; q<ukkoja; q++)
	{
		if(ukko[q].pois)continue;
		radiusukko[q]=50.01f;	
		keskipisteukko[q].x=ukko[q].x;
		keskipisteukko[q].y=50;
		keskipisteukko[q].z=ukko[q].z;
	}
	

	matriisi->LoadIdentity();
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());		
	m_pDevice->ComputeSphereVisibility(keskipisteukko,radiusukko,ukkoja,0,visibleukko);//remember SetTransform
	


	int kuvaaja;
	
	for (a=0; a<ukkoja; a++)
	{
	if(ukko[a].pois)continue;
		ukko[a].visible=true;
	if((visibleukko[a] &D3DSTATUS_CLIPINTERSECTIONALL   ) ){ukko[a].visible=false; continue;}
	
	
	if(ukko[a].distanssi>8000)continue;//no point to render if too far away

	//if(ukko[a].distanssi>2000)
	if(ukko[a].distanssi>2000)
	kuvaaja=4;
	else kuvaaja=ukko[a].kuva;
	if(ukko[a].kuole)kuvaaja=5;

	
	//from farther away all characters look ugly
	if(!mapmode){ 
		if(ukko[a].distanssi>3100)continue;
		kuvaaja=4;
	}

	//selecting textures
	switch (ukko[a].kuva) 
			{
			case 3:{
				d=0;
				break;
				   }
			/*case 5:{
				d=1;
				break;
				   }*/
			case 7:{
				d=2;
				break;
				   }
			case 8:{
				d=3;
				break;
				   }			
			case 10:{
				d=4;
				break;
				   }
			}	
	if(kuvaaja==5)d=1;

/*
	ukkotekstuuri[d].osa[0]=10;//torso
	ukkotekstuuri[d].osa[1]=11;//legs
	ukkotekstuuri[d].osa[2]=12;//arm
	ukkotekstuuri[d].osa[3]=14;//face
*/
11
		//5;left upper leg
		//6;left lower leg
		//9;right upper leg
		//10;right lower leg

	

	
	if(!ukko[a].kuole)		
		{
			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
			m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE    );
			m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_SRCALPHA    );	

			
			//render mission mark
			if(mopot[0].mission.suoritettu!=0)
			if(mopot[0].nearestukko==a)	
			if(ukko[mopot[0].nearestukko].puoli==0)
			//if(!ukko[mopot[0].nearestukko].kuole)
				if(fabs(mopot[0].nopeus)<0.7f){
					matriisi->LoadIdentity();		
					matriisi->TranslateLocal(ukko[a].x,1,ukko[a].z);					
					matriisi->RotateYawPitchRollLocal(0,0,pi/2);				
					drawfast(&mallit[2].malli[6]);				
				}
					
		

			//render balls if viewed from above
			if(!mapmode){
				matriisi->LoadIdentity();		
				matriisi->TranslateLocal(ukko[a].x,1,ukko[a].z);
				matriisi->RotateYawPitchRollLocal(0,0,pi/2);
				if(ukko[a].puoli==0)drawfast(&mallit[2].malli[13]);
				if(ukko[a].puoli==1)drawfast(&mallit[2].malli[11]);
				if(ukko[a].puoli==2)drawfast(&mallit[2].malli[14]);
			}
			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);

	}

		matriisi->LoadIdentity();		
		matriisi->TranslateLocal(ukko[a].x,57*ukko[a].korkeus+(float)fabs(ukko[a].rx)*2*ukko[a].nopeus*18,ukko[a].z);
		matriisi->RotateYawPitchRollLocal(-ukko[a].suunta,0,0);	
		matriisi->ScaleLocal(ukko[a].korkeus,ukko[a].korkeus,ukko[a].korkeus);


		matriisi->Push();q=0;//ass			
		matriisi->TranslateLocal(ukko[a].ruumiinosa[q].x,ukko[a].ruumiinosa[q].y,ukko[a].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(ukko[a].ruumiinosa[q].rx,ukko[a].ruumiinosa[q].ry,ukko[a].ruumiinosa[q].rz);
		mallit[kuvaaja].malli[q].sisus[0].textuuri2=ukkotekstuuri[d].osa[1];
		drawfast(&mallit[kuvaaja].malli[q]);
		matriisi->Pop();

		matriisi->Push();q=2;//head
		matriisi->TranslateLocal(ukko[a].ruumiinosa[q].x,ukko[a].ruumiinosa[q].y,ukko[a].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(ukko[a].ruumiinosa[q].rx,ukko[a].ruumiinosa[q].ry,ukko[a].ruumiinosa[q].rz);
		mallit[kuvaaja].malli[q].sisus[0].textuuri2=ukkotekstuuri[d].osa[3];
		drawfast(&mallit[kuvaaja].malli[q]);
		matriisi->Pop();

		matriisi->Push();q=1;//torso
		matriisi->TranslateLocal(ukko[a].ruumiinosa[q].x,ukko[a].ruumiinosa[q].y,ukko[a].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(ukko[a].ruumiinosa[q].rx,ukko[a].ruumiinosa[q].ry,ukko[a].ruumiinosa[q].rz);
		mallit[kuvaaja].malli[q].sisus[0].textuuri2=ukkotekstuuri[d].osa[0];
		drawfast(&mallit[kuvaaja].malli[q]);

		matriisi->Push();q=3;//left upper arm
		matriisi->TranslateLocal(ukko[a].ruumiinosa[q].x,ukko[a].ruumiinosa[q].y,ukko[a].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(ukko[a].ruumiinosa[q].rx,ukko[a].ruumiinosa[q].ry,ukko[a].ruumiinosa[q].rz);
		mallit[kuvaaja].malli[q].sisus[0].textuuri2=ukkotekstuuri[d].osa[2];
		drawfast(&mallit[kuvaaja].malli[q]);

		matriisi->Push();q=4;//left lower arm
		matriisi->TranslateLocal(ukko[a].ruumiinosa[q].x,ukko[a].ruumiinosa[q].y,ukko[a].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(ukko[a].ruumiinosa[q].rx,ukko[a].ruumiinosa[q].ry,ukko[a].ruumiinosa[q].rz);
		mallit[kuvaaja].malli[q].sisus[0].textuuri2=ukkotekstuuri[d].osa[2];
		drawfast(&mallit[kuvaaja].malli[q]);

		matriisi->Pop();
		matriisi->Pop();
		matriisi->Pop();
		
		matriisi->Push();q=8;//right upper arm
		matriisi->TranslateLocal(ukko[a].ruumiinosa[q].x,ukko[a].ruumiinosa[q].y,ukko[a].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(ukko[a].ruumiinosa[q].rx,ukko[a].ruumiinosa[q].ry,ukko[a].ruumiinosa[q].rz);
		mallit[kuvaaja].malli[q].sisus[0].textuuri2=ukkotekstuuri[d].osa[2];
		drawfast(&mallit[kuvaaja].malli[q]);

		matriisi->Push();q=7;//right lower arm
		matriisi->TranslateLocal(ukko[a].ruumiinosa[q].x,ukko[a].ruumiinosa[q].y,ukko[a].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(ukko[a].ruumiinosa[q].rx,ukko[a].ruumiinosa[q].ry,ukko[a].ruumiinosa[q].rz);
		mallit[kuvaaja].malli[q].sisus[0].textuuri2=ukkotekstuuri[d].osa[2];
		drawfast(&mallit[kuvaaja].malli[q]);		
		

		matriisi->Pop();
		matriisi->Pop();


		//attackers have a gun
		if(!ukko[a].kuole)
		if(ukko[a].taktiikka==0){
			matriisi->Push();
			matriisi->TranslateLocal(30,30,0);
			//matriisi->RotateYawPitchRollLocal(ukko[a].ruumiinosa[q].rx,ukko[a].ruumiinosa[q].ry,ukko[a].ruumiinosa[q].rz);			
			drawfast(&mallit[2].malli[12]);
			matriisi->Pop();
		}


		matriisi->Push();q=5;//left upper leg
		matriisi->TranslateLocal(ukko[a].ruumiinosa[q].x,ukko[a].ruumiinosa[q].y,ukko[a].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(ukko[a].ruumiinosa[q].rx,ukko[a].ruumiinosa[q].ry,ukko[a].ruumiinosa[q].rz);
		mallit[kuvaaja].malli[q].sisus[0].textuuri2=ukkotekstuuri[d].osa[1];
		drawfast(&mallit[kuvaaja].malli[q]);		

		matriisi->Push();q=6;//left lower leg
		matriisi->TranslateLocal(ukko[a].ruumiinosa[q].x,ukko[a].ruumiinosa[q].y,ukko[a].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(ukko[a].ruumiinosa[q].rx,ukko[a].ruumiinosa[q].ry,ukko[a].ruumiinosa[q].rz);
		mallit[kuvaaja].malli[q].sisus[0].textuuri2=ukkotekstuuri[d].osa[1];
		drawfast(&mallit[kuvaaja].malli[q]);
		matriisi->Pop();
		matriisi->Pop();

		matriisi->Push();q=9;//rigth upper leg
		matriisi->TranslateLocal(ukko[a].ruumiinosa[q].x,ukko[a].ruumiinosa[q].y,ukko[a].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(ukko[a].ruumiinosa[q].rx,ukko[a].ruumiinosa[q].ry,ukko[a].ruumiinosa[q].rz);
		mallit[kuvaaja].malli[q].sisus[0].textuuri2=ukkotekstuuri[d].osa[1];
		drawfast(&mallit[kuvaaja].malli[q]);


		matriisi->Push();q=10;//right lower leg
		matriisi->TranslateLocal(ukko[a].ruumiinosa[q].x,ukko[a].ruumiinosa[q].y,ukko[a].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(ukko[a].ruumiinosa[q].rx,ukko[a].ruumiinosa[q].ry,ukko[a].ruumiinosa[q].rz);
		mallit[kuvaaja].malli[q].sisus[0].textuuri2=ukkotekstuuri[d].osa[1];
		drawfast(&mallit[kuvaaja].malli[q]);
		matriisi->Pop();
		matriisi->Pop();

	}
}

//font means after ammount of letters text is cut to lines
//void rendertext(INT x, INT y, INT fontti,CHAR teksti[100],LPDIRECTDRAWSURFACE7 pinta,LPDIRECTDRAWSURFACE7 font1)
void rendertext(INT x, INT y, INT fontti,CHAR teksti[100]) //write
{
	//RECT loota; //boxxy
	INT nume;
	int xplus=0;
	int yplus=0;
	float korkeus,leveys;
	float u1,u2,v1,v2;
	int xk,yk;
	bool iso;
	BOOL lightenabled[2];
	//for (int i=0; i<4; i++)
			m_pDevice->SetMaterial( &mat[47] );			
			matriisi->LoadIdentity();
			m_pDevice->GetLightEnable(0,  &lightenabled[0]); 
			m_pDevice->GetLightEnable(1,  &lightenabled[1]); 
			m_pDevice->LightEnable(0, FALSE);
			m_pDevice->LightEnable(1, FALSE);
			m_pDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xFFFFFFFF);
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());		 
			m_pDevice->SetRenderState( D3DRENDERSTATE_ZBIAS, 0);
			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
			/*m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE    );
			m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE    );	*/
			m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE); 
			m_Projection = ProjectionMatrix(25.0f, maxvisible, (float)(80*pi/180)); // 60 visionfield
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);
			

	for (int i=0; i<abs((int)strlen(teksti)); i++)
	//for (int i=0; i<4; i++)
	{


	nume=0;
//		teksti[i]=*CharLower(&teksti[i]);
        //kirj:=LowerCase(kirj);
        //if kirj= #32 then exit;
	iso=false;
		switch (teksti[i]) 
		{
			case ' ':{nume=-1;goto te;}
			case 'a':{nume=0;goto fa;}
			case 'b':{nume=1;goto fa;}
			case 'c':{nume=2;goto fa;}
			case 'd':{nume=3;goto fa;}
			case 'e':{nume=4;goto fa;}
			case 'f':{nume=5;goto fa;}
			case 'g':{nume=6;goto fa;}
			case 'h':{nume=7;goto fa;}
			case 'i':{nume=8;goto fa;}
			case 'j':{nume=9;goto fa;}
			case 'k':{nume=10;goto fa;}
			case 'l':{nume=11;goto fa;}
			case 'm':{nume=12;goto fa;}
			case 'n':{nume=13;goto fa;}
			case 'o':{nume=14;goto fa;}
			case 'p':{nume=15;goto fa;}
			case 'q':{nume=16;goto fa;}
			case 'r':{nume=17;goto fa;}
			case 's':{nume=18;goto fa;}
			case 't':{nume=19;goto fa;}
			case 'u':{nume=20;goto fa;}
			case 'v':{nume=21;goto fa;}
			case 'w':{nume=22;goto fa;}
			case 'x':{nume=23;goto fa;}
			case 'y':{nume=24;goto fa;}
			case 'z':{nume=25;goto fa;}
			case 'å':{nume=26;goto fa;}
			case 'ä':{nume=27;goto fa;}
			case 'ö':{nume=28;goto fa;}
			case '1':{nume=29;goto fa;}
			case '2':{nume=30;goto fa;}
			case '3':{nume=31;goto fa;}
			case '4':{nume=32;goto fa;}
			case '5':{nume=33;goto fa;}
			case '6':{nume=34;goto fa;}
			case '7':{nume=35;goto fa;}
			case '8':{nume=36;goto fa;}
			case '9':{nume=37;goto fa;}
			case '-':{nume=38;goto fa;}
			case '0':{nume=39;goto fa;}
			case '.':{nume=40;goto fa;}
			case '/':{nume=41;goto fa;}
			case ':':{nume=42;goto fa;}
			case '´':{nume=43;goto fa;}
			case '?':{nume=44;goto fa;}
			case ',':{nume=45;goto fa;}
			case '!':{nume=46;goto fa;}

			case 'A':{nume=0;goto fr;}
			case 'B':{nume=1;goto fr;}
			case 'C':{nume=2;goto fr;}
			case 'D':{nume=3;goto fr;}
			case 'E':{nume=4;goto fr;}
			case 'F':{nume=5;goto fr;}
			case 'G':{nume=6;goto fr;}
			case 'H':{nume=7;goto fr;}
			case 'I':{nume=8;goto fr;}
			case 'J':{nume=9;goto fr;}
			case 'K':{nume=10;goto fr;}
			case 'L':{nume=11;goto fr;}
			case 'M':{nume=12;goto fr;}
			case 'N':{nume=13;goto fr;}
			case 'O':{nume=14;goto fr;}
			case 'P':{nume=15;goto fr;}
			case 'Q':{nume=16;goto fr;}
			case 'R':{nume=17;goto fr;}
			case 'S':{nume=18;goto fr;}
			case 'T':{nume=19;goto fr;}
			case 'U':{nume=20;goto fr;}
			case 'V':{nume=21;goto fr;}
			case 'W':{nume=22;goto fr;}
			case 'X':{nume=23;goto fr;}
			case 'Y':{nume=24;goto fr;}
			case 'Z':{nume=25;goto fr;}
			case 'Å':{nume=26;goto fr;}
			case 'Ä':{nume=27;goto fr;}
			case 'Ö':{nume=28;goto fr;}
		}

fr:
		iso=true;
fa:

		//if(nume>-1){//if there is no space
			{
		
		pvertex vertex[6];
		korkeus=70;
		leveys=60;
		yk=(int)(nume/8);
		xk=nume-yk*8;
		u1=(xk*16)/128.0f;
		u2=(xk*16+16)/128.0f;
		v1=(yk*18)/128.0f;
		v2=(yk*18+18)/128.0f;

			vertex[0].position.x=0;
			vertex[0].position.y=0;
			vertex[0].position.z=0;
			vertex[0].u=u2;
			vertex[0].v=v2;

			vertex[1].position.x=leveys;
			vertex[1].position.y=korkeus;
			vertex[1].position.z=0;
			vertex[1].u=u1;
			vertex[1].v=v1;

			vertex[2].position.x=0;
			vertex[2].position.y=korkeus;
			vertex[2].position.z=0;
			vertex[2].u=u2;
			vertex[2].v=v1;

			vertex[3].position.x=0;
			vertex[3].position.y=0;
			vertex[3].position.z=0;
			vertex[3].u=u2;
			vertex[3].v=v2;

			vertex[4].position.x=leveys;
			vertex[4].position.y=0;
			vertex[4].position.z=0;
			vertex[4].u=u1;
			vertex[4].v=v2;

			vertex[5].position.x=leveys;
			vertex[5].position.y=korkeus;
			vertex[5].position.z=0;
			vertex[5].u=u1;
			vertex[5].v=v1;
		
			

			if(iso)m_pDevice->SetTexture( 0, tausta[47] );			
			else m_pDevice->SetTexture( 0, tausta[64] );

			//m_pDevice->SetTexture( 0, tausta[65] );
			
			//set camera to its place
			kamerax1=(x+xplus*(12.5f)-1024/2)*(3.28f)+42;
			kameray1=(y+yplus*(15.17f)-768/2)*(3.28f)+46;
			kameraz1=2000;
			kamerax2=kamerax1+3.7f;
			kameray2=kameray1+3.7f;
			kameraz2=0;
			m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);				
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);
			
			
			m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ZERO    );
			m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,	D3DBLEND_INVSRCCOLOR);	
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
				D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,vertex,6,NULL);

			//set camera to its place
			kamerax1=(x+xplus*(12.5f)-1024/2)*(3.28f)+42;
			kameray1=(y+yplus*(15.17f)-768/2)*(3.28f)+46;
			kameraz1=2000;
			kamerax2=kamerax1;
			kameray2=kameray1;
			kameraz2=0;
			m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);				
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);

			
			m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE    );
			m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE    );	
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
				D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,vertex,6,NULL);
			

/*
		loota.left  =nume*13+1;
		loota.right =loota.left+12;
		loota.top   =1;
		loota.bottom=14;
		
		int textheight=13;
		pinta->BltFast(x+xplus*11, y+yplus*textheight,
        font1,
        &loota,
        DDBLTFAST_SRCCOLORKEY );
*/
		
		
		}
te:
		xplus=xplus+1;

		//cutting it to lines
		if(fontti>0)
		if((xplus>fontti)&&(nume==-1)){xplus=0;yplus=yplus+1;}
	
	
	
}
			m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE); 
			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
			m_pDevice->LightEnable(0, lightenabled[0]);
			m_pDevice->LightEnable(1, lightenabled[1]);

}


void render_game(void){//just renders some moped driving.
	
	int a,b,q,c,d;	
	float kerroin;
	char rivi[200];
	char temprivi[200];
	//pelivaihe2 		//gamephase2
	//0=normaali peli 	//normal game
	//1=loppudemo 		//end demo
	//2=paussi 		// pause
	//3=alkudemo 		//beginning demo
	//4=alkudemo 		//beginning demo
	//5=kuolema 		//death
	ase[2].tyyppi=4;
	ase[3].tyyppi=4;
	ase[4].tyyppi=4;
	

	if(quake>7)quake=7;
	if(quake>0)quake=quake-0.03f*elapsed*pelinopeus;//earthquake
	
	if(pelivaihe2==0){
		calculateCollisions();//does mopeds collide with anything
		laskemopot();//mopeds are rollin //calculatemopeds
		for (d=0; d<mopoja; d++){
			if(mopot[d].pois)continue;
			aja(&mopot[d]);	
		}
	}

	
	//engine is roaring
	int hertsi=(int)(1.66f*10000*(fabs(mopot->nopeus)+2.5f))+randInt(-3000,3000);
	if(hertsi<100)hertsi=100;
	if(hertsi>100000)hertsi=100000;	
	if(options[1]&&SOUNDS_LOADED)
		SndObjSetFrequency(voices[1],hertsi);
	//SndObjPlay(voices[1], DSBPLAY_LOOPING,options[1]&&SOUNDS_LOADED);		


	//normal vision angle
	if(mapmode){
		//background is grey ; it is not needed if sky is renderet separetly
		m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x004C4C4C, 0, 0 );
		kerroin=1.0f;
			float kameranopeus;
			float fSinXY,fSinXZ,fCosXZ,ero;
			float xcam=mopot[0].x1;
			float zcam=mopot[0].z1;
			kameranopeus=0.006f;
			if(mapmode2!=mapmode)kameranopeus=1/elapsed;
				dx2=mopot[0].suunta*180/pi-180;
				fSinXY = sinf((dy/180*pi));
				fSinXZ = sinf(((dx+dx2)/180*pi));
				fCosXZ = cosf(((dx+dx2)/180*pi));
				ero=camx-(xcam + (fCosXZ - (float)fabs(fSinXY) * fCosXZ) * 200);
				camx = camx-ero*elapsed*kameranopeus;
				ero=camy-(90 + fSinXY * 300);//ero=camy-(ukko[0].uy + fSinXY * 500);
				camy = camy-ero*elapsed*kameranopeus;
				ero=camz-(zcam + (fSinXZ - (float)fabs(fSinXY) * fSinXZ) * 200);
				camz = camz-ero*elapsed*kameranopeus;

				if(sqrtf(sqr(mopot[0].x1-camx)+sqr(mopot[0].z1-camz))<250){
					float kerroin=sqrtf(sqr(250)/(sqr(mopot[0].z1-camz)+sqr(mopot[0].x1-camx)));
					camz=(camz-mopot[0].z1)*kerroin+mopot[0].z1;
					camx=(camx-mopot[0].x1)*kerroin+mopot[0].x1;
					//mopot->x2=(mopot->x2-mopot->x1)*kerroin+mopot->x1;

				}
	
	kamerax1=camx+1;
	kameray1=camy;
	kameraz1=camz+1;

	kamerax2=mopot[0].x1;
	kameray2=100;
	kameraz2=mopot[0].z1;

	m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);	
	//m_Projection = ProjectionMatrix(25.0f, maxvisible, (float)(80*pi/180)); // 60 vision field
	m_Projection = ProjectionMatrix(25.0f, maxvisible, (float)((80-mopot[0].nopeus*0.4f)*pi/180));
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);


//SetupVertexFog(0,200,0x004C4C4C, D3DFOG_LINEAR  , TRUE, 0);//fog	
		/*	//sky
			m_pDevice->LightEnable(0, FALSE);
			m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,FALSE);
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(camx,camy+20,camz);			
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());
			//m_View = ViewMatrix(D3DVECTOR(680,0,0), D3DVECTOR(0,0,0), D3DVECTOR(0,1,0), 0);
			//m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);			
			drawfast(&mallit[2].malli[11]);
			m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,TRUE);
			m_pDevice->LightEnable(0, TRUE);
*/
//SetupVertexFog(maxvisible-5000,maxvisible,0x004C4C4C, D3DFOG_LINEAR  , TRUE, 0);//sumu



	}


	//vision from above
	if(!mapmode){
	kerroin=0.45f;
	kamerax1=mopot[0].x1+100;
	kameray1=10000;
	kameraz1=mopot[0].z1;

	kamerax2=mopot[0].x1+cosf(mopot[0].suunta)*1.5f;
	kameray2=0;
	kameraz2=mopot[0].z1+sinf(mopot[0].suunta)*1.5f;

	m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);	
	m_Projection = ProjectionMatrix(4000, 11000, (float)(30*pi/180)); // 60 vision field	
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);	
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);
	}
		
	luoteja=0;
	if(pelivaihe2==0){
		svolume(voices[1],DSBVOLUME_MAX, options[1]&&SOUNDS_LOADED);
		calculatecharacters();
		calculatebullets();
		calculatebullets();
		laskemissiot(&mopot[0]);
	}

	

	//is character dead
	if((mopot[0].energia<0)&&(pelivaihe2!=5)){
		pelivaihe2=5;
		//mopot[0].pois=true;
					
		SndObjStop(voices[1]);//motor stops
					//smoke to air
					if(ase[1].savumaahan!=0)
						for (q=0; q<3; q++){	
							fromsmoke(1.0f,0.001f,true,3000,mopot[0].x1,60,mopot[0].z1,ase[1].savumaahan,randDouble(pi,-pi),randDouble(pi,-pi),randDouble(pi,-pi));
						}
					//explosion
					if(ase[1].pommi!=0){
						quake=3;
						for (q=0; q<100; q++){
						shoot(-6667,-1,1,randDouble(100,300),mopot,2,mopot[0].x1,60,mopot[0].z1,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
						}
							fromsmoke(1.0f,0.01f,true,3000,mopot[0].x1,60,mopot[0].z1,3,0,0,0);													
						playsound(8,1,mopot[0].x1,mopot[0].z1);
					}


	}

		
	//is the character at workshop
	if(maps[mopot[0].sektoriz][mopot[0].sektorix]==6){

		float mopox=mopot[0].x1-mopot[0].sektorix*8000;
		float mopoz=mopot[0].z1-mopot[0].sektoriz*8000;

		mopot[0].korjaamolla2=mopot[0].korjaamolla;
		
		//it is at workshop area
		mopot[0].korjaamolla=false;
		if((mopox>4834)&(mopox<5065)&(mopoz<6700)&(mopoz>6300))
			mopot[0].korjaamolla=true;

		if((mopot[0].korjaamolla==true)&(mopot[0].korjaamolla2==false)){
			SndObjStop(voices[1]);
			pelivaihe=2;
			korjaussumma=0;
			mopot[0].suunta=pi/2;
			mopot[0].x1=(float)(mopot[0].sektorix*8000+4950);
			mopot[0].z1=(float)(mopot[0].sektoriz*8000+6500);
			mopot[0].x2=mopot[0].x1+sinf(-mopot[0].suunta-pi/2)*70;
			mopot[0].z2=mopot[0].z1+cosf(-mopot[0].suunta-pi/2)*70;
			mopot[0].nopeus=0.0f;
			mopot[0].x3=mopot[0].x1;
			mopot[0].y3=mopot[0].y1;
			mopot[0].z3=mopot[0].z1;
			mopot[0].x4=mopot[0].x2;
			mopot[0].y4=mopot[0].y2;
			mopot[0].z4=mopot[0].z2;
			mopot[0].kulmakeuliminen=0;
			mopot[0].etusuunta=0;
			for (a=0; a<100; a++)mopot[0].osuma[a]=false;
		}		
	}

		

	//headlight
	lamppu[0].valo.dvPosition.x = mopot[0].x1;
	lamppu[0].valo.dvPosition.y = 100;
	lamppu[0].valo.dvPosition.z = mopot[0].z1;
	lamppu[0].valo.dvRange = 4000;			
	lamppu[0].valo.dvDirection=D3DVECTOR((float)cosf(mopot[0].suunta+mopot[0].etusuunta),(float)sinf(mopot[0].kulmakeuliminen),(float)sinf(mopot[0].suunta+mopot[0].etusuunta));
	lamppu[0].valo.dvFalloff=1.0f; 
	lamppu[0].valo.dltType=D3DLIGHT_SPOT;
	lamppu[0].valo.dvTheta=0.0f;
	lamppu[0].valo.dvPhi =0.7f;	
	lamppu[0].valo.dvAttenuation2=0.1f*0.00001f;
	m_pDevice->SetLight(0, &lamppu[0].valo);
	m_pDevice->LightEnable(0, TRUE);

	//light of world
	lamppu[1].valo.dvPosition.x = kamerax1;
	lamppu[1].valo.dvPosition.y = 5000;
	lamppu[1].valo.dvPosition.z = kameraz1;
	lamppu[1].valo.dvRange = maxvisible-4000;
	lamppu[1].valo.dcvDiffuse.r = 0.1f;    
	lamppu[1].valo.dcvDiffuse.g = 0.1f;
	lamppu[1].valo.dcvDiffuse.b = 0.1f;    
	lamppu[1].valo.dcvAmbient.r = 0.0f;
	lamppu[1].valo.dcvAmbient.g = 0.0f;    
	lamppu[1].valo.dcvAmbient.b = 0.0f;
	lamppu[1].valo.dcvSpecular.r = 0.0f;    
	lamppu[1].valo.dcvSpecular.g = 0.0f;
	lamppu[1].valo.dcvSpecular.b = 0.0f;
	lamppu[1].valo.dvDirection=1.0f; 
	lamppu[1].valo.dvFalloff=1.0f; 
	lamppu[1].valo.dltType=D3DLIGHT_POINT;
	lamppu[1].valo.dvAttenuation0=0.05f;
	lamppu[1].valo.dvAttenuation1=0.1f*0.00001f;
	lamppu[1].valo.dvAttenuation2=0.1f*0.00000001f;
	m_pDevice->SetLight(1, &lamppu[1].valo);
	m_pDevice->LightEnable(1, TRUE);

		/*	lamppu[q].valo.dltType = D3DLIGHT_POINT;	
			lamppu[q].valo.dcvDiffuse.r = 1.0f;    
			lamppu[q].valo.dcvDiffuse.g = 1.0f;
			lamppu[q].valo.dcvDiffuse.b = 1.0f;    
			lamppu[q].valo.dcvAmbient.r = 1.0f;
			lamppu[q].valo.dcvAmbient.g = 1.0f;    
			lamppu[q].valo.dcvAmbient.b = 1.0f;
			lamppu[q].valo.dcvSpecular.r = 1.0f;    
			lamppu[q].valo.dcvSpecular.g = 1.0f;
			lamppu[q].valo.dcvSpecular.b = 1.0f;
			lamppu[q].valo.dvDirection=1.0f; 
			lamppu[q].valo.dvPosition.x = x;
			lamppu[q].valo.dvPosition.y = y;  
			lamppu[q].valo.dvPosition.z = z;
			lamppu[q].valo.dvAttenuation0 = 0.5f;
			lamppu[q].valo.dvAttenuation1=0.0f;	
			lamppu[q].valo.dvAttenuation2=0.0f;
			lamppu[q].valo.dvRange = 500;
*/
	//m_pDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xFFFFEEEE);
	m_pDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xFFFFFFFF);
	//m_pDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0x00000000);
	m_pDevice->SetRenderState( D3DRENDERSTATE_ZBIAS, 0);//set zbias to 0 because of the bullet holes
	/*
	int e=0;
	int d;
	float lamppux[2000];
	float lamppuz[2000];
	for (a=0; a<mapsz; a++){
		for (b=0; b<mapsx; b++){
			for (c=0; c<3; c++){
				for (d=0; d<3; d++){	
					if((c==1)&&d==1) continue;
					e=e+1;
					lamppux[e]=a*8000+c*4000;
					lamppuz[e]=b*8000+d*4000;
				}
			}			
		}
	}

	//lamput
	e=0;
		for (a=0; a<mapsx*mapsz*8; a++){
			e=e+1;
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(lamppux[e],0,lamppuz[e]);			
			
			drawfast(&mallit[2].malli[12]);		
			
		}
	*/


	//maps
	//can you see it ?
	for (a=0; a<mapsz; a++){
		for (b=0; b<mapsx; b++){
			keskipistemap[a*mapsx+b].x=(float)b*8000+4000;
			keskipistemap[a*mapsx+b].y=0;
			keskipistemap[a*mapsx+b].z=(float)a*8000+4000;
			radiusmap[a*mapsx+b]=4000;
		}
	}
	matriisi->LoadIdentity();
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());		
	m_pDevice->ComputeSphereVisibility(keskipistemap,radiusmap,mapsx*mapsz,0,visiblemap);//remember SetTransform						
	


	//calculate distance between blocks
	float mapdistance[500];
	int maporder[500];
	int maporderx[500];
	int maporderz[500];
	int mapsvisible;
	for (q=0; q<500; q++)
		maporder[q]=499;
	for (a=0; a<mapsz; a++){
		for (b=0; b<mapsx; b++){
			//if(visiblemap[a*mapsx+b] &D3DSTATUS_CLIPINTERSECTIONALL){continue;}
			mapdistance[a*mapsx+b]=sqrtf(sqr(b*8000+4000-mopot[0].x1)+sqr(a*8000+4000-mopot[0].z1));
		}
	}

	//arrange first nearests
	mapdistance[499]=1000000;
	for (c=0; c<200; c++){
		for (a=0; a<mapsz; a++){
			for (b=0; b<mapsx; b++){
				if(visiblemap[a*mapsx+b] &D3DSTATUS_CLIPINTERSECTIONALL){continue;}
				if(mapdistance[a*mapsx+b]<mapdistance[maporder[c]])				
				{
					maporder[c]=a*mapsx+b;
					maporderx[c]=b;
					maporderz[c]=a;				
				}
			}
		}		
		mapdistance[maporder[c]]=1000000;
		if(maporder[c]==499) {mapsvisible=c;break;}
	}

	//render nearest 6
	q=16;
	if(mapsvisible<q)q=mapsvisible;
	for (c=0; c<q; c++){	
			//if(visiblemap[a*mapsx+b] &D3DSTATUS_CLIPINTERSECTIONALL){continue;}			
			
			matriisi->LoadIdentity();
			matriisi->TranslateLocal((float)maporderx[c]*8000,0,(float)maporderz[c]*8000);			
			matriisi->ScaleLocal(1,kerroin,1);
			drawfast(&mallit[1].malli[maps[maporderz[c]][maporderx[c]]]);//map
			
			if((abs(mopot[0].sektorix-maporderx[c])<2)&(abs(mopot[0].sektoriz-maporderz[c])<2))
				drawfast(&mallit[0].malli[5]);//base
			else drawfast(&mallit[0].malli[4]);//base
		
	}
/*
	//render bases
	for (a=1; a<mapsz-1; a++){
		for (b=1; b<mapsx-1; b++){
			
			if(visiblemap[a*mapsx+b] &D3DSTATUS_CLIPINTERSECTIONALL){continue;}
			
			matriisi->LoadIdentity();
			matriisi->TranslateLocal((float)b*8000,0,(float)a*8000);			
			if((abs(mopot[0].sektorix-b)<2)&(abs(mopot[0].sektoriz-a)<2))
				drawfast(&mallit[0].malli[5]);//pohja
			else drawfast(&mallit[0].malli[4]);//pohja
		}
	}
*/

	
	
	//bullets	
	luoteja=0;
	for (a=10; a<maksimiluoteja; a++){//first 10 are for driving over people
		if(luoti[a].poista)continue;
		luoteja=luoteja+1;
		matriisi->LoadIdentity();		
		luotitrace[luoteja*2].position.x=luoti[a].paikka.x;
		luotitrace[luoteja*2].position.y=luoti[a].paikka.y;
		luotitrace[luoteja*2].position.z=luoti[a].paikka.z;
		
		luotitrace[luoteja*2+1].position.x=luoti[a].paikkavanha.x;
		luotitrace[luoteja*2+1].position.y=luoti[a].paikkavanha.y;
		luotitrace[luoteja*2+1].position.z=luoti[a].paikkavanha.z;

		switch (ase[luoti[a].aseesta].panoskuva) 
		{
		

			case 0:{
			luotitrace[luoteja*2].u=0;
			luotitrace[luoteja*2].v=0.16f;
			luotitrace[luoteja*2+1].u=1;
			luotitrace[luoteja*2+1].v=0.16f;
			break;
			}
			
			case 1:{
			luotitrace[luoteja*2].u=0;
			luotitrace[luoteja*2].v=0.33f;
			luotitrace[luoteja*2+1].u=1;
			luotitrace[luoteja*2+1].v=0.33f;
			break;
			}

			case 2:{
			luotitrace[luoteja*2].u=0;
			luotitrace[luoteja*2].v=0.55f;
			luotitrace[luoteja*2+1].u=1;
			luotitrace[luoteja*2+1].v=0.55f;
			break;
			}

			case 3:{
			luotitrace[luoteja*2].u=0;
			luotitrace[luoteja*2].v=0.80f;
			luotitrace[luoteja*2+1].u=1;
			luotitrace[luoteja*2+1].v=0.80f;
			break;
			}
		}



	}

	m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, 
												D3DBLEND_ONE );
	m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, 
												D3DBLEND_ONE );
	m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
		m_pDevice->SetMaterial( &mat[30] );
		m_pDevice->SetTexture( 0, tausta[30] );
		m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());		  				
		m_pDevice->DrawPrimitive(D3DPT_LINELIST  ,
			D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,luotitrace,luoteja*2,NULL);
		m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);

	
	
	//are mopeds visible
	for (a=0; a<mopoja; a++){
			if(mopot[a].pois)continue;
			keskipistemap[a].x=mopot[a].x1;
			keskipistemap[a].y=0;
			keskipistemap[a].z=mopot[a].z1;
			radiusmap[a]=800;
		}	
	matriisi->LoadIdentity();
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());		
	m_pDevice->ComputeSphereVisibility(keskipistemap,radiusmap,mopoja,0,visiblemap);//remember SetTransform						
	



	int e, mopokuva;


	//chasis
	if(pelivaihe2!=5)//if player is not dead
	for (d=0; d<mopoja; d++){
		if(mopot[d].pois)continue;
		mopot[d].visible=true;
		if(visiblemap[d] &D3DSTATUS_CLIPINTERSECTIONALL){mopot[d].visible=false;continue;}
		
		//if too far away othe mopeds are ugly
		mopot[d].distanssi=sqrtf(sqr(mopot[d].x1-mopot[0].x1)+sqr(mopot[d].z1-mopot[0].z1));		
		
		if(mopot[d].mopona==0){
			mopokuva=0;
			if (mopot[d].distanssi>2000) mopokuva=9;
			if(!mapmode) mopokuva=9;
		}
		if(mopot[d].mopona==1){
			mopokuva=6;
		}


		if(mopokuva==0){
			matriisi->LoadIdentity();

			matriisi->TranslateLocal(mopot[d].x2,mopot[d].y2,mopot[d].z2);			
			matriisi->RotateYawPitchRollLocal(-mopot[d].suunta,mopot[d].kulmakallistus,mopot[d].kulmakeuliminen);
			drawfast(&mallit[mopokuva].malli[0]);
		}
		if(mopokuva==6){
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(mopot[d].x2,mopot[d].y2+1.5f,mopot[d].z2);			
			matriisi->RotateYawPitchRollLocal(-mopot[d].suunta,mopot[d].kulmakallistus,mopot[d].kulmakeuliminen);
			drawfast(&mallit[mopokuva].malli[0]);
		}
		if(mopokuva==9){
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(mopot[d].x2,mopot[d].y2+1.5f,mopot[d].z2);			
			matriisi->RotateYawPitchRollLocal(-mopot[d].suunta,mopot[d].kulmakallistus,mopot[d].kulmakeuliminen);
			drawfast(&mallit[mopokuva].malli[0]);
		}
/*
	ukkotekstuuri[d].osa[0]=10;//torso
	ukkotekstuuri[d].osa[1]=11;//legs
	ukkotekstuuri[d].osa[2]=12;//hand
	ukkotekstuuri[d].osa[3]=14;//face
*/

	//passanger
	if(mopot[d].mission.tyyppi==1)
	if(mopot[d].mission.suoritettu==0){	
		matriisi->Push();
		matriisi->TranslateLocal(7,57,0);

		//select textures
		switch (mopot[d].mission.asiakas[0].kuva) 
			{
			case 3:{
				e=0;
				break;
				   }			
			case 7:{
				e=2;
				break;
				   }
			case 8:{
				e=3;
				break;
				   }			
			case 10:{
				e=4;
				break;
				   }
			}

		matriisi->Push();q=0;//ass				
		matriisi->TranslateLocal(mopot[d].mission.asiakas[0].ruumiinosa[q].x,mopot[d].mission.asiakas[0].ruumiinosa[q].y,mopot[d].mission.asiakas[0].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(0,0,0);
		mallit[mopot[d].mission.asiakas[0].kuva].malli[q].sisus[0].textuuri2=ukkotekstuuri[e].osa[1];
		drawfast(&mallit[mopot[d].mission.asiakas[0].kuva].malli[q]);
		matriisi->Pop();		

		matriisi->Push();q=1;//torso
		matriisi->TranslateLocal(mopot[d].mission.asiakas[0].ruumiinosa[q].x,mopot[d].mission.asiakas[0].ruumiinosa[q].y,mopot[d].mission.asiakas[0].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(0,0,-0.14f);
		mallit[mopot[d].mission.asiakas[0].kuva].malli[q].sisus[0].textuuri2=ukkotekstuuri[e].osa[0];
		drawfast(&mallit[mopot[d].mission.asiakas[0].kuva].malli[q]);

		matriisi->Push();q=2;//head
		matriisi->TranslateLocal(mopot[d].mission.asiakas[0].ruumiinosa[q].x,mopot[d].mission.asiakas[0].ruumiinosa[q].y,mopot[d].mission.asiakas[0].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(0,0,0);
		mallit[mopot[d].mission.asiakas[0].kuva].malli[q].sisus[0].textuuri2=ukkotekstuuri[e].osa[3];
		drawfast(&mallit[mopot[d].mission.asiakas[0].kuva].malli[q]);
		matriisi->Pop();				

		matriisi->Push();q=3;//left upper arm
		matriisi->TranslateLocal(mopot[d].mission.asiakas[0].ruumiinosa[q].x,mopot[d].mission.asiakas[0].ruumiinosa[q].y,mopot[d].mission.asiakas[0].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(0,0,pi*0.1f);
		mallit[mopot[d].mission.asiakas[0].kuva].malli[q].sisus[0].textuuri2=ukkotekstuuri[e].osa[2];
		drawfast(&mallit[mopot[d].mission.asiakas[0].kuva].malli[q]);

		matriisi->Push();q=4;//left lower arm
		matriisi->TranslateLocal(mopot[d].mission.asiakas[0].ruumiinosa[q].x,mopot[d].mission.asiakas[0].ruumiinosa[q].y,mopot[d].mission.asiakas[0].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(0,0,pi*0.35f);
		mallit[mopot[d].mission.asiakas[0].kuva].malli[q].sisus[0].textuuri2=ukkotekstuuri[e].osa[2];
		drawfast(&mallit[mopot[d].mission.asiakas[0].kuva].malli[q]);
		
		matriisi->Pop();
		matriisi->Pop();
		
		matriisi->Push();q=8;//rigth upper arm
		matriisi->TranslateLocal(mopot[d].mission.asiakas[0].ruumiinosa[q].x,mopot[d].mission.asiakas[0].ruumiinosa[q].y,mopot[d].mission.asiakas[0].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(0,0,pi*0.1f);
		mallit[mopot[d].mission.asiakas[0].kuva].malli[q].sisus[0].textuuri2=ukkotekstuuri[e].osa[2];
		drawfast(&mallit[mopot[d].mission.asiakas[0].kuva].malli[q]);

		matriisi->Push();q=7;//rigth lower arm
		matriisi->TranslateLocal(mopot[d].mission.asiakas[0].ruumiinosa[q].x,mopot[d].mission.asiakas[0].ruumiinosa[q].y,mopot[d].mission.asiakas[0].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(0,0,pi*0.35f);
		mallit[mopot[d].mission.asiakas[0].kuva].malli[q].sisus[0].textuuri2=ukkotekstuuri[e].osa[2];
		drawfast(&mallit[mopot[d].mission.asiakas[0].kuva].malli[q]);

		matriisi->Pop();
		matriisi->Pop();
		matriisi->Pop();


		matriisi->Push();q=5;////left upper leg
		matriisi->TranslateLocal(mopot[d].mission.asiakas[0].ruumiinosa[q].x,mopot[d].mission.asiakas[0].ruumiinosa[q].y,mopot[d].mission.asiakas[0].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(0.26f,0,1.45f);
		mallit[mopot[d].mission.asiakas[0].kuva].malli[q].sisus[0].textuuri2=ukkotekstuuri[e].osa[1];
		drawfast(&mallit[mopot[d].mission.asiakas[0].kuva].malli[q]);		

		matriisi->Push();q=6;////left lower leg
		matriisi->TranslateLocal(mopot[d].mission.asiakas[0].ruumiinosa[q].x,mopot[d].mission.asiakas[0].ruumiinosa[q].y,mopot[d].mission.asiakas[0].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(0,0,-0.8f);
		mallit[mopot[d].mission.asiakas[0].kuva].malli[q].sisus[0].textuuri2=ukkotekstuuri[e].osa[1];
		drawfast(&mallit[mopot[d].mission.asiakas[0].kuva].malli[q]);
		matriisi->Pop();
		matriisi->Pop();

		matriisi->Push();q=9;////rigth upper leg
		matriisi->TranslateLocal(mopot[d].mission.asiakas[0].ruumiinosa[q].x,mopot[d].mission.asiakas[0].ruumiinosa[q].y,mopot[d].mission.asiakas[0].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(-0.26f,0,1.45f);
		mallit[mopot[d].mission.asiakas[0].kuva].malli[q].sisus[0].textuuri2=ukkotekstuuri[e].osa[1];
		drawfast(&mallit[mopot[d].mission.asiakas[0].kuva].malli[q]);


		matriisi->Push();q=10;////rigth lower leg
		matriisi->TranslateLocal(mopot[d].mission.asiakas[0].ruumiinosa[q].x,mopot[d].mission.asiakas[0].ruumiinosa[q].y,mopot[d].mission.asiakas[0].ruumiinosa[q].z);		
		matriisi->RotateYawPitchRollLocal(0,0,0-0.8f);
		mallit[mopot[d].mission.asiakas[0].kuva].malli[q].sisus[0].textuuri2=ukkotekstuuri[e].osa[1];
		drawfast(&mallit[mopot[d].mission.asiakas[0].kuva].malli[q]);
		matriisi->Pop();
		matriisi->Pop();
		matriisi->Pop();
	}
	//muzzleflare and location of gun barrel
		matriisi->Push();
		matriisi->TranslateLocal(84,70,0);		
		matriisi->RotateYawPitchRollLocal(0,randDouble(-pi,pi),0);
		mopot[d].piippu=*matriisi->GetTop();			
	if(mopot[d].suuliekki){
		drawfast(&mallit[2].malli[15]);	
	}
		matriisi->Pop();

	if(mopokuva==0){
		//rear wheel
		matriisi->Push();
		matriisi->TranslateLocal(0,20,0);
		matriisi->RotateYawPitchRollLocal(0,0,mopot[d].kulmaetu);			
		drawfast(&mallit[mopokuva].malli[3]);	
		matriisi->Pop();
		//frontside 
		matriisi->TranslateLocal(70,0,0);
		//matriisi->RotateYawPitchRollLocal(-mopot[d].suunta,0,0);
		matriisi->RotateYawPitchRollLocal(-mopot[d].etusuunta,0,0);	
		drawfast(&mallit[mopokuva].malli[2]);
		//frontwheel
		matriisi->TranslateLocal(40,20,0);
		matriisi->RotateYawPitchRollLocal(0,0,mopot[d].kulmaetu);		
		drawfast(&mallit[mopokuva].malli[3]);
	}
	if(mopokuva==6){
		//rearwheel
		matriisi->Push();
		matriisi->TranslateLocal(0,20,0);
		matriisi->RotateYawPitchRollLocal(0,0,mopot[d].kulmaetu);			
		drawfast(&mallit[mopokuva].malli[2]);	
		matriisi->Pop();
		//front side
		matriisi->TranslateLocal(79,0,0);
		matriisi->RotateYawPitchRollLocal(-mopot[d].etusuunta,0,0);	
		drawfast(&mallit[mopokuva].malli[1]);
		//front wheel
		matriisi->TranslateLocal(40,20,0);
		matriisi->RotateYawPitchRollLocal(0,0,mopot[d].kulmaetu);		
		drawfast(&mallit[mopokuva].malli[2]);
	}
	if(mopokuva==9){
		//rear wheel
		matriisi->Push();
		matriisi->TranslateLocal(0,20,0);
		matriisi->RotateYawPitchRollLocal(0,0,mopot[d].kulmaetu);			
		drawfast(&mallit[mopokuva].malli[2]);	
		matriisi->Pop();
		//front side
		matriisi->TranslateLocal(79,0,0);
		matriisi->RotateYawPitchRollLocal(-mopot[d].etusuunta,0,0);	
		drawfast(&mallit[mopokuva].malli[1]);
		//front wheel
		matriisi->TranslateLocal(40,20,0);
		matriisi->RotateYawPitchRollLocal(0,0,mopot[d].kulmaetu);		
		drawfast(&mallit[mopokuva].malli[2]);
	}
			
	}

	m_pDevice->LightEnable(1, FALSE);
	rendercharacters();
	m_pDevice->LightEnable(1, TRUE);

	//camera angle
	float camq=-atan2f(-kamerax2+kamerax1,-kameraz2+kameraz1);			
	float camw=0;
	float came=-atan2f(-kameray2+kameray1,sqrtf((sqr(-kameraz2+kameraz1)+sqr(-kamerax2+kamerax1))));
	
	if(mopot[0].valittuukko!=-6667){
			/*m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, 
												D3DBLEND_ONE );
			m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, 
												D3DBLEND_ONE );
		m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);*/
			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
			//rendering crosshair
			if(mopot[0].valittuukko>=0){				
				matriisi->LoadIdentity();		
				matriisi->TranslateLocal(ukko[mopot[0].valittuukko].x,57,ukko[mopot[0].valittuukko].z);
				matriisi->RotateYawPitchRollLocal(-camq+pi/2,camw,came);
				drawfast(&mallit[2].malli[0]);
			}
			//rendering crosshair
			if(mopot[0].valittuukko<=1){				
				matriisi->LoadIdentity();		
				matriisi->TranslateLocal(mopot[-mopot[0].valittuukko-1].x1,57,mopot[-mopot[0].valittuukko-1].z1);
				matriisi->RotateYawPitchRollLocal(-camq+pi/2,camw,came);
				drawfast(&mallit[2].malli[0]);
			}
			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
	}
	
	//}


	//bulletholes	
	//if(savuja>0)
	{	
	m_pDevice->SetRenderState( D3DRENDERSTATE_ZBIAS, 1);//set zbias as 1 beacause of the bullet holes
		
	
	
	
	for (q=0; q<maksimisavuja; q++)
	{
		if(savu[q].pois)continue;
		//kappaletta=kappaletta+1;
		radius[q]=100.01f;	
		keskipiste[q].x=savu[q].paikka.x;
		keskipiste[q].y=savu[q].paikka.y;
		keskipiste[q].z=savu[q].paikka.z;
	}


	matriisi->LoadIdentity();
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());		
	m_pDevice->ComputeSphereVisibility(keskipiste,radius,maksimisavuja,0,visible);//remember SetTransform
	m_pDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,FALSE);//ei rendertext z-bufferiin, jotta savut olisi läpinäkyvät
	//m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,FALSE);	

	int kappaletta=0;//ammount of bullet holes
			
			
			for (q=0; q<maksimisavuja; q++){
				if(savu[q].pois)continue;				
				if((visible[q] &D3DSTATUS_CLIPINTERSECTIONALL   ) ){continue;}

			
				if(savu[q].tyyppi==0){//normal bullet hole
					kolmiot[kappaletta*12+0].position.x=savu[q].paikka.x-savu[q].cos*-2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+0].position.y=savu[q].paikka.y+0;//*savu[q].koko;
					kolmiot[kappaletta*12+0].position.z=savu[q].paikka.z-savu[q].sin*-2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+0].u=0.0f;
					kolmiot[kappaletta*12+0].v=1.0f;
					
					kolmiot[kappaletta*12+1].position.x=savu[q].paikka.x+savu[q].cos*2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+1].position.y=savu[q].paikka.y+5;//*savu[q].koko;
					kolmiot[kappaletta*12+1].position.z=savu[q].paikka.z+savu[q].sin*2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+1].u=1.0f;
					kolmiot[kappaletta*12+1].v=1.0f;
					
					kolmiot[kappaletta*12+2].position.x=savu[q].paikka.x+savu[q].cos*-2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+2].position.y=savu[q].paikka.y+5;//*savu[q].koko;
					kolmiot[kappaletta*12+2].position.z=savu[q].paikka.z+savu[q].sin*-2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+2].u=0.0f;
					kolmiot[kappaletta*12+2].u=1.0f;

					kolmiot[kappaletta*12+3].position.x=savu[q].paikka.x-savu[q].cos*-2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+3].position.y=savu[q].paikka.y+0;//*savu[q].koko;
					kolmiot[kappaletta*12+3].position.z=savu[q].paikka.z-savu[q].sin*-2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+3].u=0.0f;
					kolmiot[kappaletta*12+3].v=0.0f;
					
					kolmiot[kappaletta*12+4].position.x=savu[q].paikka.x+savu[q].cos*-2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+4].position.y=savu[q].paikka.y+5;//*savu[q].koko;
					kolmiot[kappaletta*12+4].position.z=savu[q].paikka.z+savu[q].sin*-2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+4].u=1.0f;
					kolmiot[kappaletta*12+4].v=1.0f;
					
					kolmiot[kappaletta*12+5].position.x=savu[q].paikka.x+savu[q].cos*-2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+5].position.y=savu[q].paikka.y+0;//*savu[q].koko;
					kolmiot[kappaletta*12+5].position.z=savu[q].paikka.z+savu[q].sin*-2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+5].u=0.0f;
					kolmiot[kappaletta*12+5].u=1.0f;

					


					kolmiot[kappaletta*12+6].position.x=savu[q].paikka.x-savu[q].cos*+2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+6].position.y=savu[q].paikka.y+0;//*savu[q].koko;
					kolmiot[kappaletta*12+6].position.z=savu[q].paikka.z-savu[q].sin*+2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+6].u=0.0f;
					kolmiot[kappaletta*12+6].v=1.0f;
					
					kolmiot[kappaletta*12+7].position.x=savu[q].paikka.x+savu[q].cos*-2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+7].position.y=savu[q].paikka.y+5;//*savu[q].koko;
					kolmiot[kappaletta*12+7].position.z=savu[q].paikka.z+savu[q].sin*-2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+7].u=1.0f;
					kolmiot[kappaletta*12+7].v=1.0f;
					
					kolmiot[kappaletta*12+8].position.x=savu[q].paikka.x+savu[q].cos*+2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+8].position.y=savu[q].paikka.y+5;//*savu[q].koko;
					kolmiot[kappaletta*12+8].position.z=savu[q].paikka.z+savu[q].sin*+2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+8].u=0.0f;
					kolmiot[kappaletta*12+8].u=1.0f;

					kolmiot[kappaletta*12+9].position.x=savu[q].paikka.x-savu[q].cos*+2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+9].position.y=savu[q].paikka.y+0;//*savu[q].koko;
					kolmiot[kappaletta*12+9].position.z=savu[q].paikka.z-savu[q].sin*+2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+9].u=0.0f;
					kolmiot[kappaletta*12+9].v=0.0f;
					
					kolmiot[kappaletta*12+10].position.x=savu[q].paikka.x+savu[q].cos*+2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+10].position.y=savu[q].paikka.y+5;//*savu[q].koko;
					kolmiot[kappaletta*12+10].position.z=savu[q].paikka.z+savu[q].sin*+2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+10].u=1.0f;
					kolmiot[kappaletta*12+10].v=1.0f;
					
					kolmiot[kappaletta*12+11].position.x=savu[q].paikka.x+savu[q].cos*+2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+11].position.y=savu[q].paikka.y+0;//*savu[q].koko;
					kolmiot[kappaletta*12+11].position.z=savu[q].paikka.z+savu[q].sin*+2.5f;//*savu[q].koko;
					kolmiot[kappaletta*12+11].u=0.0f;
					kolmiot[kappaletta*12+11].u=1.0f;
					kappaletta=kappaletta+1;					
				}		

				
			}


			
			
			//render bulletholes2
			
			if(kappaletta>0){
			m_pDevice->SetMaterial( &mat[15] );
			m_pDevice->SetTexture( 0, tausta[15] );
			m_pDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE ,TRUE);			
			matriisi->LoadIdentity();
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());		  		
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
				D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,kolmiot,kappaletta*12,NULL);
			m_pDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE ,FALSE);						
			}			

			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);

			
			
			for (q=0; q<maksimisavuja; q++){
				if(savu[q].pois)continue;
				if((visible[q] &D3DSTATUS_CLIPINTERSECTIONALL   ) ){continue;}				

				//smokes towards camera
				if(savu[q].up!=0){		
					savu[q].q=camq;
					savu[q].w=camw;
					savu[q].e=came;
				}

				switch(savu[q].tyyppi){

				case 4:{//ball like smoke
					matriisi->LoadIdentity();
					matriisi->TranslateLocal(savu[q].paikka.x,savu[q].paikka.y,savu[q].paikka.z);
					matriisi->RotateYawPitchRollLocal(-savu[q].q+pi/2,savu[q].w,savu[q].e);
					matriisi->ScaleLocal(savu[q].koko,savu[q].koko,savu[q].koko);
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
					m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, 
												D3DBLEND_DESTCOLOR    );
					m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, 
												D3DBLEND_SRCALPHA     );				
					drawfast(&mallit[2].malli[10]);
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
					break;
				}
				
				case 3:{//explosion
					matriisi->LoadIdentity();
					matriisi->TranslateLocal(savu[q].paikka.x,savu[q].paikka.y,savu[q].paikka.z);
					matriisi->RotateYawPitchRollLocal(-savu[q].q+pi/2,savu[q].w,savu[q].e);
					matriisi->ScaleLocal(savu[q].koko,savu[q].koko,savu[q].koko);
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
					m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, 
												D3DBLEND_ONE );
					m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, 
												D3DBLEND_ONE );				
					drawfast(&mallit[2].malli[5]);
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
					break;
				}
				
				case 2:{//smoke
					matriisi->LoadIdentity();
					matriisi->TranslateLocal(savu[q].paikka.x,savu[q].paikka.y,savu[q].paikka.z);
					matriisi->RotateYawPitchRollLocal(-savu[q].q+pi/2,savu[q].w,savu[q].e);
					matriisi->ScaleLocal(savu[q].koko,savu[q].koko,savu[q].koko);
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
					m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, 
												D3DBLEND_SRCCOLOR );
					m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, 
												D3DBLEND_SRCALPHA );					
					
					//select randomly from two options
					if(savu[q].kuva==0){
						drawfast(&mallit[2].malli[3]);
					}
					else{
						drawfast(&mallit[2].malli[7]);
					}
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
					break;					   
				}

				case 1:{//One big hell of a hole
					matriisi->LoadIdentity();
					matriisi->TranslateLocal(savu[q].paikka.x,savu[q].paikka.y,savu[q].paikka.z);
					matriisi->RotateYawPitchRollLocal(-savu[q].q+pi/2,savu[q].w,savu[q].e);
					matriisi->ScaleLocal(savu[q].koko,savu[q].koko,savu[q].koko);
					
					
					m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, 
												D3DBLEND_ONE );
					m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, 
												D3DBLEND_ONE );						
					drawfast(&mallit[2].malli[4]);

					matriisi->LoadIdentity();
					matriisi->TranslateLocal(savu[q].paikka.x,savu[q].paikka.y,savu[q].paikka.z);
					matriisi->RotateYawPitchRollLocal(-savu[q].q+pi/2,savu[q].w,savu[q].e);
					matriisi->ScaleLocal(savu[q].koko*0.6f,savu[q].koko*0.6f,savu[q].koko*0.6f);
					
					
					m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, 
												D3DBLEND_ZERO    );
					m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, 
												D3DBLEND_INVSRCCOLOR       );						
					drawfast(&mallit[2].malli[4]);
					
					break;
				}	

			/*	case 1:{//One big hell of a hole
					matriisi->LoadIdentity();
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_EQUAL);
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE); 
					matriisi->TranslateLocal(savu[q].paikka.x,savu[q].paikka.y,savu[q].paikka.z);
					matriisi->RotateYawPitchRollLocal(-savu[q].q+pi/2,savu[q].w,savu[q].e);
					matriisi->ScaleLocal(savu[q].koko,savu[q].koko,savu[q].koko);
					m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,false);										
					drawfast(&mallit[2].malli[16]);
					m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,true);
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE); 
					//m_pDevice->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);
					break;
				}*/
			}
			
			}
			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
			m_pDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);


	}
	
	

	//arrows and crosshairs related to mission
		m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
		m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_SRCCOLOR);
		m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_SRCALPHA);
		m_pDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,FALSE);
	
	if(mopot[0].mission.suoritettu==0){
		float kx,kz;//targets coordinates
		int f;
		//target	
		for (f=0; f<mopot[0].mission.kohteita; f++){
			matriisi->LoadIdentity();
			if(mopot[0].mission.kohdetyyppi==0)//character //ukko
			{			
				kx=ukko[mopot[0].mission.kohde[f]].x;				
				kz=ukko[mopot[0].mission.kohde[f]].z;
			}				
			if(mopot[0].mission.kohdetyyppi==1)//coordinates
			{
				kx=mopot[0].mission.kohdex[0];
				kz=mopot[0].mission.kohdez[0];
			}	
			if(mopot[0].mission.kohdetyyppi==2)//moped
			{
				kx=mopot[mopot[0].mission.kohde[f]].x1;
				kz=mopot[mopot[0].mission.kohde[f]].z1;
			}
			matriisi->TranslateLocal(kx,57,kz);	
			matriisi->RotateYawPitchRollLocal(-camq+pi/2,camw,came);
			drawfast(&mallit[2].malli[8]);
		

			//arrow
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(mopot[0].x1,10,mopot[0].z1);
			matriisi->RotateYawPitchRollLocal(-atan2f(mopot[0].z1-kz,mopot[0].x1-kx)+pi/2+pi,0,pi/2);		
			drawfast(&mallit[2].malli[9]);
			if(mopot[0].mission.kohdetyyppi==1)//render first one of the coordinates
				if(f>=0){break;}
		}
		
		//timer
		if(mopot[0].mission.aika>0){
			strcpy(rivi,"time left ");
			itoa((int)mopot[0].mission.aika/1000,temprivi,10);
			strcat(rivi,temprivi);
			rendertext((int)(1024*0.03f),(int)(768*0.95f-30),0,rivi);		
		}
		
		
		//mission brief text
			rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,mopot[0].mission.shortbriefing);
		/*//go and kill some one
			if(mopot[0].mission.tyyppi==0){
				if(mopot[0].mission.alatyyppi==0){
					rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"kill him");	
				}
				if(mopot[0].mission.alatyyppi==1){
					rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"kill him");
				}
			}
			//taxi
			if(mopot[0].mission.tyyppi==1){
				if(mopot[0].mission.alatyyppi==0){
					rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"take me there");
				}
				if(mopot[0].mission.alatyyppi==1){
					rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"take me there");
				}
			}
*/
	}
	
	m_pDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);

	if(mopot[0].mission.suoritettu==1){		
			rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"mission accomplished");		
	}
	
	if(mopot[0].mission.suoritettu==2){		
			rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"mission failed");		
	}
	
	if(mopot[0].mission.suoritettu==3){		
			rendertext((int)(1024*0.03f),(int)(768*0.95f-15),0,"no mission");		
	}

	

			
		
		

	m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);


	//end demo
	if(pelivaihe2==1){
		rendertext((int)(1024*0.08f),(int)(768*0.15f),60,missioninfo[20]);
	}
	//pause
	if(pelivaihe2==2){
		svolume(voices[1],DSBVOLUME_MIN, options[1]&&SOUNDS_LOADED);
		rendertext((int)(1024*0.15f),(int)(768*0.48f+15*0),70,"Bikez II is now paused");
		rendertext((int)(1024*0.15f),(int)(768*0.48f+15*1),70,"esc to return to game");
		rendertext((int)(1024*0.15f),(int)(768*0.48f+15*2),70,"f9 to exit");
	}
	//beginning demo
	if(pelivaihe2==3){
		rendertext((int)(1024*0.08f),(int)(768*0.15f),60,"You are a mercenary biker in a near future dark city. The local criminal faction, Bikez, has just signed a contract with you about completing a series of missions including a whole lot of killing and blood...");
		rendertext((int)(1024*0.08f),(int)(768*0.24f),60,"If you are new to Bikez press Enter to learn the basics. Otherwise press Esc to start playing.");
	}
	//beginning demo
	if(pelivaihe2==4){
		rendertext((int)(1024*0.08f),(int)(768*0.15f),60,"Keys: Put your right hand on the arrow keys and your left hand so that your little finger is on number 1 and your index finger on number 4. Use 5 to slow the game down. Shift between bird´s eye view and following camera by pressing the tab key. Space is hand brake.");
		rendertext((int)(1024*0.08f),(int)(768*0.30f),60,"When you are low on energy, in need of a weapons upgrade, or need to save your game, you should find a Bikez warehouse. These warehouses are brownish buildings with a Bikez sign. Enter below the sign.");
		rendertext((int)(1024*0.08f),(int)(768*0.43f),60,"To get a mission, you must find a man that looks like your character. After finding the guy you have to stop by him, a green circle is lit under him if everything is right. Then press enter to get a mission.");
	}
	//is dead
	if(pelivaihe2==5){
		luoti[0].poista=true;
		pelinopeus=0.2f;
		calculatebullets();
		calculatebullets();
		rendertext((int)(1024*0.15f),(int)(768*0.48f+15*0),70,"You are dead. All is lost.");
	}

	//press enter to ask for a mission
	if(mopot[0].mission.suoritettu!=0){//there is no mission
		if(mopot[0].nearestukko!=-1)
		if(!ukko[mopot[0].nearestukko].kuole)
		if(!ukko[mopot[0].nearestukko].puoli==0)
		{
			if(fabs(mopot[0].nopeus)<0.7f)
			rendertext((int)(1024*0.03f),(int)(768*0.95f),0,"press enter");		
			
			if(fabs(mopot[0].nopeus)>=0.7f)
			rendertext((int)(1024*0.03f),(int)(768*0.95f),0,"slow down");
		}
	}
	//energy meter
			//set camera to its place
			kamerax1=0;
			kameray1=0;
			kameraz1=100;
			kamerax2=kamerax1;
			kameray2=kameray1;
			kameraz2=0;
			m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);	
			m_Projection = ProjectionMatrix(25.0f, maxvisible, (float)(80*pi/180)); // 60 vision field
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);
			m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE); 

		//meter
		matriisi->LoadIdentity();
		matriisi->TranslateLocal(156-500,256-500,-4.199f*100);		
		matriisi->ScaleLocal(2.5f,2.5f,2.5f);
		matriisi->RotateYawPitchRollLocal(0,4.5f,0.15f);		
		drawfast(&mallit[2].malli[16]);
		//needle of meter
		if(mopot[0].energia<0)mopot[0].energia=0;
		float energiamittari=-mopot[0].energia/100*4.24f+2.120f;
		matriisi->RotateYawPitchRollLocal(energiamittari,0,0);
		drawfast(&mallit[2].malli[17]);

			m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE); 


		//money		
			itoa((int)mopot[0].rahat,rivi,10);
			rendertext(896,710,0,rivi);

/*
	//energy meter
	pvertex vertex[6];
	float korkeus=50;
			vertex[0].position.x=-500;
			vertex[0].position.y=-korkeus;
			vertex[0].position.z=0;
			vertex[0].u=0;
			vertex[0].v=1;

			vertex[1].position.x=500;
			vertex[1].position.y=korkeus;
			vertex[1].position.z=0;
			vertex[1].u=1;
			vertex[1].v=0;

			vertex[2].position.x=-500;
			vertex[2].position.y=korkeus;
			vertex[2].position.z=0;
			vertex[2].u=0;
			vertex[2].v=0;

			vertex[3].position.x=-500;
			vertex[3].position.y=-korkeus;
			vertex[3].position.z=0;
			vertex[3].u=0;
			vertex[3].v=1;

			vertex[4].position.x=500;
			vertex[4].position.y=-korkeus;
			vertex[4].position.z=0;
			vertex[4].u=1;
			vertex[4].v=1;

			vertex[5].position.x=500;
			vertex[5].position.y=korkeus;
			vertex[5].position.z=0;
			vertex[5].u=1;
			vertex[5].v=0;
		
			//set camera to its place
			kamerax1=0;
			kameray1=0;
			kameraz1=1660;
			kamerax2=0;
			kameray2=960;
			kameraz2=0;
			m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);	
			m_Projection = ProjectionMatrix(25.0f, maxvisible, (float)(80*pi/180)); // 60 vision field
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);

			//render energy meter
			m_pDevice->SetMaterial( &mat[45] );
			m_pDevice->SetTexture( 0, tausta[45] );			
			matriisi->LoadIdentity();
			//matriisi->TranslateLocal(mopot[0].x1,0,mopot[0].z1);
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());		 
			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
			m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,D3DBLEND_ONE);
			m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND,D3DBLEND_ONE);	
			m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE); 
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
				D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,vertex,6,NULL);
			//m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE); 
			//m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);


			vertex[0].position.x=-mopot[0].energia/100*1000+500;
			vertex[0].position.y=-korkeus;
			vertex[0].position.z=0;
			vertex[0].u=1-mopot[0].energia/100;
			vertex[0].v=1;

			vertex[1].position.x=500;
			vertex[1].position.y=korkeus;
			vertex[1].position.z=0;
			vertex[1].u=1;
			vertex[1].v=0;

			vertex[2].position.x=-mopot[0].energia/100*1000+500;
			vertex[2].position.y=korkeus;
			vertex[2].position.z=0;
			vertex[2].u=1-mopot[0].energia/100;
			vertex[2].v=0;

			vertex[3].position.x=-mopot[0].energia/100*1000+500;
			vertex[3].position.y=-korkeus;
			vertex[3].position.z=0;
			vertex[3].u=1-mopot[0].energia/100;
			vertex[3].v=1;

			vertex[4].position.x=500;
			vertex[4].position.y=-korkeus;
			vertex[4].position.z=0;
			vertex[4].u=1;
			vertex[4].v=1;

			vertex[5].position.x=500;
			vertex[5].position.y=korkeus;
			vertex[5].position.z=0;
			vertex[5].u=1;
			vertex[5].v=0;
		
			//render energy meter
			m_pDevice->SetMaterial( &mat[46] );
			m_pDevice->SetTexture( 0, tausta[46] );			
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST  ,
				D3DFVF_XYZ |D3DFVF_TEX1|D3DFVF_TEXCOORDSIZE2(0) ,vertex,6,NULL);
			m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE); 
			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
*/

			m_pDevice->LightEnable(1, FALSE);

}

void render_mission(void){//render mission briefing

	int a,b;
	char rivi[200],temprivi[200];

	float kerroin=0.055f;
	//m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x00000000, 0, 0 );

	//m_View = ViewMatrix(D3DVECTOR(10,50000,10), D3DVECTOR(0,0,0), D3DVECTOR(0,1,0), 0);
	m_View = ViewMatrix(D3DVECTOR(mapsx*8000*0.5f*kerroin+100,10000,mapsz*8000*0.5f*kerroin), D3DVECTOR(mapsx*8000*0.5f*kerroin,0,mapsz*8000*0.5f*kerroin), D3DVECTOR(0,1,0), 0);
	m_Projection = ProjectionMatrix(4000, 11000, (float)(30*pi/180)); // 60 vision field
	
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);	
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &m_Projection);
	/*
	//keyboard control
	//accept mission
	if((mopot[0].enter2==false) & (mopot[0].enter==true)){
		if(missionantovaihe==1){
			pelivaihe=0;//back to riding
			mopot[0].mission=mopot[0].mission_arvottu;
			//ukko tulee kyytiin
			if(mopot[0].mission.tyyppi==1)
				ukko[mopot->nearestukko].pois=true;
		}
		missionantovaihe=1;//mission briefing is readed
	}*/
	/*if((mopot[0].esc2==false) & (mopot[0].esc==true)){
		pelivaihe=0;//back to riding
	}*/




	//maps	- kartat
/*
	//is it visible?
	for (a=0; a<mapsz; a++){
		for (b=0; b<mapsx; b++){
			keskipistemap[a*mapsx+b].x=(float)b*8000+4000;
			keskipistemap[a*mapsx+b].y=0;
			keskipistemap[a*mapsx+b].z=(float)a*8000+4000;
			radiusmap[a*mapsx+b]=4000;
		}
	}
	matriisi->LoadIdentity();
	m_pDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, *matriisi->GetTop());		
	m_pDevice->ComputeSphereVisibility(keskipistemap,radiusmap,mapsx*mapsz,0,visiblemap);//remember SetTransform						
	*/
	//rendering map
	for (a=0; a<mapsz; a++){
		for (b=0; b<mapsx; b++){
			
		//	if(visiblemap[a*mapsx+b] &D3DSTATUS_CLIPINTERSECTIONALL){continue;}
			
			matriisi->LoadIdentity();
			matriisi->TranslateLocal((float)b*8000*kerroin,0,(float)a*8000*kerroin);			
			matriisi->ScaleLocal(kerroin,kerroin,kerroin);
			drawfast(&mallit[0].malli[4]);//base
			drawfast(&mallit[1].malli[maps[a][b]]);//map
		}
	}


	
	//location of moped
			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,TRUE);
			m_pDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE    );
			m_pDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_SRCALPHA    );	
			m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,FALSE);	

			matriisi->LoadIdentity();		
			matriisi->TranslateLocal(mopot[0].x1*kerroin,100,mopot[0].z1*kerroin);
			matriisi->RotateYawPitchRollLocal(0,0,pi/2);				
			drawfast(&mallit[2].malli[6]);	
			

	//location of target
			int f;
		for (f=0; f<mopot[0].mission_arvottu.kohteita; f++){
			matriisi->LoadIdentity();
			if(mopot->mission_arvottu.kohdetyyppi==0)//character
			matriisi->TranslateLocal(ukko[mopot[0].mission_arvottu.kohde[f]].x*kerroin,100,ukko[mopot[0].mission_arvottu.kohde[f]].z*kerroin);			
			if(mopot->mission_arvottu.kohdetyyppi==1)//coordinates
			matriisi->TranslateLocal(mopot->mission_arvottu.kohdex[f]*kerroin,100,mopot->mission_arvottu.kohdez[f]*kerroin);			
			if(mopot->mission_arvottu.kohdetyyppi==2)//moped
			matriisi->TranslateLocal(mopot[mopot[0].mission_arvottu.kohde[f]].x1*kerroin,100,mopot[mopot[0].mission_arvottu.kohde[f]].z1*kerroin);			
			
			matriisi->RotateYawPitchRollLocal(0,0,pi/2);	
			//matriisi->ScaleLocal(0.4f,0.4f,0.4f);
			drawfast(&mallit[2].malli[0]);
		}

			m_pDevice->SetRenderState(D3DRENDERSTATE_ZENABLE,TRUE);
			m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);
		

			rendertext((int)(1024*0.03f),(int)(768*0.90f),0,"enter to continue");	//write	
			//rendertext((int)(1024*0.03f),(int)(768*0.90f+13),0,"esc to reject");		
			if(missionantovaihe==1){
				rendertext((int)(1024*0.03f),(int)(768*0.10f+13*0),50,mopot->mission_arvottu.rivi0);				
				strcpy(temprivi,"The pay is: ");
				itoa(mopot->mission_arvottu.palkka,rivi,10);
				strcat(temprivi,rivi);
				rendertext((int)(1024*0.03f),(int)(768*0.5f),50,temprivi);
			}
			if(missionantovaihe==0){
				rendertext((int)(1024*0.03f),(int)(768*0.10f+13*0),50,missioninfo[mopot->level]);		
			}

			
					
}

void arvo_mission(bikebase *mopot,int missionumero){ //randomize a mission. 
	
	int f;
	float kx,kz,distanssi;
	//.type  		alatyypit
	// 0= kill some one    	0= no time limit   	1=timelimit
	// 1= taxi			   

	

	// .target type
	// 0= person
	// 1= coordinates
	// 2= moped

	if(missionumero==-1)mopot->missionumero=randInt(0,missionlevel[mopot->level].missions);
	else mopot->missionumero=missionumero;
	mopot->mission_arvottu=missionlevel[mopot->level].mission[mopot->missionumero];
	//target is a character
	if(mopot->mission_arvottu.kohdetyyppi==0){
		for (f=0; f<mopot->mission_arvottu.kohteita; f++){
			mopot->mission_arvottu.kohde[f]=randInt(0,ukkoja);
			arvoukko(mopot->mission_arvottu.kohde[f]);
			ukko[mopot->mission_arvottu.kohde[f]].kuva=mopot->mission_arvottu.asiakas[f].kuva;
			ukko[mopot->mission_arvottu.kohde[f]].aseena=mopot->mission_arvottu.asiakas[f].aseena;
			ukko[mopot->mission_arvottu.kohde[f]].energia=mopot->mission_arvottu.asiakas[f].energia;
			ukko[mopot->mission_arvottu.kohde[f]].korkeus=mopot->mission_arvottu.asiakas[f].korkeus;
			ukko[mopot->mission_arvottu.kohde[f]].taktiikka=mopot->mission_arvottu.asiakas[f].taktiikka;
			ukko[mopot->mission_arvottu.kohde[f]].puoli=mopot->mission_arvottu.asiakas[f].puoli;
		}
	}

	//target is coordinates
	if(mopot->mission_arvottu.kohdetyyppi==1){		
			mopot->mission_arvottu.asiakas[0]=ukko[mopot->nearestukko];//characer becomes passanger			
		for (f=0; f<mopot->mission_arvottu.kohteita; f++){
			laskekoordinaatit(&mopot->mission_arvottu.kohdex[f],&mopot->mission_arvottu.kohdez[f]);//randomizes coordinates outside of houses		
		}
	}

	//target is moped
	if(mopot->mission_arvottu.kohdetyyppi==2){
		//mopoja=mopot->mission_arvottu.kohteita+1;
		for (f=0; f<mopot->mission_arvottu.kohteita; f++){
			//mopot->mission_arvottu.kohde=randInt(1,mopoja);
			mopot->mission_arvottu.kohde[f]=f+1;			
			arvomopo(mopot->mission_arvottu.kohde[f]);
			mopot[mopot->mission_arvottu.kohde[f]].mopona=mopot->mission_arvottu.asiakas[f].kuva;
			mopot[mopot->mission_arvottu.kohde[f]].ase[0]=mopot->mission_arvottu.asiakas[f].aseena;
			mopot[mopot->mission_arvottu.kohde[f]].energia=mopot->mission_arvottu.asiakas[f].energia;
			//mopot[mopot->mission_arvottu.kohde].taktiikka=mopot->mission_arvottu.asiakas.taktiikka;
			//mopot[mopot->mission_arvottu.kohde].puoli=mopot->mission_arvottu.asiakas.puoli;
		}
	}

	
	//timelimit
	mopot->mission_arvottu.aika=0;
	if(mopot->mission_arvottu.alatyyppi==1){	
		if(mopot->mission_arvottu.kohdetyyppi==0)//character
			{			
				kx=ukko[mopot->mission_arvottu.kohde[0]].x;				
				kz=ukko[mopot->mission_arvottu.kohde[0]].z;
			}				
		if(mopot->mission_arvottu.kohdetyyppi==1)//coordinates
			{
				kx=mopot->mission_arvottu.kohdex[0];
				kz=mopot->mission_arvottu.kohdez[0];
			}
		if(mopot->mission_arvottu.kohdetyyppi==2)//moped
			{			
				kx=mopot[mopot->mission_arvottu.kohde[0]].x1;				
				kz=mopot[mopot->mission_arvottu.kohde[0]].z1;
			}

		distanssi=sqrtf(sqr(kx-mopot->x1)+sqr(kz-mopot->z1));
		mopot->mission_arvottu.aika=randDouble((distanssi/1.7f),(distanssi/1.3f));
	}	
	
}

void laskekoordinaatit(float *xa,float *za){//calculate coordinates

	int a,b,c;
	bool osuma=false;
	float osumax,osumaz;
fa:
		
		*xa=randDouble(0,(float)mapsx*8000);
		*za=randDouble(0,(float)mapsz*8000);

		int mapx=(int)*xa/8000;
		int mapz=(int)*za/8000;
		

		a=maps[mapz][mapx];
		int wallhits=0;
		for (b=0; b<viivagroup[0].viivat[a].viivaa; b++){
				for (c=0; c<viivagroup[0].viivat[a].viiva[b].linjaa; c++){						
					if(linecollidesline(&osuma,&osumax,&osumaz,*xa-mapx*8000,*za-mapz*8000,*xa+10000-mapx*8000,*za+10000-mapz*8000,	viivagroup[0].viivat[a].viiva[b].piste[c].x1,viivagroup[0].viivat[a].viiva[b].piste[c].z1,viivagroup[0].viivat[a].viiva[b].piste[c].x2,viivagroup[0].viivat[a].viiva[b].piste[c].z2))
						wallhits=wallhits+1;
				}
		}
		if((float)wallhits/2*1000!=((int)(wallhits/2))*1000)
		goto fa;
		if(sqrtf(sqr(*xa-mopot[0].x1)+sqr(*za-mopot[0].z1))<10000)
		goto fa;


}

void laskemissiot(bikebase *mopot){ //calculate missions
	int q,f;
	bool kuollut=true;
	if(mopot->mission.suoritettu!=0) return;
	//kill some one
	if(mopot->mission.tyyppi==0){
		//remove dead ones from the list
		for (f=0; f<mopot->mission.kohteita; f++){
			if(mopot->mission.kohdetyyppi==0){
				if(ukko[mopot->mission.kohde[f]].kuole){
					for (q=f; q<mopot->mission.kohteita; q++){
						mopot->mission.kohde[q]=mopot->mission.kohde[q+1];
					}
					mopot->mission.kohteita=mopot->mission.kohteita-1;					
				}
			}
			if(mopot->mission.kohdetyyppi==2){
				if(mopot[mopot->mission.kohde[f]].pois){
					for (q=f; q<mopot->mission.kohteita; q++){
						mopot->mission.kohde[q]=mopot->mission.kohde[q+1];
					}
					mopot->mission.kohteita=mopot->mission.kohteita-1;					
				}
			}
		}
		//is everyone dead?
		for (f=0; f<mopot->mission.kohteita; f++){
			if(mopot->mission.kohdetyyppi==0) if(!ukko[mopot->mission.kohde[f]].kuole) kuollut=false;
			if(mopot->mission.kohdetyyppi==2) if(!mopot[mopot->mission.kohde[f]].pois) kuollut=false;
		}
		if(mopot->mission.alatyyppi==0){//no timelimit
			if(kuollut==true) mopot->mission.suoritettu=1;//character killed
		}
		if(mopot->mission.alatyyppi==1){//with timelimit
			mopot->mission.aika=mopot->mission.aika-elapsed*pelinopeus;
			if(mopot->mission.aika<0) mopot->mission.suoritettu=2;//mission failed
			if(kuollut==true) mopot->mission.suoritettu=1;//character killed
		}
	}


	//taxi
	if(mopot->mission.tyyppi==1){
		if(mopot->mission.alatyyppi==0){//no timelimit
			if(sqrtf(sqr(mopot->mission.kohdex[0]-mopot->x1)+sqr(mopot->mission.kohdez[0]-mopot->z1))<100)
				if(fabs(mopot[0].nopeus)<0.7f){
					for (f=0; f<mopot->mission.kohteita-1; f++){
						mopot->mission.kohdex[f]=mopot->mission.kohdex[f+1];
						mopot->mission.kohdez[f]=mopot->mission.kohdez[f+1];
					}
					mopot->mission.kohteita=mopot->mission.kohteita-1;
						if(mopot->mission.kohteita==0){
							mopot->mission.suoritettu=1;//we are there
							q=randInt(0,ukkoja);
							ukko[q]=mopot->mission.asiakas[0];
							ukko[q].x=mopot->x2;
							ukko[q].z=mopot->z2;
							ukko[q].nopeus=randDouble(0.02f,0.1f);
						}
				}
		}
		if(mopot->mission.alatyyppi==1){//with timelimit
			mopot->mission.aika=mopot->mission.aika-elapsed*pelinopeus;
			if(mopot->mission.aika<0) mopot->mission.suoritettu=2;//mission failed
			if(sqrtf(sqr(mopot->mission.kohdex[0]-mopot->x1)+sqr(mopot->mission.kohdez[0]-mopot->z1))<100)
				if(fabs(mopot[0].nopeus)<0.7f){
				mopot->mission.suoritettu=1;//we are there
				q=randInt(0,ukkoja);
				ukko[q]=mopot->mission.asiakas[0];
				ukko[q].x=mopot->x2;
				ukko[q].z=mopot->z2;
				ukko[q].nopeus=randDouble(0.02f,0.1f);
				}
		}
	}

	/*//if failed
	if(mopot->mission.suoritettu==2){
		mopot->rahat=mopot->rahat-100;
		if(mopot->rahat<0)mopot->rahat=0;
	}*/
	//if accomplished
	if(mopot->mission.suoritettu==1){
		//money is payed
		mopot->rahat=mopot->rahat+mopot->mission.palkka;
		//level up
		mopot->level=mopot->level+1;
		//read briefing
		missionantovaihe=0;
		//if there is no more missions
		if(missionlevel[mopot->level].missions==0){
			pelivaihe2=1;//game over
		}
	}	

}

void arvoukko(int q){//create random character

	int b,ampuva,a;
	int prosentti;

		for (a=0; a<100; a++)ukko[q].osuma[a]=false;
		ukko[q].korkeus=randDouble(0.9f,1.1f);
		ukko[q].menossa=1;
		ukko[q].menoajastin=0;
		ukko[q].kuole=false;
		ukko[q].pois=false;
		laskekoordinaatit(&ukko[q].x,&ukko[q].z);
		ukko[q].suunta=randDouble(-pi,pi);
		ukko[q].nopeus=randDouble(0.05f,0.1f);
		ukko[q].lx=0;
		ukko[q].rx=0;
		ukko[q].jalka=false;
		ukko[q].sektorix=(int)ukko[q].x/8000;
		ukko[q].sektoriz=(int)ukko[q].z/8000;
		moveparts(q);
			for (b=0; b<11; b++){
				ukko[q].ruumiinosa[b].gox=0;
				ukko[q].ruumiinosa[b].goy=0;
				ukko[q].ruumiinosa[b].goz=0;
			}

		//randomize character properties
		int a1=15;//character is at players side
		int a2=15;//enemy
		int a3=70;//passive
//ukko[q].kuva=7;
		prosentti=randInt(0,100);
		//own
		if((prosentti>=0)&&(prosentti<a1)){
			ukko[q].kuva=3;
			ukko[q].puoli=0;
			ukko[q].aseena=randInt(10,13);
			ukko[q].taktiikka=1;
			ukko[q].energia=randDouble(2.4f,3.3f);
		}
		//enemy
		if((prosentti>=a1)&&(prosentti<a1+a2)){
			ukko[q].kuva=8;
			ukko[q].puoli=2;
			ukko[q].aseena=randInt(10,13);
			ukko[q].taktiikka=0;
			ukko[q].energia=randDouble(1.4f,2.5f);
		}
		//passive
		if((prosentti>=a1+a2)&&(prosentti<a1+a2+a3)){
			ukko[q].kuva=randInt(0,2);
			
			if(ukko[q].kuva==0)ukko[q].kuva=7;
			if(ukko[q].kuva==1)ukko[q].kuva=10;

			ukko[q].puoli=1;
			//Randomly select does it have a gun or not.
			ukko[q].aseena=-1;
			ampuva=randInt(0,4);
			if(ampuva==0){
				ukko[q].aseena=randInt(10,13);
			}
			ukko[q].taktiikka=1;
			ukko[q].energia=randDouble(0.5f,1.7f);
		}

/*
		ukko[q].kuva=randInt(0,2);
		switch (ukko[q].kuva) 
			{
			case 0:{
				ukko[q].kuva=3;
				break;
				   }
			case 1:{
				ukko[q].kuva=7;
				break;
				   }
			}
*/			

}
	
void luemissiot(void){ //read missions

	FILE *fil;
	CHAR rivi[800];
	int q,f,level;
	
		for (q=0; q<10; q++){
		missionlevel[q].missions=0;
		}

		//load missions		
		fil = fopen("data/mission.dat","rt");

	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[0],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[1],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[2],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[3],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[4],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[5],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[6],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[7],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[8],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[9],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[10],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[11],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[12],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[13],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[14],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[15],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[16],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[17],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[18],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[19],rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missioninfo[20],rivi);
		
	stripped_fgets(rivi,sizeof(rivi),fil);
		level=atoi(rivi);
lue:
	stripped_fgets(rivi,sizeof(rivi),fil);
		missionlevel[level].mission[missionlevel[level].missions].tyyppi=atoi(rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		missionlevel[level].mission[missionlevel[level].missions].kohdetyyppi=atoi(rivi);	
	stripped_fgets(rivi,sizeof(rivi),fil);
		missionlevel[level].mission[missionlevel[level].missions].alatyyppi=atoi(rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		missionlevel[level].mission[missionlevel[level].missions].kohteita=atoi(rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		missionlevel[level].mission[missionlevel[level].missions].asiakas[0].kuva=atoi(rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		missionlevel[level].mission[missionlevel[level].missions].asiakas[0].aseena=atoi(rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		missionlevel[level].mission[missionlevel[level].missions].asiakas[0].energia=(float)atof(rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		missionlevel[level].mission[missionlevel[level].missions].asiakas[0].korkeus=(float)atof(rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		missionlevel[level].mission[missionlevel[level].missions].asiakas[0].taktiikka=atoi(rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		missionlevel[level].mission[missionlevel[level].missions].asiakas[0].puoli=atoi(rivi);		
	stripped_fgets(rivi,sizeof(rivi),fil);
		missionlevel[level].mission[missionlevel[level].missions].palkka=atoi(rivi);
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missionlevel[level].mission[missionlevel[level].missions].shortbriefing,rivi);		
	stripped_fgets(rivi,sizeof(rivi),fil);
		strcpy(missionlevel[level].mission[missionlevel[level].missions].rivi0,rivi);
	for (f=0; f<100; f++){
		missionlevel[level].mission[missionlevel[level].missions].asiakas[f]=missionlevel[level].mission[missionlevel[level].missions].asiakas[0];
	}

		missionlevel[level].missions=missionlevel[level].missions+1;
	
	//read next level, if it is 666666 file ends
	stripped_fgets(rivi,sizeof(rivi),fil);
		level=atoi(rivi);
		if(level!=666666)goto lue;

		fclose(fil);
}

void laskemopot(void){ //calculate mopeds
	int q,q2,d;
	float dq,temp1;
	int negaatio;
	int osumia;
	//if(mopoja==1)return;

	if(mopot->mission.suoritettu!=0) return;
	for (d=1; d<mopoja; d++){
		if(mopot[d].pois)continue;

		if(mopot[d].energia<0){mopot[d].pois=true;
					//smoke to air
					if(ase[1].savumaahan!=0)
						for (q=0; q<3; q++){	
							fromsmoke(1.0f,0.001f,true,3000,mopot[d].x1,60,mopot[d].z1,ase[1].savumaahan,randDouble(pi,-pi),randDouble(pi,-pi),randDouble(pi,-pi));
						}
					//explosion
					if(ase[1].pommi!=0){
						quake=3;
						for (q2=0; q2<100; q2++){
						shoot(-6667,-1,1,randDouble(100,300),mopot,3,mopot[d].x1,60,mopot[d].z1,randDouble(-pi,pi),randDouble(-pi,pi),randDouble(-pi,pi));
						}
						//for (q2=0; q2<1; q2++){
							fromsmoke(1.0f,0.01f,true,4000,mopot[d].x1,60,mopot[d].z1,3,0,0,0);							
						//}
					}
		}
		//if(mopot[d].pois==true) mopoja=1;//arvomopo(d);

		//angle towards player
		mopot[d].kulmamopoon=atan2f(mopot[0].z1-mopot[d].z1,mopot[0].x1-mopot[d].x1)+pi;

		//reset controls
		mopot[d].enter2=mopot[d].enter;
		mopot[d].esc2=mopot[d].esc;
		mopot[d].up2=mopot[d].up;
		mopot[d].down2=mopot[d].down;
		mopot[d].left2=mopot[d].left;
		mopot[d].right2=mopot[d].right;
		mopot[d].one2=mopot[d].one;
		mopot[d].two2=mopot[d].two;
		mopot[d].three2=mopot[d].three;
		mopot[d].four2=mopot[d].four;
		mopot[d].space2=mopot[d].space;	
		mopot[d].enter=false;
		mopot[d].esc=false;
		mopot[d].up=false;
		mopot[d].down=false;
		mopot[d].left=false;
		mopot[d].right=false;
		mopot[d].one=false;
		mopot[d].two=false;
		mopot[d].three=false;
		mopot[d].four=false;
		mopot[d].space=false;
		mopot[d].suuntatimer=mopot[d].suuntatimer+elapsed*pelinopeus;
		mopot[d].taktiikkatimer=mopot[d].taktiikkatimer+elapsed*pelinopeus;
		mopot[d].walltimer=mopot[d].walltimer-elapsed*pelinopeus;
		if(mopot[d].left2){mopot[d].left3=mopot[d].left3+1;if(mopot[d].right3>0)mopot[d].right3=mopot[d].right3-1;}
		if(mopot[d].right2){mopot[d].right3=mopot[d].right3+1;if(mopot[d].left3>0)mopot[d].left3=mopot[d].left3-1;}
		if(mopot[d].left3>30)mopot[d].left3=30;
		if(mopot[d].right3>30)mopot[d].right3=30;
		if(mopot[d].up2){mopot[d].up3=mopot[d].up3+1;if(mopot[d].up3>0)mopot[d].up3=mopot[d].up3-1;}
		if(mopot[d].down2){mopot[d].down3=mopot[d].down3+1;if(mopot[d].down3>0)mopot[d].down3=mopot[d].down3-1;}
		if(mopot[d].up3>30)mopot[d].up3=30;
		if(mopot[d].down3>30)mopot[d].down3=30;

	//Continue away from a wall if it has collided with it.
	if(mopot[d].walltimer>0){
			mopot[d].up=mopot[d].up2;
			mopot[d].down=mopot[d].down2;
			mopot[d].left=mopot[d].left2;
			mopot[d].right=mopot[d].right2;
	}
		
		//Artificial intelligence

	if(mopot[d].walltimer<0){
		//eager to use throttle
		mopot[d].up=true;

		/*if(mopot[d].distanssi<300){
			mopot[d].up=false;
			mopot[d].down=true;
		}*/
		


				//finds out is the bike at right or left side.
				dq=atan2f(mopot[d].z1-mopot[0].z1,mopot[d].x1-mopot[0].x1)+pi;
				temp1=mopot[d].suunta;
				//if(dq>pi){dq=dq-2*pi;mopot[d].suunta=mopot[d].suunta-2*pi;}
				//if(dq<pi){dq=dq+2*pi;mopot[d].suunta=mopot[d].suunta+2*pi;}
				if(mopot[d].suunta-dq>pi)temp1=temp1-pi*2;
				if(dq-mopot[d].suunta>pi)dq=dq-pi*2;
				
				if(mopot[d].up){
					negaatio=1;
					if (dq<temp1)
						negaatio=-1;
				}
				else{
					negaatio=-1;
					if (dq<temp1)
						negaatio=1;
				}

		//taktics			
		if(mopot[d].taktiikkatimer>2000){
			mopot[d].taktiikkatimer=0;
			mopot[d].taktiikka=randInt(0,2);
		}

		//use hand brake		
		if((fabs(mopot[d].suunta-dq)>0.4f)&&(mopot[d].down==false)&&(mopot[d].nopeus>2)){
			mopot[d].space=true;
		}
		if(mopot[d].kulmakeuliminen>0.2f){
			mopot[d].space=true;
		}
		
		/*//player is ahead
		if(fabs(mopot[d].suunta-dq)<0.1f){			
			mopot[d].one=true;
			//mopot[d].two=true;
			//if player near enough ahead do not use throttle
			if(mopot[d].distanssi<1500)
				mopot[d].up=false;
		}*/

		//Shoot
		if(fabs(mopot[d].suunta-dq)<1.2f)	
			mopot[d].one=true;

		

		//attack
		if(mopot[d].taktiikka==0)
		{
			if(fabs(mopot[d].suunta-dq)>0.05f){
						

			//when turned enough choose new direction
			if(mopot[d].suuntatimer>1000)
			{
				mopot[d].suuntatimer=0;
				if(negaatio==-1)
					mopot[d].right=true;
				if(negaatio==1)
					mopot[d].left=true;
			}
			else{
				mopot[d].right=mopot[d].right2;
				mopot[d].left=mopot[d].left2;
			}
			}
		}

		//escapes
		if(mopot[d].taktiikka==1){
			if(fabs(mopot[d].suunta-dq)>0.3f){
			//when turned enough choose new direction
			if(mopot[d].suuntatimer>2000)
			{
				mopot[d].suuntatimer=0;
				if(negaatio==1)
					mopot[d].right=true;
				if(negaatio==-1)
					mopot[d].left=true;
			}
			else{
				mopot[d].right=mopot[d].right2;
				mopot[d].left=mopot[d].left2;
			}
			}
		}
		
		osumia=0;
		//if cant get off the wall
		for (q=0; q<100; q++){
			if(mopot[d].osuma[q])
			osumia=osumia+1;
		}

		//if it is clearly in the wall
		if(mopot[d].osuma[0]){
			mopot[d].walltimer=(float)(osumia+20)*30;
			//if it was going straigth ahaed use reverse
			if(mopot[d].up3>mopot[d].down3){
				mopot[d].down=false;
				mopot[d].up=true;
			}
			//and viseversa
			if(mopot[d].up3<mopot[d].down3){
				mopot[d].down=true;
				mopot[d].up=false;
			}
			//do not go left
			if(mopot[d].left3>mopot[d].right3){
				mopot[d].suuntatimer=0;
				mopot[d].left=false;
				mopot[d].right=true;
			}
			//do not go rigth either
			if(mopot[d].left3<mopot[d].right3){
				mopot[d].suuntatimer=0;
				mopot[d].left=true;
				mopot[d].right=false;
			}			
		}

		
			if((osumia>90)&&(mopot[d].visible==false)){
				
				laskekoordinaatit(&mopot[d].x1,&mopot[d].z1);
			
			}

}

	
}	
}

void arvomopo(int d){ //randomize moped
	int a;

	mopot[d].etusuunta=0;
	mopot[d].ase[0]=0;
	mopot[d].ase[1]=0;
	mopot[d].ase[2]=0;
	mopot[d].ase[3]=0;
	mopot[d].timesparks=-1;
	mopot[d].mission.suoritettu=3;
	mopot[d].mopona=0;
	mopot[d].numero=d;
	mopot[d].energia=100;
	mopot[d].level=0;
	mopot[d].suunta=pi*0.25f;
	laskekoordinaatit(&mopot[d].x1,&mopot[d].z1);	
	mopot[d].x2=mopot[d].x1+sinf(mopot[d].suunta)*70;
	mopot[d].z2=mopot[d].z1+cosf(mopot[d].suunta)*70;	
	mopot[d].nopeus=0.01f;	
	mopot[d].sektorix=(int)mopot[d].x1/8000;
	mopot[d].sektoriz=(int)mopot[d].z1/8000;
	mopot[d].pois=false;
	for (a=0; a<100; a++)mopot[d].osuma[a]=false;
	mopot[d].suuntatimer=0;
	mopot[d].taktiikkatimer=0;
	mopot[d].visible=true;
	mopot[d].x3=mopot[d].x1;
	mopot[d].y3=mopot[d].y1;
	mopot[d].z3=mopot[d].z1;
	mopot[d].x4=mopot[d].x2;
	mopot[d].y4=mopot[d].y2;
	mopot[d].z4=mopot[d].z2;

}

void render_workshop(void){//render workshop
	RECT     rcSource, rcDest, loota;
	int a,b;
	int valittua,valittub,valittuc;
	char rivi[200],temprivi[200];
	float nop;
 
 
	
	pelinopeus=1;	

	//background picture
	rcSource.top = 0; 
	rcSource.left = 0;
	rcSource.bottom = 768; 
	rcSource.right = 1024; 
	rcDest.top = 0; 
	rcDest.left = 0;
	rcDest.bottom = SCREEN_HEIGHT; 
	rcDest.right = SCREEN_WIDTH;
 
	taka->Blt(&rcDest,
					kuvia[0],
					&rcSource,0,NULL);
	valittua=-2;
	valittub=-2;
	valittuc=-2;

	float hintataso=1.05f;
	//advantages and disadvantages
	for (a=0; a<4; a++){
		ase[mopot[0].ase[a]].hinta=(int)(sqr(ase[mopot[0].ase[a]].pampumanopeus+ase[mopot[0].ase[a]].pnopeus+ase[mopot[0].ase[a]].pvahinko+ase[mopot[0].ase[a]].haku*5)*hintataso);
		ase[mopot[0].ase[a]].hinta2=(int)(sqr(ase[mopot[0].ase[a]].pampumanopeus+ase[mopot[0].ase[a]].pnopeus+ase[mopot[0].ase[a]].pvahinko+ase[mopot[0].ase[a]].haku*5-1)*hintataso);
		ase[mopot[0].ase[a]].hintahaku=0;
		for (b=0; b<5; b++){
			ase[mopot[0].ase[a]].hintahaku=ase[mopot[0].ase[a]].hintahaku+(int)(sqr(ase[mopot[0].ase[a]].pampumanopeus+ase[mopot[0].ase[a]].pnopeus+ase[mopot[0].ase[a]].pvahinko+b)*hintataso);	
		}
		for (b=0; b<4; b++){
			
			//disadvantage
			rcSource.top = 0; 
			rcSource.left = 0;
			rcSource.bottom = 28; 
			rcSource.right = 28; 
			rcDest.top = (125+a*29)*SCREEN_HEIGHT/768; 
			rcDest.left = (228+b*180)*SCREEN_WIDTH/1024;
			rcDest.bottom = rcDest.top+28*SCREEN_HEIGHT/768; 
			rcDest.right = rcDest.left+28*SCREEN_WIDTH/1024;
			if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom))
			{
				valittua=a;
				valittub=b;
				valittuc=-1;
				if(mousestate.rgbButtons[0]){
				rcSource.top = 28; 
				rcSource.bottom = 56; 
				}
			} 
			taka->Blt(&rcDest,
							kuvia[2],
							&rcSource,NULL,NULL);


			//advantage
			rcSource.top = 0; 
			rcSource.left = 28;
			rcSource.bottom = 28; 
			rcSource.right = 56; 
			rcDest.top = (125+a*29)*SCREEN_HEIGHT/768; 
			rcDest.left = (228+b*180+71)*SCREEN_WIDTH/1024;
			rcDest.bottom = rcDest.top+28*SCREEN_HEIGHT/768; 
			rcDest.right = rcDest.left+28*SCREEN_WIDTH/1024;
			if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom))
			{
				valittua=a;
				valittub=b;
				valittuc=1;
				if(mousestate.rgbButtons[0]){
				rcSource.top = 28; 
				rcSource.bottom = 56; 
				} 
			} 
			taka->Blt(&rcDest,
							kuvia[2],
							&rcSource,NULL,NULL);

			switch (a) 
			{
					case 0:{
						itoa(ase[mopot[0].ase[b]].pvahinko,rivi,10);
						break;
					}
					case 1:{
						itoa(ase[mopot[0].ase[b]].pampumanopeus,rivi,10);
						break;
					}
					case 2:{
						itoa(ase[mopot[0].ase[b]].pnopeus,rivi,10);
						break;
					}
					case 3:{
						itoa(ase[mopot[0].ase[b]].haku*5,rivi,10);
						break;
					}
			}

			//gun points
			//strcpy(rivi,":");
			//itoa((int)mopot[0].mission.aika/1000,rivi,10);
			//strcat(rivi,temprivi);
			rendertext((212+b*180+60),(125+a*29+10),0,rivi);
						
		}
		//price
		itoa((int)ase[mopot[0].ase[a]].hinta,rivi,10);
		rendertext((212+a*180+50),(125+4*29+10),0,rivi);
	}
	//repair moped 
	if((mopot[0].korjaamolla2==false)&&(mopot[0].korjaamolla==true)){
		korjaussumma=int(100-mopot[0].energia)*((mopot[0].level+2)/2);
		if(korjaussumma>mopot[0].rahat)korjaussumma=mopot[0].rahat;
		mopot[0].energia=mopot[0].energia+korjaussumma/((mopot[0].level+2)/2);
		mopot[0].rahat=mopot[0].rahat-korjaussumma;
	}

	//money
		itoa((int)mopot[0].rahat,rivi,10);
		rendertext((200),(125+5*29+10),0,rivi);

	//moped fixed
		if(korjaussumma>0){
			strcpy(rivi,"bike repaired for ");
			itoa((int)korjaussumma,temprivi,10);
			strcat(rivi,temprivi);
			rendertext((190),(76),0,rivi);
		}

	//key is pressed. //translator note: could be understood as "a brat is f*cked". 
	if ((mousestate2.rgbButtons[0])&&(!mousestate.rgbButtons[0]))
	if ((valittua!=-2)&&(valittub!=-2)&&(valittuc!=-2)){
		switch (valittua) 
		{
					case 0:{
						if(valittuc==1)
						if(ase[mopot[0].ase[valittub]].pvahinko<10)
						if(mopot[0].rahat>=ase[mopot[0].ase[valittub]].hinta)
						{
							SndObjPlay(voices[18], NULL,options[1]&&SOUNDS_LOADED);
							ase[mopot[0].ase[valittub]].pvahinko=ase[mopot[0].ase[valittub]].pvahinko+1;
							mopot[0].rahat=mopot[0].rahat-ase[mopot[0].ase[valittub]].hinta;
						}
						if(valittuc==-1)
						if(ase[mopot[0].ase[valittub]].pvahinko>1)
						{
							SndObjPlay(voices[19], NULL,options[1]&&SOUNDS_LOADED);
							ase[mopot[0].ase[valittub]].pvahinko=ase[mopot[0].ase[valittub]].pvahinko-1;
							mopot[0].rahat=mopot[0].rahat+ase[mopot[0].ase[valittub]].hinta2;
						}
						break;
					}
					case 1:{
						if(valittuc==1)
						if(ase[mopot[0].ase[valittub]].pampumanopeus<10)
						if(mopot[0].rahat>=ase[mopot[0].ase[valittub]].hinta)
						{
							SndObjPlay(voices[18], NULL,options[1]&&SOUNDS_LOADED);
							ase[mopot[0].ase[valittub]].pampumanopeus=ase[mopot[0].ase[valittub]].pampumanopeus+1;
							mopot[0].rahat=mopot[0].rahat-ase[mopot[0].ase[valittub]].hinta;
						}
						if(valittuc==-1)
						if(ase[mopot[0].ase[valittub]].pampumanopeus>1)
						{
							SndObjPlay(voices[19], NULL,options[1]&&SOUNDS_LOADED);
							ase[mopot[0].ase[valittub]].pampumanopeus=ase[mopot[0].ase[valittub]].pampumanopeus-1;
							mopot[0].rahat=mopot[0].rahat+ase[mopot[0].ase[valittub]].hinta2;
						}
						break;
					}
					case 2:{
						if(valittuc==1)
						if(ase[mopot[0].ase[valittub]].pnopeus<10)
						if(mopot[0].rahat>=ase[mopot[0].ase[valittub]].hinta)
						{
							SndObjPlay(voices[18], NULL,options[1]&&SOUNDS_LOADED);
							ase[mopot[0].ase[valittub]].pnopeus=ase[mopot[0].ase[valittub]].pnopeus+1;
							mopot[0].rahat=mopot[0].rahat-ase[mopot[0].ase[valittub]].hinta;
						}
						if(valittuc==-1)
						if(ase[mopot[0].ase[valittub]].pnopeus>1)
						{
							SndObjPlay(voices[19], NULL,options[1]&&SOUNDS_LOADED);
							ase[mopot[0].ase[valittub]].pnopeus=ase[mopot[0].ase[valittub]].pnopeus-1;
							mopot[0].rahat=mopot[0].rahat+ase[mopot[0].ase[valittub]].hinta2;
						}
						break;
					}
					case 3:{
						if(valittuc==1)
						if(ase[mopot[0].ase[valittub]].haku==false)
						if(mopot[0].rahat>=ase[mopot[0].ase[valittub]].hintahaku)
						{
							SndObjPlay(voices[18], NULL,options[1]&&SOUNDS_LOADED);
							ase[mopot[0].ase[valittub]].haku=true;
							mopot[0].rahat=mopot[0].rahat-ase[mopot[0].ase[valittub]].hintahaku;
						}
						if(valittuc==-1)
						if(ase[mopot[0].ase[valittub]].haku==true)
						{
							SndObjPlay(voices[19], NULL,options[1]&&SOUNDS_LOADED);
							ase[mopot[0].ase[valittub]].haku=false;
							mopot[0].rahat=mopot[0].rahat+ase[mopot[0].ase[valittub]].hintahaku;
						}
						break;
					}
		}	
	}
	//exit
			rcSource.top = 0; 
			rcSource.left = 0;
			rcSource.bottom = 40; 
			rcSource.right = 80; 
			rcDest.top = (700)*SCREEN_HEIGHT/768; 
			rcDest.left = (900)*SCREEN_WIDTH/1024;
			rcDest.bottom = rcDest.top+40*SCREEN_HEIGHT/768; 
			rcDest.right = rcDest.left+80*SCREEN_WIDTH/1024;
			if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom))
			{
				//key is pressed countinuosly
				if (mousestate.rgbButtons[0]){
					rcSource.top = 40; 
					rcSource.bottom = 80; 
				}
				//key is pressed one time
				if ((mousestate2.rgbButtons[0])&&(!mousestate.rgbButtons[0])){
					SndObjPlay(voices[1], DSBPLAY_LOOPING,options[1]&&SOUNDS_LOADED);
					pelivaihe=0;
					pelivaihe2=0;
				}
			}
				taka->Blt(&rcDest,
							kuvia[3],
							&rcSource,NULL,NULL);

	//load
			rcSource.top = 0; 
			rcSource.left = 160;
			rcSource.bottom = 40; 
			rcSource.right = 240; 
			rcDest.top = (40)*SCREEN_HEIGHT/768; 
			rcDest.left = (800)*SCREEN_WIDTH/1024;
			rcDest.bottom = rcDest.top+40*SCREEN_HEIGHT/768; 
			rcDest.right = rcDest.left+80*SCREEN_WIDTH/1024;
			if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom))
			{
				//key is pressed countinuosly
				if (mousestate.rgbButtons[0]){
					rcSource.top = 40; 
					rcSource.bottom = 80; 
				}
				//key is pressed one time
				if ((mousestate2.rgbButtons[0])&&(!mousestate.rgbButtons[0])){
					readsaves();//read saves
					pelivaihe=4;
					pelivaihe2=1;
					pelivaihe_oli=2;
				}
			}
				taka->Blt(&rcDest,
							kuvia[3],
							&rcSource,NULL,NULL);

	//save
			rcSource.top = 0; 
			rcSource.left = 80;
			rcSource.bottom = 40; 
			rcSource.right = 160; 
			rcDest.top = (40)*SCREEN_HEIGHT/768; 
			rcDest.left = (900)*SCREEN_WIDTH/1024;
			rcDest.bottom = rcDest.top+40*SCREEN_HEIGHT/768; 
			rcDest.right = rcDest.left+80*SCREEN_WIDTH/1024;
			if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom))
			{
				//key is pressed continuosly
				if (mousestate.rgbButtons[0]){
					rcSource.top = 40; 
					rcSource.bottom = 80; 
				}
				//key is pressed one time
				if ((mousestate2.rgbButtons[0])&&(!mousestate.rgbButtons[0])){
					readsaves();//read saves
					pelivaihe2=2;
					pelivaihe=4;
					tallennettu=false;
					pelivaihe_oli=2;
				}
			}
				taka->Blt(&rcDest,
							kuvia[3],
							&rcSource,NULL,NULL);

	//mouse
		loota.left  =0;
		loota.right =25;
		loota.top   =0;
		loota.bottom=25;

		if(int(mousex)+11>SCREEN_WIDTH)
			loota.right=SCREEN_WIDTH-int(mousex);
		if(int(mousey)+19>SCREEN_HEIGHT)
			loota.bottom=SCREEN_HEIGHT-int(mousey);

		taka->BltFast(
				int(mousex)
				,int(mousey)
				,kuvia[1],
				&loota,
				DDBLTFAST_SRCCOLORKEY);

	//calculate weapon properties
	for (b=0; b<4; b++){
		ase[mopot[0].ase[b]].vahinko=ase[mopot[0].ase[b]].pvahinko*0.1f+(ase[mopot[0].ase[b]].pvahinko-1)*0.7f;		
		ase[mopot[0].ase[b]].nopeus=ase[mopot[0].ase[b]].pnopeus*3.7f+(ase[mopot[0].ase[b]].pnopeus-1)*1.44f;
		ase[mopot[0].ase[b]].hauleja=1;	
		ase[mopot[0].ase[b]].tyyppi=0;
		ase[mopot[0].ase[b]].hajonta=0.01f+ase[mopot[0].ase[b]].pampumanopeus*0.01f;
		nop=(float)ase[mopot[0].ase[b]].pampumanopeus;		
		if((ase[mopot[0].ase[b]].pampumanopeus>5)&&(ase[mopot[0].ase[b]].pampumanopeus)<8){ase[mopot[0].ase[b]].tyyppi=2; nop=2;ase[mopot[0].ase[b]].hauleja=(int)(7*(ase[mopot[0].ase[b]].pampumanopeus-3));ase[mopot[0].ase[b]].vahinko=ase[mopot[0].ase[b]].vahinko/20;ase[mopot[0].ase[b]].hajonta=ase[mopot[0].ase[b]].hajonta*4;}
		if(ase[mopot[0].ase[b]].pampumanopeus>7)ase[mopot[0].ase[b]].tyyppi=1;
		
		//if((ase[mopot[0].ase[b]].pampumanopeus>3)&&(ase[mopot[0].ase[b]].pampumanopeus)<8){ase[b].tyyppi=2; nop=(float)ase[mopot[0].ase[b]].pampumanopeus/(5*(8-ase[mopot[0].ase[b]].pampumanopeus));ase[mopot[0].ase[b]].hauleja=(int)(5*(8-ase[mopot[0].ase[b]].pampumanopeus));}
		ase[mopot[0].ase[b]].ampumanopeus=(int)(710+78-nop*78);

		ase[mopot[0].ase[b]].savumaahan=0;
		if(ase[mopot[0].ase[b]].haku){
			//ase[mopot[0].ase[b]].kimmokkeita=0;
			ase[mopot[0].ase[b]].savumaahan=2;
			ase[mopot[0].ase[b]].savuvana=10;
		}
		else {
			ase[mopot[0].ase[b]].kimmokkeita=ase[mopot[0].ase[b]].pvahinko;
			ase[mopot[0].ase[b]].savuvana=0;
		}
		ase[mopot[0].ase[b]].paino=ase[mopot[0].ase[b]].pvahinko*0.00001f;
		ase[mopot[0].ase[b]].pommi=0;
		ase[mopot[0].ase[b]].monttukuva=0;
		if(ase[mopot[0].ase[b]].pvahinko>6){
			ase[mopot[0].ase[b]].tyyppi=3;
			ase[mopot[0].ase[b]].kimmokkeita=0;
			ase[mopot[0].ase[b]].pommi=ase[mopot[0].ase[b]].pvahinko-6;
			ase[mopot[0].ase[b]].savumaahan=2;
			ase[mopot[0].ase[b]].savukesto=1000;
			ase[mopot[0].ase[b]].monttukuva=1;
		}
		ase[mopot[0].ase[b]].savukoko=ase[mopot[0].ase[b]].pvahinko*0.1f;


	}

	
	mopot[0].korjaamolla2=mopot[0].korjaamolla;


}

void readkey_game(void){
	
	//mopep control
	mopot[0].enter2=mopot[0].enter;
	mopot[0].esc2=mopot[0].esc;
	mopot[0].up2=mopot[0].up;
	mopot[0].down2=mopot[0].down;
	mopot[0].left2=mopot[0].left;
	mopot[0].right2=mopot[0].right;
	mopot[0].one2=mopot[0].one;
	mopot[0].two2=mopot[0].two;
	mopot[0].three2=mopot[0].three;
	mopot[0].four2=mopot[0].four;
	mopot[0].space2=mopot[0].space;
	mapmode2=mapmode;

	mopot[0].enter=false;
	mopot[0].esc=false;
	mopot[0].up=false;
	mopot[0].down=false;
	mopot[0].left=false;
	mopot[0].right=false;
	mopot[0].one=false;
	mopot[0].two=false;
	mopot[0].three=false;
	mopot[0].four=false;
	mopot[0].space=false;


	if (KEYDOWN(buffer, DIK_RETURN))
		mopot[0].enter=true;
	if (KEYDOWN(buffer, DIK_ESCAPE))
		mopot[0].esc=true;
	/*if (KEYDOWN(buffer, DIK_UP))
		mopot[0].up=true;	
	if (KEYDOWN(buffer, DIK_DOWN))
		mopot[0].down=true;
	if (KEYDOWN(buffer, DIK_LEFT))
		mopot[0].left=true;
	if (KEYDOWN(buffer, DIK_RIGHT))
		mopot[0].right=true;
	if (KEYDOWN(buffer, DIK_1))
		mopot[0].one=true;
	if (KEYDOWN(buffer, DIK_2))
		mopot[0].two=true;
	if (KEYDOWN(buffer, DIK_3))
		mopot[0].three=true;
	if (KEYDOWN(buffer, DIK_4))
		mopot[0].four=true;
	if (KEYDOWN(buffer, DIK_SPACE))
		mopot[0].space=true;
	*/
	if (buffer[key[1]]& 0x80)
		mopot[0].up=true;
	if (buffer[key[2]]& 0x80)
		mopot[0].down=true;
	if (buffer[key[3]]& 0x80)
		mopot[0].left=true;
	if (buffer[key[4]]& 0x80)
		mopot[0].right=true;
	if (buffer[key[5]]& 0x80)
		mopot[0].one=true;
	if (buffer[key[6]]& 0x80)
		mopot[0].two=true;
	if (buffer[key[7]]& 0x80)
		mopot[0].three=true;
	if (buffer[key[8]]& 0x80)
		mopot[0].four=true;
	if (buffer[key[11]]& 0x80)
		mopot[0].space=true;

				//skip demo by pressing enter
				if (!KEYDOWN(buffer,  DIK_RETURN )&&KEYDOWN(buffer2,  DIK_RETURN)){					
					if(pelivaihe2==3)pelivaihe2=4;
					else if(pelivaihe2==4)pelivaihe2=0;
					if(pelivaihe2==5){pelivaihe2=0; pelivaihe=4;}
					if(pelivaihe2==1){pelivaihe2=0; pelivaihe=4;}
							
				}		

				//pause by pressing esc
				if (!KEYDOWN(buffer,  DIK_ESCAPE )&&KEYDOWN(buffer2,  DIK_ESCAPE))
					{
					if (pelivaihe2==0) pelivaihe2=2;
					else if (pelivaihe2==2) pelivaihe2=0;
					if (pelivaihe2==3) pelivaihe2=0;
					if (pelivaihe2==4) pelivaihe2=0;
					}

				//exit
				if (!KEYDOWN(buffer,  DIK_F9 )&&KEYDOWN(buffer2,  DIK_F9))
					{
					pelivaihe=4;
					pelivaihe2=0;
					//SendMessage( hWnd, WM_CLOSE, 0, 0 );
					}
				
				//slow the game down
				if (buffer[key[9]]& 0x80)
					{
					 if(pelinopeus>0.2f)
						 pelinopeus=pelinopeus-0.5f*0.01f*elapsed;
					}
				else
					if(pelinopeus<0.9f+0.1f*vaikeustaso)
						pelinopeus=pelinopeus+0.5f*0.01f*elapsed;

					if(pelinopeus>0.9f+0.1f*vaikeustaso)
						pelinopeus=0.9f+0.1f*vaikeustaso;						
					if(pelinopeus<0.2f)
						pelinopeus=0.2f;
				
				//changching camera mode
				if (buffer[key[10]]& 0x80)
				if (!(buffer2[key[10]]& 0x80))
				{					
					if(!mapmode)mapmode=true;
					else mapmode=false;
				}
				
				//controlling camera
				float MOTION_SPEED=0.1f;//camera speed
				if (KEYDOWN(buffer,  DIK_END))
					{
						dy=dy-MOTION_SPEED*elapsed;
						if (dy<=-5) dy=-5;
					}
				if (KEYDOWN(buffer,  DIK_HOME))
					{
						dy=dy+MOTION_SPEED*elapsed;			
						if (dy>=43) dy=43;
					}
				if (KEYDOWN(buffer,  DIK_DELETE))
					{
						dx=dx-MOTION_SPEED*elapsed;
					}
				if (KEYDOWN(buffer,  DIK_NEXT))
					{
						dx=dx+MOTION_SPEED*elapsed;
					}



				
					//when getting in menu play music
				if(pelivaihe==4){
					
					SndObjStop(voices[1]);
				}
}

void readsaves(void){ // read saves
	int		i;
	char	name[256];
	FILE	*f;

	for (i=0 ; i<10 ; i++)
	{
		//strcpy (m_filenames[i], "--- Unused Slot ---");
		strcpy (m_filenames[i], " -Unused-");
		loadable[i] = false;
		sprintf (name, "save/s%i.sav", i);
		f = fopen (name, "r");
		if (!f)
			continue;
		stripped_fgets(name,sizeof(name),f);
		strcpy (m_filenames[i], name);
		loadable[i] = true;
		stripped_fgets(name,sizeof(name),f);		
		kirjaintan[i]=atoi(name);
		fclose (f);
	}
}
void game_load(void){//load game
	FILE *fil;
		int q,d,a,b;
		char temprivi[300];
		char tallennusrivi[300];
		float kx,kz;

		if(!loadable[tallennuspaikka]) return;//exit if not right
		
		itoa(tallennuspaikka,temprivi,10);
		strcpy(tallennusrivi,"save/s");
		strcat(tallennusrivi,temprivi);
		strcat(tallennusrivi,".sav");

		
		fil = fopen(tallennusrivi,"rb");

	

		game_new();
		korjaussumma=0;
		mopot[0].korjaamolla2=false;
		mopot[0].korjaamolla=true;
		pelivaihe2=0;
		pelivaihe=2;
		

		//stripped_fgets(temprivi,sizeof(temprivi),fil);//temprivi
		//fgets(temprivi,sizeof(temprivi),fil);nextmatsi=atoi(temprivi);

		//name
		fgets(temprivi,sizeof(temprivi),fil);
		fgets(temprivi,sizeof(temprivi),fil);

		//diffucultylevel	
		fgets(temprivi,sizeof(temprivi),fil); vaikeustaso=atoi(temprivi);
			//weapons change accordin to diffucultylevel
			q=10;
			//police gun 0 pistol	
			if(vaikeustaso==0) ase[q].vahinko=3.5f;
			if(vaikeustaso==1) ase[q].vahinko=4.5f;
			if(vaikeustaso==2) ase[q].vahinko=5.5f;
			ase[q].tyyppi=0;

			q=11;
			//police gun 1 machinegun
			if(vaikeustaso==0) ase[q].vahinko=0.5f;
			if(vaikeustaso==1) ase[q].vahinko=0.8f;
			if(vaikeustaso==2) ase[q].vahinko=1.1f;
			ase[q].tyyppi=1;

			q=12;
			//police gun 2 missile
			if(vaikeustaso==0) ase[q].vahinko=5;
			if(vaikeustaso==1) ase[q].vahinko=7;
			if(vaikeustaso==2) ase[q].vahinko=10;
			ase[q].tyyppi=3;

		//field
		fgets(temprivi,sizeof(temprivi),fil); mapsx=atoi(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); mapsz=atoi(temprivi);	
		for (a=0; a<mapsz; a++){
			for (b=0; b<mapsx; b++){
				fgets(temprivi,sizeof(temprivi),fil); maps[a][b]=atoi(temprivi);												
			}
		}
		//dont randomize characters until fiel is randomized
		ukkoja=1000;
		mopot[0].x1=-10000;//moped is not noticed while randomizing character locations
		mopot[0].z1=-10000;
		for (q=0; q<1000; q++){
			arvoukko(q);	
		}
		//frontwheel coordinates
		fgets(temprivi,sizeof(temprivi),fil); mopot[0].x1=(float)atof(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); mopot[0].z1=(float)atof(temprivi);
		
		//rearwheel
		fgets(temprivi,sizeof(temprivi),fil); mopot[0].x2=(float)atof(temprivi);
		fgets(temprivi,sizeof(temprivi),fil); mopot[0].z2=(float)atof(temprivi);
		//direction
		fgets(temprivi,sizeof(temprivi),fil); mopot[0].suunta=(float)atof(temprivi);
		//ammount of money
		fgets(temprivi,sizeof(temprivi),fil); mopot[0].rahat=atoi(temprivi);
		//weapon properties
		for (q=0; q<4; q++){
			fgets(temprivi,sizeof(temprivi),fil); ase[mopot[0].ase[q]].pvahinko=atoi(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); ase[mopot[0].ase[q]].pnopeus=atoi(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); ase[mopot[0].ase[q]].pampumanopeus=atoi(temprivi);
			fgets(temprivi,sizeof(temprivi),fil);
			if(atoi(temprivi)==0) ase[mopot[0].ase[q]].haku=false;
			else ase[mopot[0].ase[q]].haku=true;
		}
		//energy
		fgets(temprivi,sizeof(temprivi),fil); mopot[0].energia=(float)atof(temprivi);
		//what level missions are given
		fgets(temprivi,sizeof(temprivi),fil); mopot[0].level=atoi(temprivi);
		//what mission from this level has been given
		fgets(temprivi,sizeof(temprivi),fil); mopot[0].missionumero=atoi(temprivi);
	//mission
		arvo_mission(&mopot[0],mopot[0].missionumero);		
		mopot[0].mission=mopot[0].mission_arvottu;
		//how many similiar targets

		fgets(temprivi,sizeof(temprivi),fil); mopot[0].mission.kohteita=atoi(temprivi);		
		//targets coordinates
		for (q=0; q<mopot[0].mission.kohteita; q++){
			fgets(temprivi,sizeof(temprivi),fil); kx=(float)atof(temprivi);
			fgets(temprivi,sizeof(temprivi),fil); kz=(float)atof(temprivi);
			if(mopot[0].mission.kohdetyyppi==0)//character
			{			
				ukko[mopot[0].mission.kohde[q]].x=kx;				
				ukko[mopot[0].mission.kohde[q]].z=kz;
			}				
			if(mopot[0].mission.kohdetyyppi==1)//coordinates
			{
				mopot[0].mission.kohdex[q]=kx;
				mopot[0].mission.kohdez[q]=kz;
			}	
			if(mopot[0].mission.kohdetyyppi==2)//moped
			{
				mopot[mopot[0].mission.kohde[q]].x1=kx;
				mopot[mopot[0].mission.kohde[q]].z1=kz;
			}
		}
		//is it accomplished
		fgets(temprivi,sizeof(temprivi),fil); mopot[0].mission.suoritettu=atoi(temprivi);		
		//time
		fgets(temprivi,sizeof(temprivi),fil); mopot[0].mission.aika=(float)atof(temprivi);
	
	//customer
		arvoukko(10);
		mopot[0].mission.asiakas[0]=ukko[10];
		//what picture on character
		fgets(temprivi,sizeof(temprivi),fil); mopot[0].mission.asiakas[0].kuva=atoi(temprivi);
		//energy
		fgets(temprivi,sizeof(temprivi),fil); mopot[0].mission.asiakas[0].energia=(float)atof(temprivi);		

		fclose(fil);

		for (d=0; d<mopoja; d++){
			if(mopot[d].pois)continue;
			aja(&mopot[d]);
		}


}
void game_save(void){//save game
	
		FILE *fil;
		int q,a,b;
		tallennettu=true;
		char temprivi[300];
		char tallennusrivi[300];
		float kx,kz;

		itoa(tallennuspaikka,temprivi,10);
		strcpy(tallennusrivi,"save/s");
		strcat(tallennusrivi,temprivi);
		strcat(tallennusrivi,".sav");

		korjaussumma=0;

		
		fil = fopen(tallennusrivi,"wb");

		if(kirjaintanimessa==0)
		strcpy(temprivi,"no name");
		else 
		strcpy(temprivi,savenimi);

		//name
		fprintf(fil, "%s\n", temprivi);
		fprintf(fil, "%d\n", kirjaintanimessa);
		//diffyculty
		fprintf(fil, "%d\n", vaikeustaso);
		//field
		fprintf(fil, "%d\n", mapsx);
		fprintf(fil, "%d\n", mapsz);		
		for (a=0; a<mapsz; a++){
			for (b=0; b<mapsx; b++){
				fprintf(fil, "%d\n", maps[a][b]);								
			}
		}
		//frontwheel coordinates
		fprintf(fil, "%f\n", mopot[0].x1);
		fprintf(fil, "%f\n", mopot[0].z1);
		//rearwheel
		fprintf(fil, "%f\n", mopot[0].x2);
		fprintf(fil, "%f\n", mopot[0].z2);		
		//direction
		fprintf(fil, "%f\n", mopot[0].suunta);
		//ammount of money
		fprintf(fil, "%d\n", mopot[0].rahat);
		//gun properties
		for (q=0; q<4; q++){
			fprintf(fil, "%d\n", ase[mopot[0].ase[q]].pvahinko);
			fprintf(fil, "%d\n", ase[mopot[0].ase[q]].pnopeus);
			fprintf(fil, "%d\n", ase[mopot[0].ase[q]].pampumanopeus);
			fprintf(fil, "%d\n", ase[mopot[0].ase[q]].haku);
		}
		//energy
		fprintf(fil, "%f\n", mopot[0].energia);
		//level of missions that will be given. 
		fprintf(fil, "%d\n", mopot[0].level);
		//what mission from this level has been given
		fprintf(fil, "%d\n", mopot[0].missionumero);
	//mission
		//ammount of similiar targets
		fprintf(fil, "%d\n", mopot[0].mission.kohteita);
		//targets coordinates
		for (q=0; q<mopot[0].mission.kohteita; q++){			
			if(mopot[0].mission.kohdetyyppi==0)//characters
			{			
				kx=ukko[mopot[0].mission.kohde[q]].x;				
				kz=ukko[mopot[0].mission.kohde[q]].z;
			}				
			if(mopot[0].mission.kohdetyyppi==1)//coordinates
			{
				kx=mopot[0].mission.kohdex[q];
				kz=mopot[0].mission.kohdez[q];
			}	
			if(mopot[0].mission.kohdetyyppi==2)//moped
			{
				kx=mopot[mopot[0].mission.kohde[q]].x1;
				kz=mopot[mopot[0].mission.kohde[q]].z1;
			}
			fprintf(fil, "%f\n", kx);
			fprintf(fil, "%f\n", kz);
		}
		//is it accomplished?
		fprintf(fil, "%d\n", mopot[0].mission.suoritettu);
		//time
		fprintf(fil, "%f\n", mopot[0].mission.aika);
	//customer
		//what picture on character
		fprintf(fil, "%d\n", mopot[0].mission.asiakas[0].kuva);
		//energy
		fprintf(fil, "%f\n", mopot[0].mission.asiakas[0].energia);

/*		float x1,z1;//front wheel coordinates
		float x2,z2;//rear wheel
		int rahat;//ammount of money left
		float energia;//energy
		int level;//level of missions that will be given.
		int missionumero;//what mission from this level has been given

		int kohteita;//ammount of similiar targets
		int kohde[100];//possible target (kill some one?)		
		float kohdex[100], kohdez[100];//targets coordinates (go to location x?)
		float aika;//time		
		int suoritettu;//0=not accomplished 1=accomplished2=failed 3=there is no mission		
		

		//person asiakas[100];//as a passanger in a taxi
			int kuva;//what picture is on character
			int aseena;//wich weapon does it have -1=no weapon
			float energia;//energy
			int taktiikka;//what will it do. 0=pursues 1=walks normally 2=escapes
			int puoli;//0=friend 1=passive 2=enemy
*/
		
		fclose(fil);
}
void render_menu(void){//renders the menu
	RECT     rcSource, rcDest, loota;
	char menuteksti[40][256];
	char rivi[200],temprivi[200];
	int tex,tey;
	int q;
	int space;

	pelinopeus=1;
	quake=0;
	m_pDevice->LightEnable(0, FALSE);
	m_pDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xFFFFFFFF);
	m_pDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE ,FALSE);


	//m_pDevice->GetRenderTarget(&taka);




	//cusor
	kursori=kursori-elapsed;
	if(kursori<-500)kursori=500;
					
	 
	//wallpaper
	rcSource.top = 0; 
	rcSource.left = 0;
	rcSource.bottom = 768; 
	rcSource.right = 1024; 
	rcDest.top = 0; 
	rcDest.left = 0;
	rcDest.bottom = SCREEN_HEIGHT; 
	rcDest.right = SCREEN_WIDTH;
 
	taka->Blt(&rcDest,
					kuvia[4],
					&rcSource,0  ,NULL);

	rendertext(340,738,0,"game version 1.21");

	
	if(pelivaihe2==0){//headmenu
		space=40;
		strcpy(menuteksti[0],"New Game");
		strcpy(menuteksti[1],"Load Game");
		strcpy(menuteksti[2],"Options");
		strcpy(menuteksti[3],"Exit");
	}
	if((pelivaihe2==1)||(pelivaihe2==2)||(pelivaihe2==3)){//load and save
		space=20;
		strcpy(menuteksti[0]," ");
		strcpy(menuteksti[11]," ");
		strcpy(menuteksti[12],"Back");
		for (q=0; q<10; q++){
			strcpy(menuteksti[q+1],m_filenames[q]);
			//menuteksti[q]=savenimi[q]
		}
	}
	if(pelivaihe2==4){//options
		space=20;
		strcpy(menuteksti[0]," ");		
		strcpy(menuteksti[1],"Sounds");
		if(options[1]&&!SOUNDS_ON)strcpy(menuteksti[1],"Sounds  unable to play");//if sounds cannot be played
		strcpy(menuteksti[2]," ");
		strcpy(menuteksti[3]," ");
		strcpy(menuteksti[4]," ");
		strcpy(menuteksti[5]," ");
		strcpy(menuteksti[6]," ");
		strcpy(menuteksti[7]," ");
		strcpy(menuteksti[8]," ");
		strcpy(menuteksti[9]," ");
		strcpy(menuteksti[10]," ");
		strcpy(menuteksti[11],"Set Keys");
		strcpy(menuteksti[12],"Back");
	}
	if(pelivaihe2==5){//new game
		space=40;
		strcpy(menuteksti[0],"Easy");
		strcpy(menuteksti[1],"Normal");
		strcpy(menuteksti[2],"Hard");
		strcpy(menuteksti[3],"Back");
	}
	if(pelivaihe2==6){//set keys
		space=20;
		 strcpy(menuteksti[0]," ");		
		 strcpy(menuteksti[1],"Up           ");		
		 strcpy(menuteksti[2],"Down         ");
		 strcpy(menuteksti[3],"Left         ");
		 strcpy(menuteksti[4],"Right        ");
		 strcpy(menuteksti[5],"Shoot 1      ");
		 strcpy(menuteksti[6],"Shoot 2      ");
		 strcpy(menuteksti[7],"Shoot 3      ");
		 strcpy(menuteksti[8],"Shoot 4      ");
		 strcpy(menuteksti[9],"Slow´Mo      ");
		strcpy(menuteksti[10],"Chance View  ");
		strcpy(menuteksti[11],"Hand Brake   ");
		strcpy(menuteksti[12],"Back");
		for (q=1; q<12; q++){
			itoa(key[q],temprivi,10);
			strcat(menuteksti[q],temprivi);
		}
	}



					tex=270;tey=220+0*space;
					if(pelivaihe2==1)strcpy(rivi,"Load");
					if(pelivaihe2==2){
					if(!tallennettu)
						strcpy(rivi,"Save");
					else
						strcpy(rivi,"Game saved");
					}
					if(pelivaihe2==3){
						strcpy(rivi,"Enter a name");	
						strcpy(menuteksti[menuvalittu],savenimi);
					}
					if(pelivaihe2==4)strcpy(rivi,"Options");
					if(pelivaihe2==6)strcpy(rivi,"Set Keys");

					if((pelivaihe2==1)||(pelivaihe2==2)||(pelivaihe2==3)||(pelivaihe2==4)||(pelivaihe2==6))
					rendertext((int)(tex),(int)(tey),0,rivi);
	
	

	
	//menuvalittu=-1;

	for (q=0; q<menuja[pelivaihe2]; q++){
		rendertext(210,220+q*space,0,menuteksti[q]);
		rcDest.top = (210+q*space)*SCREEN_HEIGHT/768; 
		rcDest.left = (205)*SCREEN_WIDTH/1024;
		rcDest.bottom = rcDest.top+space*SCREEN_HEIGHT/768; 
		rcDest.right = rcDest.left+230*SCREEN_WIDTH/1024;		
		//thing selected while saving cannot be changed.
		if((pelivaihe2!=3)&&((pelivaihe2!=6)||(valittu==false)))
		if((mousex<rcDest.right)&&(mousex>rcDest.left)&&(mousey>rcDest.top)&&(mousey<rcDest.bottom)){					
			menuvalittu=q;
		}
		
		if((q==menuvalittu)&&((pelivaihe2!=4)||(q>10)))
			rendertext(210,220+q*space,0,menuteksti[q]);
		if(((q<10)&&(q>0))&&((pelivaihe2==4)&&(options[q])))
			rendertext(210,220+q*space,0,menuteksti[q]);
		
	//cursor
		if((menuvalittu<11)&&(menuvalittu>0))
		{
				if((pelivaihe2==3)&&(menuvalittu==q)&&(kursori<0)&&(kirjaintanimessa<49))
				rendertext(int(210+(kirjaintanimessa)*12.5f),(220+q*space),0,":");
		}
	}

	



	//render moped
			//set camera to its place
			float kamerax1=0;
			float kameray1=1.6f*100;
			float kameraz1=2000;
			float kamerax2=kamerax1;
			float kameray2=kameray1-1.05f*1000;
			float kameraz2=0;

			m_View = ViewMatrix(D3DVECTOR(kamerax1,kameray1,kameraz1), D3DVECTOR(kamerax2,kameray2,kameraz2), D3DVECTOR(0,1,0), 0);				
			m_pDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &m_View);


			lamppu[1].valo.dltType = D3DLIGHT_POINT;	
			lamppu[1].valo.dcvDiffuse.r = 1.0f;    
			lamppu[1].valo.dcvDiffuse.g = 1.0f;
			lamppu[1].valo.dcvDiffuse.b = 1.0f;    
			lamppu[1].valo.dcvAmbient.r = 1.0f;
			lamppu[1].valo.dcvAmbient.g = 1.0f;    
			lamppu[1].valo.dcvAmbient.b = 1.0f;
			lamppu[1].valo.dcvSpecular.r = 1.0f;    
			lamppu[1].valo.dcvSpecular.g = 1.0f;
			lamppu[1].valo.dcvSpecular.b = 1.0f;
			lamppu[1].valo.dvDirection=1.0f; 
			lamppu[1].valo.dvPosition.x = 0;
			lamppu[1].valo.dvPosition.y = 0;  
			lamppu[1].valo.dvPosition.z = 0;
			lamppu[1].valo.dvAttenuation0 = 0.5f;
			lamppu[1].valo.dvAttenuation1=0.0f;	
			lamppu[1].valo.dvAttenuation2=0.0f;
			lamppu[1].valo.dvRange = 500;
			m_pDevice->LightEnable(1, TRUE);	
			m_pDevice->SetLight(1, &lamppu[1].valo);


		int mopokuva=6;
		int d=7;
		mopot[d].x2=0;
		mopot[d].y2=0;
		mopot[d].z2=0;
		mopot[d].suunta=mopot[d].suunta+0.002f*elapsed*pelinopeus;
		mopot[d].kulmakallistus=0;
		mopot[d].kulmakeuliminen=0;


		if(mopokuva==0){
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(mopot[d].x2,mopot[d].y2,mopot[d].z2);			
			matriisi->RotateYawPitchRollLocal(-mopot[d].suunta,mopot[d].kulmakallistus,mopot[d].kulmakeuliminen);
			drawfast(&mallit[mopokuva].malli[0]);
		}
		if(mopokuva==6){
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(mopot[d].x2,mopot[d].y2+1.5f,mopot[d].z2);			
			matriisi->RotateYawPitchRollLocal(-mopot[d].suunta,mopot[d].kulmakallistus,mopot[d].kulmakeuliminen);
			drawfast(&mallit[mopokuva].malli[0]);
		}
		if(mopokuva==9){
			matriisi->LoadIdentity();
			matriisi->TranslateLocal(mopot[d].x2,mopot[d].y2+1.5f,mopot[d].z2);			
			matriisi->RotateYawPitchRollLocal(-mopot[d].suunta,mopot[d].kulmakallistus,mopot[d].kulmakeuliminen);
			drawfast(&mallit[mopokuva].malli[0]);
		}

	if(mopokuva==0){
		//rear wheel
		matriisi->Push();
		matriisi->TranslateLocal(0,20,0);
		matriisi->RotateYawPitchRollLocal(0,0,mopot[d].kulmaetu);			
		drawfast(&mallit[mopokuva].malli[3]);	
		matriisi->Pop();
		//front side
		matriisi->TranslateLocal(70,0,0);
		//matriisi->RotateYawPitchRollLocal(-mopot[d].suunta,0,0);
		matriisi->RotateYawPitchRollLocal(-mopot[d].etusuunta,0,0);	
		drawfast(&mallit[mopokuva].malli[2]);
		//front wheel
		matriisi->TranslateLocal(40,20,0);
		matriisi->RotateYawPitchRollLocal(0,0,mopot[d].kulmaetu);		
		drawfast(&mallit[mopokuva].malli[3]);
	}
	if(mopokuva==6){
		//rear wheel
		matriisi->Push();
		matriisi->TranslateLocal(0,20,0);
		matriisi->RotateYawPitchRollLocal(0,0,mopot[d].kulmaetu);			
		drawfast(&mallit[mopokuva].malli[2]);	
		matriisi->Pop();
		//front side
		matriisi->TranslateLocal(79,0,0);
		matriisi->RotateYawPitchRollLocal(-mopot[d].etusuunta,0,0);	
		drawfast(&mallit[mopokuva].malli[1]);
		//front wheel
		matriisi->TranslateLocal(40,20,0);
		matriisi->RotateYawPitchRollLocal(0,0,mopot[d].kulmaetu);		
		drawfast(&mallit[mopokuva].malli[2]);
	}
	if(mopokuva==9){
		//rear wheel
		matriisi->Push();
		matriisi->TranslateLocal(0,20,0);
		matriisi->RotateYawPitchRollLocal(0,0,mopot[d].kulmaetu);			
		drawfast(&mallit[mopokuva].malli[2]);	
		matriisi->Pop();
		//front side
		matriisi->TranslateLocal(79,0,0);
		matriisi->RotateYawPitchRollLocal(-mopot[d].etusuunta,0,0);	
		drawfast(&mallit[mopokuva].malli[1]);
		//front wheel
		matriisi->TranslateLocal(40,20,0);
		matriisi->RotateYawPitchRollLocal(0,0,mopot[d].kulmaetu);		
		drawfast(&mallit[mopokuva].malli[2]);
	}

	m_pDevice->LightEnable(1, FALSE);
	



	//mouse
		loota.left  =0;
		loota.right =25;
		loota.top   =0;
		loota.bottom=25;

		if(int(mousex)+11>SCREEN_WIDTH)
			loota.right=SCREEN_WIDTH-int(mousex);
		if(int(mousey)+19>SCREEN_HEIGHT)
			loota.bottom=SCREEN_HEIGHT-int(mousey);

		taka->BltFast(
				int(mousex)
				,int(mousey)
				,kuvia[1],
				&loota,
				DDBLTFAST_SRCCOLORKEY);

	
}

void game_new(void){ //new game

	int a,b,d,q;
	float nop;

	
	
	SndObjPlay(voices[1], DSBPLAY_LOOPING,options[1]&&SOUNDS_LOADED);
	

	q=6;
	ase[q].kuva=0;//moped gun 0
	ase[q].nopeus=45;
	ase[q].hajonta=0.2f;
	ase[q].ampumanopeus=711;
	ase[q].monttukuva=0;
	ase[q].panoskuva=0;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.00001f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=2;
	ase[q].vahinko=0.1f;
	ase[q].haku=false;
	ase[q].pvahinko=2;
	ase[q].pnopeus=2;
	ase[q].pampumanopeus=2;
	ase[q].hauleja=1;

	q=7;
	ase[q].kuva=0;//moped gun1
	ase[q].nopeus=45;
	ase[q].hajonta=0.2f;
	ase[q].ampumanopeus=711;
	ase[q].monttukuva=0;
	ase[q].panoskuva=0;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.00001f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=2;
	ase[q].vahinko=0.1f;
	ase[q].haku=false;
	ase[q].pvahinko=2;
	ase[q].pnopeus=2;
	ase[q].pampumanopeus=2;
	ase[q].hauleja=1;

	q=8;
	ase[q].kuva=0;//moped gun2
	ase[q].nopeus=45;
	ase[q].hajonta=0.2f;
	ase[q].ampumanopeus=711;
	ase[q].monttukuva=0;
	ase[q].panoskuva=0;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.00001f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=2;
	ase[q].vahinko=0.1f;
	ase[q].haku=false;
	ase[q].pvahinko=2;
	ase[q].pnopeus=2;
	ase[q].pampumanopeus=2;
	ase[q].hauleja=1;

	q=9;
	ase[q].kuva=0;//moped gun3
	ase[q].nopeus=45;
	ase[q].hajonta=0.2f;
	ase[q].ampumanopeus=711;
	ase[q].monttukuva=0;
	ase[q].panoskuva=0;
	ase[q].savumaahan=0;
	ase[q].savukesto=5000;
	ase[q].paino=0.00001f;
	ase[q].pommi=0;
	ase[q].savuvana=0;
	ase[q].kimmokkeita=2;
	ase[q].vahinko=0.1f;
	ase[q].haku=false;
	ase[q].pvahinko=2;
	ase[q].pnopeus=2;
	ase[q].pampumanopeus=2;
	ase[q].hauleja=1;
	

	
	//ramdomize map //before randomizing characters
	mapsz=12;
	mapsx=10;
	for (a=0; a<mapsz; a++){
		for (b=0; b<mapsx; b++){
			maps[a][b]=4;
			while((maps[a][b]==4)|(maps[a][b]==5))
			maps[a][b]=randInt(0,objnum1);			
		}
	}
	
	//atleast one house is a workshop
	maps[randInt(1,mapsz-1)][randInt(1,mapsx-1)]=6;

	//headquartes location //NOTE! this may have same coordinates as the only workshop that is generated.
	majax=randInt(1,mapsz-1);
	majaz=randInt(1,mapsx-1);
	maps[majax][majaz]=5;
	
	
	//map edges
	for (a=0; a<mapsz; a++) {maps[a][0]=4;maps[a][mapsx-1]=4;}
	for (a=0; a<mapsx; a++) {maps[0][a]=4;maps[mapsz-1][a]=4;}
	

	


	//generate characters
	ukkoja=1000;
	mopot[0].x1=-10000;//moped is not noticed while generating these places
	mopot[0].z1=-10000;
	for (q=0; q<1000; q++){
		arvoukko(q);	
	}



	//initialize mopeds
	mopoja=10;
	initializemopeds();
	for (q=1; q<100; q++){
		mopot[q].pois=true;
	}

	quake=0;//at the beginning there will be no erthquakes
	missionantovaihe=0;//read introduction
	mapmode=true;
	dx=0;//camera
	dy=13;//camera
	luoteja=0;//at the beginning there will be not a single bullet
	savuja=0;	
	

	

	pelinopeus=1.0f;
	pelivaihe=0;
	
	for (d=0; d<mopoja; d++){
		if(mopot[d].pois)continue;
		aja(&mopot[d]);
	}

	for (q=0; q<maksimiluoteja; q++){
		luoti[q].poista=true;
	}
	for (q=0; q<maksimisavuja; q++){
		savu[q].pois=true;
	}

	//calculate gun properties
	for (b=0; b<12; b++){
		if((b==2)||(b==3)||(b==4))continue;//blood and sparks are not changed
		ase[b].vahinko=ase[b].pvahinko*0.1f+(ase[b].pvahinko-1)*0.7f;
		ase[b].nopeus=ase[b].pnopeus*3.7f+(ase[b].pnopeus-1)*1.44f;
		ase[b].hauleja=1;
		ase[b].tyyppi=0;
		nop=(float)ase[b].pampumanopeus;		
		//if((ase[b].pampumanopeus>3)&&(ase[b].pampumanopeus)<8){ase[b].tyyppi=2; nop=(float)ase[b].pampumanopeus/(5*(8-ase[b].pampumanopeus));ase[b].hauleja=(int)(5*(8-ase[b].pampumanopeus));}
		if((ase[b].pampumanopeus>5)&&(ase[b].pampumanopeus)<8){ase[b].tyyppi=2; nop=2;ase[b].hauleja=(int)(7*(ase[b].pampumanopeus-3));ase[b].vahinko=ase[b].vahinko/20;ase[b].hajonta=ase[b].hajonta*4;}
		if(ase[b].pampumanopeus>7)ase[b].tyyppi=1;

		ase[b].ampumanopeus=(int)(710+78-nop*78);
		ase[b].hajonta=0.01f+ase[b].pampumanopeus*0.01f;
		ase[b].savumaahan=0;
		if(ase[b].haku){
			//ase[b].kimmokkeita=0;
			ase[b].savumaahan=2;
			ase[b].savuvana=10;
		}
		else {
			ase[b].kimmokkeita=ase[b].pvahinko;
			ase[b].savuvana=0;
		}
		ase[b].paino=ase[b].pvahinko*0.00001f;
		ase[b].pommi=0;
		ase[b].monttukuva=0;
		if(ase[b].pvahinko>6){
			ase[b].tyyppi=3;
			ase[b].kimmokkeita=0;
			ase[b].pommi=ase[b].pvahinko-6;
			ase[b].savumaahan=2;
			ase[b].savukesto=1000;
			ase[b].monttukuva=1;
		}
		ase[b].savukoko=ase[b].pvahinko*0.1f;
	}

	//guns changed by diffyculty level
	q=10;
	//police gun 0 pistol	
	if(vaikeustaso==0) ase[q].vahinko=3.5f;
	if(vaikeustaso==1) ase[q].vahinko=4.5f;
	if(vaikeustaso==2) ase[q].vahinko=5.5f;
	ase[q].tyyppi=0;

	q=11;
	//police gun 1 machinegun
	if(vaikeustaso==0) ase[q].vahinko=0.5f;
	if(vaikeustaso==1) ase[q].vahinko=0.8f;
	if(vaikeustaso==2) ase[q].vahinko=1.1f;
	ase[q].tyyppi=1;

	q=12;
	//police gun 2 missile	
	if(vaikeustaso==0) ase[q].vahinko=5;
	if(vaikeustaso==1) ase[q].vahinko=7;
	if(vaikeustaso==2) ase[q].vahinko=10;
	ase[q].tyyppi=3;



	//light bulb is connected
	m_pDevice->LightEnable(0, TRUE);

	//render one screen before beginning demo
	pelivaihe2=0;
	render_game();	
	pelivaihe2=3;

	

}
void sounds_start(void){

	//sounds
	if((!options[1])&&(!options[2])){return;}

	//if((options[1])||(options[2]))
		if(!SOUNDS_LOADED){
			if(DirectSoundCreate(NULL, &lpDS, NULL)!=DS_OK){SOUNDS_ON=false;return;}
			
		}
	if(SOUNDS_ON){
		if(!SOUNDS_LOADED){
			IDirectSound_SetCooperativeLevel( lpDS,hWnd, DSSCL_PRIORITY);
			
			/*
			DSBUFFERDESC dsBD = {0};			
			dsBD.dwSize = sizeof(dsBD);
			dsBD.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2;
			
 
			IDirectSound_CreateSoundBuffer(lpDS,&dsBD,&pDSB,NULL);
			*/
		}
			
		if((options[1])&&(!SOUNDS_LOADED)){
			voices[0]=SndObjCreate(lpDS, "#140", 1);//menu1 //remember SAMPLE_NUMBER
			voices[1]=SndObjCreate(lpDS, "#145", 1);//motor
			voices[2]=SndObjCreate(lpDS, "#146", 4);//pistol
			voices[3]=SndObjCreate(lpDS, "#147", 3);//bazooka
			voices[4]=SndObjCreate(lpDS, "#148", 2);//shotgun
			voices[5]=SndObjCreate(lpDS, "#149", 5);//machinegun
			voices[6]=SndObjCreate(lpDS, "#150", 1);//wall1
			voices[7]=SndObjCreate(lpDS, "#151", 1);//wall2
			voices[8]=SndObjCreate(lpDS, "#152", 2);//explosion
			voices[9]=SndObjCreate(lpDS, "#153", 2);//bounce1
			voices[10]=SndObjCreate(lpDS, "#154", 2);//bounce2
			voices[11]=SndObjCreate(lpDS, "#155", 2);//bounce3
			voices[12]=SndObjCreate(lpDS, "#156", 2);//bounce4
			voices[13]=SndObjCreate(lpDS, "#157", 2);//die0
			voices[14]=SndObjCreate(lpDS, "#158", 2);//die1
			voices[15]=SndObjCreate(lpDS, "#159", 2);//die2
			voices[16]=SndObjCreate(lpDS, "#160", 2);//die3
			voices[17]=SndObjCreate(lpDS, "#161", 2);//die4
			voices[18]=SndObjCreate(lpDS, "#162", 2);//upgrade
			voices[19]=SndObjCreate(lpDS, "#163", 2);//downgrade
			/*voices[1]=SndObjCreate(lpDS, "#143", 1);
			voices[2]=SndObjCreate(lpDS, "#144", 1);
			voices[3]=SndObjCreate(lpDS, "#145", 1);
			voices[4]=SndObjCreate(lpDS, "#146", 1);//meat
			voices[5]=SndObjCreate(lpDS, "#147", 1);
			voices[6]=SndObjCreate(lpDS, "#148", 1);
			voices[7]=SndObjCreate(lpDS, "#149", 1);
			voices[8]=SndObjCreate(lpDS, "#150", 1);
			voices[9]=SndObjCreate(lpDS, "#151", 2);//cloth
			voices[10]=SndObjCreate(lpDS, "#152", 1);
			voices[11]=SndObjCreate(lpDS, "#153", 1);//menu1
			voices[12]=SndObjCreate(lpDS, "#154", 1);//aah
			voices[13]=SndObjCreate(lpDS, "#155", 1);//yohe
			voices[14]=SndObjCreate(lpDS, "#156", 2);//walk1
			voices[15]=SndObjCreate(lpDS, "#157", 2);//walk2
			voices[16]=SndObjCreate(lpDS, "#158", 2);//walk3*/
			SAMPLE_NUMBER=2;
			SOUNDS_LOADED=true;
		}
		
		
	}
	
	}

void cfg_save(void){
		FILE *fil;
		int q;
		
		fil = fopen("cfg.cfg","wt");
		for (q=0; q<10; q++){
			fprintf(fil, "%d\n", options[q]);
		}
		for (q=0; q<13; q++){
			fprintf(fil, "%d\n", key[q]);
		}

		
		fclose(fil);
		if(options[1]&&!SOUNDS_LOADED)sounds_start();
}

void cfg_load(void){
		FILE *fil;
		int q,b;
		char temprivi[300];

		
		fil = fopen("cfg.cfg","rt");
		
		for (q=0; q<10; q++){
			fgets(temprivi,sizeof(temprivi),fil);b=atoi(temprivi);
			if(b==0)options[q]=false;
			else options[q]=true;
		}
		for (q=0; q<13; q++){
			fgets(temprivi,sizeof(temprivi),fil);key[q]=atoi(temprivi);			
		}

		fclose(fil);

		//SOUNDS_ON=options[1];

}
void playsound(int samplenumero,float volume,float paikkax,float paikkaz){ //play a sound
	if(soundtimer[samplenumero]<40)return;
	if(!(options[1]&&SOUNDS_LOADED))return;

	float distanssi=sqrtf(sqr(paikkax-mopot[0].x1)+sqr(paikkaz-mopot[0].z1));
	if(distanssi<10000)
	{
		//finds out is the bike at rigth or left side
				float dq=atan2f(mopot[0].z1-paikkaz,mopot[0].x1-paikkax)+pi;
				float temp1=mopot[0].suunta;
				if(mopot[0].suunta-dq>pi)temp1=temp1-pi*2;
				if(dq-mopot[0].suunta>pi)dq=dq-pi*2;
				int negaatio=1;
				if (dq<temp1)
						negaatio=-1;
				
				/*if(mopot[0].up){
					negaatio=1;
					if (dq<temp1)
						negaatio=-1;
				}
				else{
					negaatio=-1;
					if (dq<temp1)
						negaatio=1;
				}*/

		//float voluumi=-(distanssi*distanssi*0.0001f-10000)/10000-(1-volume);
		float voluumi=(10000-distanssi)/10000-(1-volume);
		soundtimer[samplenumero]=0;
		SndObjPlay(voices[samplenumero], NULL,options[1]&&SOUNDS_LOADED);	
		svolume(voices[samplenumero],(int)((1-voluumi)*(-6000-DSBVOLUME_MAX)), options[1]&&SOUNDS_LOADED);				
		//DSBPLAY_LOOPING   DSBVOLUME_MIN
		float pan=(float)(negaatio/10000*distanssi);
		SndObjSetPan(voices[samplenumero],pan);
		

	}
}
void clearzbuffer(void){
	//if(!options[3]){
		m_pDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER , 0x00000000, 1, 0 );
	/*}
	else{	
		DDBLTFX ddbltfx;	
		memset(&ddbltfx, 0, sizeof(ddbltfx));
		ddbltfx.dwSize = sizeof(DDBLTFX);
		ddbltfx.dwFillDepth=0x00FFFFFF;
		zpuskuri->Blt(NULL,NULL,NULL,DDBLT_DEPTHFILL,&ddbltfx);
	}*/

}
