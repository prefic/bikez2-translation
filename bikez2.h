#pragma once



#include <windows.h>
#include "resource.h"
#define D3D_OVERLOADS
#include <windowsx.h>
#include <mmsystem.h>
#include <ddraw.h>
#include <d3d.h>
#include <d3dx.h>
#include <dinput.h>
#include <dsound.h>
#include <stdio.h>
#include "dsutil.h"
#include "func.h"



#pragma comment(lib, "d3dx.lib")
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib,"dinput8.lib")

/*
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

	*/

	struct ukontekstuurit {//character textures
		int osa[4];		
	};

	struct vvertex {
				D3DVECTOR position;
				D3DVECTOR normal;
				float     u, v;//, w;   
			};

	struct pvertex {
				D3DVECTOR position;
				float     u, v;   
			};

	struct esine//object
	{
		vvertex *kolmijako;
		INT vert;
	};


	struct objekt 
	{
		INT textuuri;//material
		INT textuuri2;//number of texture
		INT matsku;//skin 0, steel 1, cloth 2, sword 3
		D3DVECTOR upleft,downright;//size
		esine loota;//object box
		float x,y,z;
		float rx,ry,rz;

	};

	struct obj
	{
		BOOL mirror;
		INT count;
		objekt *sisus;
		float x,y,z;
		float rx,ry,rz;
		float swordpointx,swordpointy,swordpointz;
		D3DXMATRIX sijainti;
	};

	struct kuvat//pictures
	{
		obj *malli;
	};

	struct ruumiinosan_koordinaatit//body part coordinates
	{
		float x,y,z;
		float rx,ry,rz;
		float gox,goy,goz;//Does it fly
	};

	struct person
	{
		int kuva;//Picture in character
		float kulmamopoon;//angle to player
		float distanssi;//distance from player
		float x,z,y;
		float x2,z2;//x and z were
		float suunta;//direction
		float nopeus;//speed
		bool jalka;//wich leg
		float lx,rx;//left and rigth leg
		int sektorix,sektoriz;//in wich sector it is *8000
		int jaosx,jaosz;//in wich section *400
		bool kuole;//call for dying animation
		bool pois;//character completely away
		ruumiinosan_koordinaatit ruumiinosa[11];//bodypart_coordinates bodypart
		int aseena;//wich weapon? -1=no weapon
		float asetime;//gun timer
		float energia;//energy
		int taktiikka;//What person does. 0=attacks 1=walks normally 2=escapes
		int menossa;//wich direction it is going 1=forward -1=backward
		float menoajastin;//timer for expense
		int puoli;//0=own 1=passive 2=enemy
		bool visible;//visible or not.
		float korkeus;//What size it is
		bool osuma[100];//has it collided with walls lately
	};

	struct missio
	{
		int tyyppi;//mission type (kill a character / go to place x)
		int alatyyppi;//mission subtype (kill within a timelimit)
		int kohdetyyppi;//target 0=character 1=coordinates 2=moped
		int kohde[100];//possible target (kill a character?)
		person asiakas[100];//taxi ride
		float kohdex[100], kohdez[100];//targets coordinates (go to place x?)
		float aika;//time		
		int suoritettu;//0=not accomplished 1=accomplished 2=lost 3=there is no mission
		//int suoritettu2;//performed value on last frame
		int palkka;//bounty from the mission
		char shortbriefing[100];//short briefing
		char rivi0[800];//mission briefing
		int kohteita;//Ammount of similiar targets
	};

	struct missiovarasto//mission reservoir
	{
		missio mission[20];
		int missions;//Number of mission in a level
	};

	struct bikebase
	{		
		float savuaika;//Timer of exhaustgasses
		int numero;//player 1 or 2
		int ase[4];//Wich gun is where
		float asetime[4];//timer of guns
		bool enter,esc,up,down,left,right,one,two,three,four,space;//keys
		bool enter2,esc2,up2,down2,left2,right2,one2,two2,three2,four2,space2;//keys on last frame		
		float x1,y1,z1;//front wheel coordinates
		float x2,y2,z2;//rear wheel
		float x3,y3,z3;//old front wheel coordinates
		float x4,y4,z4;//old rear wheel	
		float x5,y5,z5;//front wheel front side
		float x6,y6,z6;//rear wheel rear side
		float etusuunta;//front wheel direction
		float nopeus, suunta;		//speed, direction
		float kulmaetu;//Rotation of wheels in angles
		float kulmakeuliminen;//Angle of wheelie
		float kulmakallistus;//tilting of the bike
		float timesparks;//sparks doesnt appear too often
		int nearestukko;//Nearest character
		missio mission;//What mission is on
		missio mission_arvottu;//random mission 
		int missionumero;//What mission is given from the level
		int rahat;//ammount of money
		int mopona;//What kind of moped
		int sektorix,sektoriz;//In wich sector it is
		int valittuukko;//what character is aimed at -3=no-one
		float energia;//energy
		int level;//level of the given mission 
		bool osuma[100];//has it collided with walls lately
		float suuntatimer;//For artificial intelligence: how long it is gone to same direction
		float taktiikkatimer;//For artificial intelligence: tactic timer
		int taktiikka;//0=attack 1=escape
		bool visible;//Is in visible on the screen
		bool pois;//get rid of moped
		float distanssi;//distance from player
		float kulmamopoon;//angle to player
		bool suuliekki;//Muzzleflare
		bool korjaamolla,korjaamolla2;//Is it now at depot. Or has it been lately at depot
		D3DXMATRIX piippu;//where is the barrel of gun
		float walltimer;//How long its been since it hit wall
		float turntime;//how long its turned
		int left3;//have it turned left lately
		int right3;//have it turned right lately
		int up3;
		int down3;
	};

	struct dot
	{
		float x1,y1,z1;//start point
		float x2,y2,z2;//end point
	};

	struct linja//route or a line
	{
		int linjaa;
		dot *piste;
	};
	
	struct linjat//routes
	{
		int viivaa;//line
		linja *viiva;
	};

	struct linjagroup//route group
	{
		int grouppia;
		linjat *viivat;
	};
	
	struct panos
	{
		D3DXVECTOR3 paikkavanha;//place old
		D3DXVECTOR3 paikka;//place
		D3DXVECTOR3 suunta;//direction
		float q,w,e;//Angle of bullet
		int aseesta;//from gun
		bool poista;//delete
		float savuvana;//How much time for making smoketrail
		int sektorix[2],sektoriz[2];//in wich sector it is
		//int jaosx,jaosz;//in wich section it is *800
		float aika;//time
		float nopeus;//bullet speed
		int kenen;//whos bullet it is// positive=mopeds -1=character
		int kuka;//which character shot it (prevents suicides)
		float distanssi;//distance from the player
		int kohde;//-6667=no-one, negatives-1 are mopeds, positives are characters
	};

	struct weapon
	{

		float savukoko;//Size of smoke cloud
		float vahinko;//damage
		float hajonta;//dispersion
		int kuva;//what does this gun look like?
		int panoskuva;//bullet picture
		int monttukuva;//hole in wall -1 = empty
		int savumaahan;//Is a hole in wall filled with smoke?
		int pommi;//Size of explosion
		float nopeus;//speed
		int ampumanopeus;//rate of fire
		float savukesto;//the smoke lasts
		float paino;//bullet weigth
		float savuvana;//how often is smoke trail made? 
		int kimmokkeita;//how many times it bounces from walls;
		bool haku;//is it homing
		int pvahinko,pnopeus,pampumanopeus,hinta,hinta2,hintahaku;//related to peddling //pdamage,pspeed,prateoffire,price,price2,pricesearch
		int hauleja;//how many bullets from one shot
		int tyyppi;//gun type 0=pistol 1=machinegun 2=shotgun 3=rocketlauncher 4=no sound
	};

	struct smoke
	{
		D3DXVECTOR3 paikka;//place
		int tyyppi;//place
		float q,w,e;//smoke angle
		int kuva;//subpicture 0 or 1
		float aika;//how much time
		float cos,sin,up;//for the angle
		float rotate;
		float koko;//what size it is?
		float suurenee;//How much it grows
		bool pois;//off
	};
	
	/*struct monttu
	{
		D3DVECTOR position;		
		float     u, v;

	};*/

	struct light
	{
		bool on;
		D3DLIGHT7 valo;	//light
		float aika;//how much timeleft
	};

	

	
