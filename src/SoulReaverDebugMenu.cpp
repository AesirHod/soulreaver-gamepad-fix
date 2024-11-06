#include "stdafx.h"
#include "SoulReaverDebugMenu.h"
#include "SoulReaverPossession.h"

typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

enum DEBUG_LINE_TYPE
{
	DEBUG_LINE_TYPE_BIT = 0,
	DEBUG_LINE_TYPE_LONG = 1,
	DEBUG_LINE_TYPE_ACTION = 2,
	DEBUG_LINE_TYPE_ACTION_WITH_LINE = 3,
	DEBUG_LINE_TYPE_MENU = 4,
	DEBUG_LINE_TYPE_ENDLIST = 5,
	DEBUG_LINE_TYPE_FORMAT = 6,
	DEBUG_LINE_TYPE_INFO = 7,
};

struct DebugMenuLine
{
	enum DEBUG_LINE_TYPE type;
	long lower;
	long upper;
	char* text;
	long* var_address;
	long bit_mask;
};

long* mainMenu = (long*)0x004F5F58;
long* razielMenu = (long*)0x004f6570;

char* endOfMenu = (char*)0x00B08388;

long* gameTrackerX_debugFlags = (long*)0x00C66DE0;

long* debugRazielFlags1 = (long*)0x00C644F4;
long* debugRazielFlags2 = (long*)0x00C644F8;
long* debugRazielFlags3 = (long*)0x00C644FC;

DebugMenuLine debugImbueSoulReaverMenu[] = {
	{	DEBUG_LINE_TYPE_MENU,		0,	0,	"Main Menu...",		mainMenu,					0x00000000	},
	{	DEBUG_LINE_TYPE_MENU,		0,	0,	"Raziel Menu....",	razielMenu,					0x00000000	},
	{	DEBUG_LINE_TYPE_BIT,		0,	0,	"Hold Soul Reaver",	debugRazielFlags1,			0x00000400	},
	{	DEBUG_LINE_TYPE_BIT,		0,	0,	"Spectral Reaver",	debugRazielFlags2,			0x00000400	},
	{	DEBUG_LINE_TYPE_BIT,		0,	0,	"Material Reaver",	debugRazielFlags2,			0x00000800	},
	{	DEBUG_LINE_TYPE_BIT,		0,	0,	"Fire Reaver",		debugRazielFlags2,			0x00008000	},
	{	DEBUG_LINE_TYPE_BIT,		0,	0,	"Water Reaver",		debugRazielFlags2,			0x00002000	},
	{	DEBUG_LINE_TYPE_BIT,		0,	0,	"Sunlight Reaver",	debugRazielFlags2,			0x00004000	},
	{	DEBUG_LINE_TYPE_BIT,		0,	0,	"Sound Reaver",		debugRazielFlags2,			0x00020000	},
	{	DEBUG_LINE_TYPE_BIT,		0,	0,	"Ariel Reaver",		debugRazielFlags2,			0x00001000	},
	{	DEBUG_LINE_TYPE_BIT,		0,	0,	"Kain Reaver",		debugRazielFlags2,			0x00010000	},
	{	DEBUG_LINE_TYPE_ACTION,		0,	0,	"Possess Next",		(long*)/*0x0040c470*/MONAPI_PossessNext,			0x00000000,	},
	{	DEBUG_LINE_TYPE_ENDLIST,	0,	0,	endOfMenu,			gameTrackerX_debugFlags,	0x00000000	}
};

DebugMenuLine* newDebugImbueSoulReaverMenu = nullptr;

_Instance** Raziel = (_Instance**)0x00C66D4C;
struct ObjectAccess* objectAccess = (struct ObjectAccess*)0x004fa9e8;

typedef char* (FAR WINAPIV* LPMEMPACKMALLOCCB)(ulong allocSize, uchar memType);
LPMEMPACKMALLOCCB MEMPACK_Malloc = reinterpret_cast<LPMEMPACKMALLOCCB>(0x004b5c40);

typedef int (FAR WINAPIV* LPINPUTG2UPDATECB)();
LPINPUTG2UPDATECB InputG2_Update = reinterpret_cast<LPINPUTG2UPDATECB>(0x00478170);

typedef _Instance* (FAR WINAPIV* LPINSTANCEBIRTHOBJECTCB)(_Instance* parent, Object* object, int modelNum);
LPINSTANCEBIRTHOBJECTCB INSTANCE_BirthObject = reinterpret_cast<LPINSTANCEBIRTHOBJECTCB>(0x004b1630);

typedef void (FAR WINAPIV* LPSTANCELINKTOPARENTCP)(_Instance* instance, _Instance* parent, int node);
LPSTANCELINKTOPARENTCP INSTANCE_LinkToParent = reinterpret_cast<LPSTANCELINKTOPARENTCP>(0x004b2e90);

typedef void (FAR WINAPIV* LPFXCONTUNUEPARTICLECB)(_FXParticle* currentParticle, _FXTracker* fxTracker);
LPFXCONTUNUEPARTICLECB FX_ContinueParticle = reinterpret_cast<LPFXCONTUNUEPARTICLECB>(0x004a53e0);

typedef _FXParticle* (FAR WINAPIV* LPFXGETPARTICLECB)(_Instance* instance, short startSegment);
LPFXGETPARTICLECB FX_GetParticle = reinterpret_cast<LPFXGETPARTICLECB>(0x0049ed00);

typedef TextureMT3* (FAR WINAPIV* LPFXGETTEXTUREOBJECTCB)(Object* object, int modelnum, int texnum);
LPFXGETTEXTUREOBJECTCB FX_GetTextureObject = reinterpret_cast<LPFXGETTEXTUREOBJECTCB>(0x004a1ba0);

typedef void (FAR WINAPIV* FXATTACHEDPARTICLEPRIMPROCESSCB)(_FX_PRIM* fxPrim, _FXTracker* fxTracker);
FXATTACHEDPARTICLEPRIMPROCESSCB FX_AttachedParticlePrimProcess = reinterpret_cast<FXATTACHEDPARTICLEPRIMPROCESSCB>(0x004a3a70);

typedef void (FAR WINAPIV* FXINSERTGENERALEFFECTCB)(void* ptr);
FXINSERTGENERALEFFECTCB FX_InsertGeneralEffect = reinterpret_cast<FXINSERTGENERALEFFECTCB>(0x004a66c0);

typedef int (FAR WINAPIV* LPSOULREAVERFIRECB)();
LPSOULREAVERFIRECB SoulReaverFire = reinterpret_cast<LPSOULREAVERFIRECB>(0x004c52c0);

typedef _FXParticle* (FAR WINAPIV* LPFXSTARTGENERICPARTICLECB)(_Instance* instance, int num, int segOverride, int lifeOverride, int InitFlag);
LPFXSTARTGENERICPARTICLECB FX_StartGenericParticle = reinterpret_cast<LPFXSTARTGENERICPARTICLECB>(0x004a7020);

typedef _FXForceFieldEffect* (FAR WINAPIV* LPFXSTARTFFIELDCB)(_Instance* instance, int size, _Position* offset, int size_diff, int size_change, int deg_change, long color);
LPFXSTARTFFIELDCB FX_StartFField = reinterpret_cast<LPFXSTARTFFIELDCB>(0x004a9410);

typedef evObjectBirthProjectileData* (FAR WINAPIV* LPPHYSOB_BIRTHPROJECTILECB)(_Instance* parent, int joint, int type);
LPPHYSOB_BIRTHPROJECTILECB PHYSOB_BirthProjectile = reinterpret_cast<LPPHYSOB_BIRTHPROJECTILECB>(0x004bbbd0);

typedef void (FAR WINAPIV* LPTURNOFFCOLLISIONPHYSOBCB)(_Instance* instance, int coll);
LPTURNOFFCOLLISIONPHYSOBCB TurnOffCollisionPhysOb = reinterpret_cast<LPTURNOFFCOLLISIONPHYSOBCB>(0x004c02d0);

typedef int (FAR WINAPIV* LPSETOBJECTBIRTHPROJECTILEDATACB)(_Instance* instance, int joint, int type);
LPSETOBJECTBIRTHPROJECTILEDATACB SetObjectBirthProjectileData = reinterpret_cast<LPSETOBJECTBIRTHPROJECTILEDATACB>(0x004ce5e0);

typedef void (FAR WINAPIV* LPCAMERASETVIEWVOLUMECB)(Camera* camera);
LPCAMERASETVIEWVOLUMECB CAMERA_SetViewVolume = reinterpret_cast<LPCAMERASETVIEWVOLUMECB>(0x004818c0);

typedef void (FAR WINAPIV* LPPIPE3DCALCULATEWCTRANSFORMCB)(CameraCore_Type* cameraCore);
LPPIPE3DCALCULATEWCTRANSFORMCB PIPE3D_CalculateWCTransform = reinterpret_cast<LPPIPE3DCALCULATEWCTRANSFORMCB>(0x004C2740);