BOOL lataa(char nimi[200],obj *kohde,BOOL mirror,BOOL miekkakala);//load... swordfish
BOOL lataawall(char nimi[200],linjagroup *kohde,BOOL mirror);//loadwall
BOOL lataatext();//loadtext
void init(void);
bool createscreen(void);
bool Render(void);
bool luekuvat(void);//read pictures
void CleanUp(void);//destroys stuff
BOOL draw(obj *tavara);
void poistaobj(obj *kohde, int indeksi);//delete object
bool initkeyb(void);
bool deinitkeyb(void);
void luekeyb(void);//readkeyb
void aja(bikebase *mopot);//driving mopeds
void alustamopot(void);//initializing mopeds
void laskeosumat(void);//calculate collisions
void ammu(int kohde,int kuka,int kenen, float aika,bikebase *mopot, int aseena,float paikkax,float paikkay,float paikkaz,float suuntax,float suuntay,float suuntaz);//shooting //target, who, whos, time, bikebase, mopeds, as_a_weapon, placex,palcey,placez, directionx,directiony,directionz
void laskeluodit(void);//bullets fly
void savusta(float koko, float suurenee,bool rotate,float savukesto,float x,float y,float z,int tyyppi,float q,float w,float e);//creates smoke
//void poistaluoti(int a);//poistaa luodin sarjasta
void laskesavut(void);//laskee savut
void SetupPixelFog(DWORD dwColor, DWORD dwMode);//fog
void SetupVertexFog(float fStart, float fEnd,DWORD dwColor, DWORD dwMode, BOOL fUseRange, FLOAT fDensity);//fog
void valota(float x,float y,float z);//makes light
void poistavalo(int a, int *b);//deletes light
void moveparts(int q);//moves parts to their places
BOOL drawfast(obj *tavara);//draws faster
void laskeukot(void);//calculates movements of humans
//void poistaukko(int a);//deletes a character
void renderukot(void);//draws characters
//void kirjota(INT x, INT y, INT fontti,CHAR teksti[100],LPDIRECTDRAWSURFACE7 pinta,LPDIRECTDRAWSURFACE7 font1);
void kirjota(INT x, INT y, INT fontti,CHAR teksti[100]);
void render_game(void);//draws moped driving
void render_mission(void);//draws mission briefing
void arvo_mission(bikebase *mopot,int missionumero);
void laskekoordinaatit(float *x,float *z);//gives x and z wich are not inside houses from the map.
void laskemissiot(bikebase *mopot);//examines is a mission accomplished
void arvoukko(int q);//randomizes a character to field
void luemissiot(void);//reads missions
void laskemopot(void);//calculate mopeds //for Artificial intelligence of mopeds
void arvomopo(int d);//randomizes a moped to field
void render_varikko(void);//draws a depot
void readkey_game(void);//read keys during game
void luesavet(void);//read saved games
void peli_lataa(void);//loads a game
void peli_tallenna(void);//saves a game
void render_menu(void);//draws the menu
void peli_uusi(void);//starts a new game
void cfg_save(void);//saves settings
void cfg_load(void);//loads settings
void sounds_start(void);//initialize voices
void soita(int samplenumero,float volume,float paikkax,float paikkaz);//plays a sound
void clearzbuffer(void);
void startApplication(HINSTANCE hInstance);




	//game content objects
	const float maxvisible =25000.0f;
	int mapsx,mapsz;//ammount of maps
	const int maksimiluoteja=1000;//400//maximium ammount of bullets
	const int maksimisavuja=4000;//400//maximium ammount of smokes
	const int maksimivaloja=10;//maximium ammount of lights
	const int maksimiukkoja=1000;//maximium ammount of characters
	D3DVECTOR keskipiste[maksimisavuja]; //centerpoint[maximium ammount of smokes]
	DWORD visible[maksimisavuja];
	float radius[maksimisavuja];
	pvertex kolmiot[maksimisavuja*12];//triangles
	pvertex luotitrace[maksimiluoteja*2];//bullet trace
	bikebase mopot[1000];//mopeds
	int mopoja;//ammount of mopeds
	int majax,majaz;//coordinates of headquarters
	linjagroup viivagroup[2];//walls	
	int viivagrouppia;//ammount of wall groups
	panos luoti[maksimiluoteja];//bullets	
	weapon ase[20];//guns
	smoke savu[maksimisavuja];//smokes
	int maps[200][200];
	person ukko[maksimiukkoja];//person character[maximium ammount of characters]
	D3DVECTOR keskipisteukko[maksimiukkoja];//center point character
	DWORD visibleukko[maksimiukkoja];//visible character
	float radiusukko[maksimiukkoja];//radius character
	D3DVECTOR keskipistemap[1000];//centerpoint character
	DWORD visiblemap[1000];
	float radiusmap[1000];
	//float nopeusoli;
	int pelivaihe,pelivaihe_oli;//gamephase, gamepahse_was
	int pelivaihe2,pelivaihe2_oli;//gamephase2, gamepahse_was2
	light lamppu[maksimivaloja];
	int valoja;//ligths
	bool mapmode,mapmode2;//0 =normal 1=from above
	float kamerax1,kameray1,kameraz1;//camera from
	float kamerax2,kameray2,kameraz2;//camera to
	ukontekstuurit ukkotekstuuri[10];//charactertextures
	missiovarasto missionlevel[10];//mission reservoir
	char missioninfo[21][800];//mission briefing
	int missionantovaihe;//is briefing readed
	float pelinopeus;//game speed
	int korjaussumma;//price of repairs
	char m_filenames[10][256];//file names of saved files
	int kirjaintan[10];//how many letters are in file names
	bool loadable[10];//is it able to load
	int tallennuspaikka;//wich save is selected
	bool tallennettu;//is game saved
	int keytimer;//keyboard timer
	int kirjaintanimessa;//how many letters in name
	char savenimi[256];//name of save
	float kursori;//cursor timer
	int menuvalittu;//what is selected in menu
	int menuja[10];//how many selections are possible
	bool options[10];//options
	int vaikeustaso;//game difficulty level
	bool valittu;//selected //while setting keys
	float quake;//makes game quake for short time
	

	//sounds	
	int SAMPLE_NUMBER;//number of samples
	LPDIRECTSOUND        lpDS;
	//LPDIRECTSOUNDBUFFER pDSB;
	HSNDOBJ voices[25];
	bool SOUNDS_ON;//is sound engine initialized
	bool SOUNDS_LOADED;//are samples loaded
	WORD			DLLversion;
	float soundtimer[25];//samples are not played every millisecond

	//objects
	kuvat mallit[11];
	
	//input
	LPDIRECTINPUT8        g_lpDI;
	LPDIRECTINPUTDEVICE8  g_lpDIDevice;
	LPDIRECTINPUTDEVICE8  g_pMouse;
	DIMOUSESTATE		  mousestate;
	DIMOUSESTATE		  mousestate2;
	char  buffer[256], buffer2[256];
	float mousex, mousey;
	float plusmiinus;// tempfloat adjustable by keyboard
	int key[20];//game input keys	
	bool pressed,pressed2;//is any key pressed


	int ukkoja;//ammount of characters in a level
	int savuja;//ammount of smokes in a level
	int luoteja;//ammount of bullets in the air
	LPDIRECT3DDEVICE7 m_pDevice;
	LPDIRECT3D7 m_pD3D;
	LPDIRECTDRAWSURFACE7 taka;	
	LPDIRECTDRAWSURFACE7 m_pPrimary;
	LPDIRECTDRAW7 m_pDD;
	LPDIRECTDRAWSURFACE7 zpuskuri;//zbuffer
	D3DMATRIX m_World, m_View, m_Projection;
	int enumerationint1,enumerationint2;//enumbering ints
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int SCREEN_BITS;
	int screenmode;
	//D3DDEVICEINFO info;
	DWORD m_LastTime;
	bool quittaos;//are we quiting?
	int materiaa;//ammount of materials
	D3DMATERIAL7 *mat;	
	ID3DXMatrixStack *matriisi;
	LONG bug1,bug2,bug3;
	float elapsed,elapsed2;
	float elapsed3[100];
	D3DDEVICEDESC7 desc3d;
	float dx,dx2,dy,dz;//camera 
	float camx,camy,camz;//camera
	LPDIRECTDRAWSURFACE7 
		*tausta		//background
		//,cube
		//,
		//,font1
		,*kuvia;//pictures