typedef void (FAR WINAPIV* LPG2EMULATIONINSTANCESETANIMATIONCB)(_Instance* instance, int CurrentSection, int NewAnim, int NewFrame, int Frames);
LPG2EMULATIONINSTANCESETANIMATIONCB G2EmulationInstanceSetAnimation = reinterpret_cast<LPG2EMULATIONINSTANCESETANIMATIONCB>(0x004cef60);

typedef void (FAR WINAPIV* LPEMULATIONINSTANCESETMODECB)(_Instance* instance, int CurrentSection, int Mode);
LPEMULATIONINSTANCESETMODECB G2EmulationInstanceSetMode = reinterpret_cast<LPEMULATIONINSTANCESETMODECB>(0x004cf030);

__declspec(dllexport) void WINAPIV InputG2_Update_New()
{
	InputG2_Update();

	if ((GetAsyncKeyState(VK_F11) & 1) == 1)
	{
		unsigned char* menuState = (unsigned char*)0x00C66E92;
		unsigned char* lockRaziel = (unsigned char*)0x00AF8A49;
		if (*menuState == 0)
		{
			*menuState = 4;
		}
		else if (*menuState == 4)
		{
			*menuState = 0;
			*lockRaziel = 6;
		}
	}
}

__declspec(dllexport) _FXParticle* WINAPIV FX_StartGenericParticle_New(_Instance* instance, int num, int segOverride, int lifeOverride, int InitFlag)
{
	_FXParticle* fxParticle = nullptr;
	_GenericParticleParams* particleParams = nullptr;
	Object* object = nullptr;

	//fxParticle = FX_StartGenericParticle(instance, num, segOverride, lifeOverride, InitFlag);
	//return fxParticle;

	if (objectAccess[10].object == nullptr)
	{
		return nullptr;
	}

	particleParams = &((GenericFXObject*)(objectAccess[10].object->data))->ParticleList[num];

	if (InitFlag != 0 && particleParams->StartOnInit == 0)
	{
		return nullptr;
	}

	if (particleParams->use_child != 0)
	{
		if (instance->LinkChild == nullptr)
		{
			return nullptr;
		}

		instance = instance->LinkChild;
	}

	if (particleParams->texture != -1)
	{
		object = (particleParams->useInstanceModel != 0) ? instance->object : objectAccess[10].object;

		if (object == nullptr)
		{
			return nullptr;
		}
	}

	fxParticle = reinterpret_cast<_FXParticle*>(MEMPACK_Malloc(76, 13));

	if (fxParticle != nullptr)
	{
		fxParticle->effectType = 1;
		fxParticle->type = 0;
		fxParticle->instance = instance;
		fxParticle->startSegment = 0;
		fxParticle->texture = nullptr;
		fxParticle->continue_process = FX_ContinueParticle;
		fxParticle->fxprim_process = nullptr;
		fxParticle->fxprim_modify_process = nullptr;
		fxParticle->startScale = 4096;
		fxParticle->scaleSpeed = 0;
		fxParticle->offset.z = 0;
		fxParticle->offset.y = 0;
		fxParticle->offset.x = 0;
		fxParticle->acceleration.z = 0;
		fxParticle->acceleration.y = 0;
		fxParticle->acceleration.x = 0;
		fxParticle->flag_bits = 0;
		fxParticle->z_undulate = 0;

		fxParticle->numberBirthParticles = particleParams->numberBirthParticles;
		fxParticle->size = particleParams->size;
		fxParticle->type = particleParams->type;
		fxParticle->birthRadius = particleParams->birthRadius;
		fxParticle->startSegment = (segOverride == 0) ? particleParams->startSegment : (char)segOverride;
		fxParticle->endSegment = particleParams->endSegment;
		fxParticle->direction = particleParams->direction;
		fxParticle->acceleration.x = particleParams->accx;
		fxParticle->acceleration.y = particleParams->accy;
		fxParticle->acceleration.z = particleParams->accz;
		fxParticle->startColor.r = particleParams->startColor_red;
		fxParticle->startColor.g = particleParams->startColor_green;
		fxParticle->startColor.b = particleParams->startColor_blue;
		fxParticle->startColor.a = 0;
		fxParticle->endColor.r = particleParams->startColor_red;
		fxParticle->endColor.g = particleParams->startColor_green;
		fxParticle->endColor.b = particleParams->startColor_blue;
		fxParticle->endColor.a = 0;
		fxParticle->lifeTime = (lifeOverride == 0) ? particleParams->lifeTime : (short)lifeOverride;
		fxParticle->primLifeTime = particleParams->primLifeTime;
		fxParticle->startFadeValue = particleParams->startFadeValue;
		fxParticle->startScale = particleParams->startScale;
		fxParticle->scaleSpeed = particleParams->scaleSpeed;
		fxParticle->offset = particleParams->offset;
		fxParticle->z_undulate = particleParams->z_undulation_mode;
		if (particleParams->fadeStep == -1 && particleParams->primLifeTime != 0)
		{
			fxParticle->fadeStep = (short)((4096 - (int)fxParticle->startFadeValue) / (int)particleParams->primLifeTime);
		}
		else
		{
			fxParticle->fadeStep = particleParams->fadeStep;
		}
		if (particleParams->texture != -1)
		{
			fxParticle->texture = FX_GetTextureObject(object, particleParams->model, particleParams->texture);
			fxParticle->startColor.a = (unsigned char)((fxParticle->texture->color & 0x03000000) >> 24);
		}
		if (particleParams->type == 1)
		{
			fxParticle->fxprim_process = FX_AttachedParticlePrimProcess;
		}
		if (particleParams->spectral_colorize == 1)
		{
			fxParticle->flag_bits |= 1;
		}
		if (particleParams->absolute_direction != 0)
		{
			fxParticle->flag_bits |= 2;
		}
		if (particleParams->spectral_colorize == 2)
		{
			if (SoulReaverFire() != 0)
			{
				unsigned char tempColor;
				tempColor = fxParticle->startColor.b;
				fxParticle->startColor.b = fxParticle->startColor.r;
				fxParticle->startColor.r = tempColor;
				tempColor = fxParticle->endColor.b;
				fxParticle->endColor.b = fxParticle->endColor.r;
				fxParticle->endColor.r = tempColor;
			}
		}

		FX_InsertGeneralEffect(fxParticle);
	}

	return fxParticle;
}

__declspec(dllexport) evObjectBirthProjectileData* PHYSOB_BirthProjectile_New(_Instance* parent, int joint, int type)
{
	return PHYSOB_BirthProjectile(parent, joint, type);

	evObjectBirthProjectileData* birthProjectileData = reinterpret_cast<evObjectBirthProjectileData*>(SetObjectBirthProjectileData(parent, joint, type));

	// _Instance* birthProjectilePhysOb = BirthProjectilePhysOb(parent, joint, type);

	_FXForceFieldEffect* forceFieldEffect;  // p_Var1
	__PhysObProjectileProperties* projectileProperties; // pvVar2
	__PhysObProjectileData* projectileData; // pvVar3
	PhysObData* projectilePhysObData; // puVar4
	int NewAnim;
	_Position startPos;

	_Instance* birthProjectilePhysOb = nullptr;

	// "force___"
	if (objectAccess[17].object != nullptr)
	{
		// "force___"
		birthProjectilePhysOb = INSTANCE_BirthObject(parent, objectAccess[17].object, 0);
		if (birthProjectilePhysOb != nullptr)
		{
			projectileProperties = reinterpret_cast<__PhysObProjectileProperties*>(birthProjectilePhysOb->data);
			reinterpret_cast<PhysObData*>(birthProjectilePhysOb->extraData)->projectileType = type;
			projectileData = &(reinterpret_cast<__PhysObProjectileData*>(projectileProperties->data))[type];
			birthProjectilePhysOb->currentModel = projectileData->model;
			projectilePhysObData = reinterpret_cast<PhysObData*>(birthProjectilePhysOb->extraData);
			if (projectileData->model == 0)
			{
				startPos.x = 0;
				startPos.y = 0;
				startPos.z = 0;
				forceFieldEffect = FX_StartFField(birthProjectilePhysOb, 120, &startPos, 32, 16, 128, 0x00202020);
				if (forceFieldEffect != nullptr)
				{
					forceFieldEffect->type = 1;
				}
			}
			INSTANCE_LinkToParent(birthProjectilePhysOb, parent, joint);
			TurnOffCollisionPhysOb(birthProjectilePhysOb, 7);
			projectileProperties = reinterpret_cast<__PhysObProjectileProperties*>(birthProjectilePhysOb->data);
			if (projectileProperties->Properties.family == 7)
			{
				projectileProperties->data[projectilePhysObData->projectileType].startAnim;
				if (NewAnim != -1)
				{
					G2EmulationInstanceSetAnimation(birthProjectilePhysOb, 0, NewAnim, 0, 0);
					G2EmulationInstanceSetMode(birthProjectilePhysOb, 0, 2);
				}
			}
			if ((projectileProperties->Properties.Type & 1) == 0)
			{
				projectilePhysObData->physObTimer = 614400;
			}
			else
			{
				projectilePhysObData->Mode = 0x1080;
				projectilePhysObData->Force = nullptr;
				projectilePhysObData->Step = 0;
				projectilePhysObData->Steps = 0;
				birthProjectilePhysOb->xVel = 0;
				birthProjectilePhysOb->yVel = 0;
				birthProjectilePhysOb->zVel = 0;
				birthProjectilePhysOb->xAccl = 0;
				birthProjectilePhysOb->yAccl = 0;
				birthProjectilePhysOb->zAccl = 0;
			}
		}
	}

	birthProjectileData->birthInstance = birthProjectilePhysOb;
	return birthProjectileData;
}

__declspec(dllexport) void WINAPIV CAMERA_SetViewVolume_New(Camera* camera)
{
	camera->core.rightX *= 3;
	camera->core.rightX /= 2;
	CAMERA_SetViewVolume(camera);
}

void InitializeDebugMenu()
{
	// Need to make a dynamic copy of the menu because Soul Reaver tries to write to the memory after the strings.
	int noOfMenuOptions = sizeof(debugImbueSoulReaverMenu) / sizeof(DebugMenuLine);
	newDebugImbueSoulReaverMenu = new DebugMenuLine[noOfMenuOptions];
	memcpy(newDebugImbueSoulReaverMenu, debugImbueSoulReaverMenu, sizeof(debugImbueSoulReaverMenu));
	for (int i = 0; i < noOfMenuOptions; i++)
	{
		char* newText = new char[50];
		strcpy(newText, newDebugImbueSoulReaverMenu[i].text);
		newDebugImbueSoulReaverMenu[i].text = newText;
	}

	DebugMenuLine* imbueReaverLine = &((DebugMenuLine*)razielMenu)[5];
	imbueReaverLine->var_address = (long*)newDebugImbueSoulReaverMenu;

	WriteCallToAddress(0x0047A407, InputG2_Update_New);
	WriteCallToAddress(0x004A7AF5, FX_StartGenericParticle_New);
	WriteCallToAddress(0x004C5090, PHYSOB_BirthProjectile_New);
	WriteCallToAddress(0x004AB65C, CAMERA_SetViewVolume_New);
	WriteCallToAddress(0x004ABB87, CAMERA_SetViewVolume_New);
	WriteCallToAddress(0x004ABCBD, CAMERA_SetViewVolume_New);
	WriteCallToAddress(0x004ABEC2, CAMERA_SetViewVolume_New);

	// For Raziel
	// Scale is at Raziel + 0x00000084 (aka 132). Looks correct.
	// RelativeMatrix could be at Raziel + 0x000000A4. Size of Matrix is 32 (aka 0x20), but all 0s for Raziel.
	// tFace is at Raziel + 0x000000B4
	// oldTFace is at Raziel + 0x000000B8
	// tFaceLevel is at Raziel + 0x000000BC
	// cachedTFace is at Raziel + 0x000000C8
	// cachedBSPTree is at Raziel + 0x000000CA
	// cachedTFaceLevel is at Raziel + 0x000000CC
	// Removed from PC builds: dsignal, shadow0, shadow1, extraLight, extraLightDir, extraLightScale
	// hModelList is be at Raziel + 0x000000E8
	// fadeValue is be at Raziel + 0x000000EC
	// lightMatrix might be at Raziel + 0x000000EE
	// Process function is at Raziel + 0x00000F0
	// Collide function is at Raziel + 0x00000F4
	// AdditionalCollide function is at Raziel + 0x00000F8
	// Removed from PC build: AdditionalDraw
	// Query function is at Raziel + 0x00000FC
	// Post (aka Message) function is at Raziel + 0x0000100
	// IntroName is at Raziel + 0x140 (64/0x40 bytes after post function), so looks correct from there.

	// 0x004C5090 call PHYSOB_BirthProjectile for current reaver
	//FX_StartGenericParticle = 0x004a7020
}

void ShutdownDebugMenu()
{
	int noOfMenuOptions = sizeof(debugImbueSoulReaverMenu) / sizeof(DebugMenuLine);
	for (int i = 0; i < noOfMenuOptions; i++)
	{
		delete[] newDebugImbueSoulReaverMenu[i].text;
	}

	delete newDebugImbueSoulReaverMenu;
}