#pragma once

#include "SoulReaverStructures.h"

struct VramSize
{
	short x;
	short y;
	short w;
	short h;
};

struct _RGBAColor
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

struct TextureMT3
{
	unsigned char u0;
	unsigned char v0;
	unsigned short clut;
	unsigned char u1;
	unsigned char v1;
	unsigned short tpage;
	unsigned char u2;
	unsigned char v2;
	char pad1;
	char sortPush;
	long color;
};

// Don't need the whole _Model struct right now
struct _Model
{
	char dummy;
};

// Don't need the whole _G2AnimKeylist_Type struct right now
struct _G2AnimKeylist_Type
{
	char dummy;
};

// Don't need the whole _FX_PRIM struct right now
struct _FX_PRIM
{
	char dummy;
};

// Don't need the whole _FXTracker struct right now
struct _FXTracker
{
	char dummy;
};

// Don't need the whole ObjectEffect struct right now
struct ObjectEffect
{
	char dummy;
};

struct Object
{
	long oflags;
	short id;
	short sfxFileHandle;
	short numModels;
	short numAnims;
	struct _Model** modelList;
	struct _G2AnimKeylist_Type** animList;
	short introDist;
	short vvIntroDist;
	short removeDist;
	short vvRemoveDist;
	void* data;
	char* script;
	char* name;
	unsigned char* soundData;
	long oflags2;
	short sectionA;
	short sectionB;
	short sectionC;
	short numberOfEffects;
	struct ObjectEffect* effectList;
	unsigned long* relocList;
	void* relocModule;
	struct VramSize vramSize;
};

struct PhysObData
{
	long Mode;
	union
	{
		struct
		{
			short xForce;
			short yForce;
		};
		long projectileType;
	};
	struct _Instance* Force;
	short LinkNode;
	short px;
	short py;
	short pz;
	short rx1;
	short ry1;
	short rz1;
	short Segment1;
	short rx2;
	short ry2;
	short rz2;
	short Segment2;
	short Steps;
	short Step;
	short PathNumber;
	short Pad1;
	struct _HInfo* RightCollision;
	struct _HInfo* LeftCollision;
	short burnAmpl;
	short throwFlags;
	short initialXRot;
	short xRotVel;
	short yRotVel;
	short zRotVel;
	struct _Instance* throwingInstance;
	int physObTimer;
};

struct PhysObProperties
{
	unsigned short version;
	unsigned short family;
	unsigned short ID;
	unsigned short Type;
};

struct __PhysObProjectileProperties
{
	struct PhysObProperties Properties;
	long totalProjectiles;
	struct __PhysObProjectileData* data;
};

struct __PhysObProjectileData
{
	char model;
	char startAnim;
	char loopAnim;
	char endAnim;
	long flags;
	struct PhysObWeaponAttributes* weapon;
};

struct GenericFXObject
{
	struct _GenericParticleParams* ParticleList;
	struct _GenericRibbonParams* RibbonList;
	struct _GenericGlowParams* GlowList;
	struct _GenericLightningParams* LightningList;
	struct _GenericBlastringParams* BlastList;
	struct _GenericFlashParams* FlashList;
	long* ColorList;
};

struct _GenericParticleParams
{
	short size;
	unsigned char StartOnInit;
	unsigned char type;
	short birthRadius;
	char startSegment;
	char endSegment;
	struct _Position direction;
	unsigned char spectral_colorize;
	unsigned char absolute_direction;
	char accx;
	char accy;
	char accz;
	char useInstanceModel;
	unsigned char startColor_red;
	unsigned char startColor_green;
	unsigned char startColor_blue;
	char model;
	unsigned char endColor_red;
	unsigned char endColor_green;
	unsigned char endColor_blue;
	char texture;
	short lifeTime;
	unsigned char primLifeTime;
	char use_child;
	short startFadeValue;
	short fadeStep;
	char numberBirthParticles;
	char z_undulation_mode;
	short scaleSpeed;
	struct _Position offset;
	short startScale;
};

struct evObjectBirthProjectileData
{
	struct _Instance* instance;
	int joint;
	int type;
	struct _Instance* birthInstance;
};

struct _FXForceFieldEffect
{
	void* next;
	void* continue_process;
	struct _Instance* instance;
	unsigned char effectType;
	unsigned char type;
	short lifeTime;
	struct _SVector offset;
	short size;
	short size_diff;
	short size_change;
	short deg;
	short deg_change;
	short start_fade;
	short end_fade;
	long color;
};

struct _FXParticle
{
	void* next;
	void* continue_process;
	struct _Instance* instance;
	unsigned char effectType;
	unsigned char type;
	short lifeTime;
	struct TextureMT3* texture;
	void* fxprim_modify_process;
	void* fxprim_process;
	short size;
	short primLifeTime;
	short birthRadius;
	short scaleSpeed;
	struct _Position direction;
	unsigned short flag_bits;
	struct _Position acceleration;
	short startScale;
	struct _Position offset;
	char startSegment;
	char z_undulate;
	/*long*/ struct _RGBAColor startColor;
	/*long*/ struct _RGBAColor endColor;
	short colorStepValue;
	char numberBirthParticles;
	char endSegment;
	short startFadeValue;
	short fadeStep;
};

struct _GenericBlastringParams
{
	char type;
	char use_child;
	short lifeTime;
	struct _Position offset;
	short matrixSeg;
	char segment;
	char sortInWorld;
	short radius;
	short size1;
	short size2;
	short endRadius;
	short colorchange_radius;
	int vel;
	int accl;
	short height1;
	short height2;
	short height3;
	char predator_offset;
	char stay_in_place;
	long startColor;
	long endColor;
};

struct __ReaverTuneData
{
	unsigned long spectralGlowColor;
	unsigned long materialGlowColor;
	unsigned long sunlightGlowColor;
	unsigned long waterGlowColor;
	unsigned long stoneGlowColor;
	unsigned long fireGlowColor;
	unsigned long spiritGlowColor;
	unsigned long soundGlowColor;
	unsigned long spectralInnerColor;
	unsigned long materialInnerColor;
	unsigned long sunlightInnerColor;
	unsigned long waterInnerColor;
	unsigned long stoneInnerColor;
	unsigned long fireInnerColor;
	unsigned long spiritInnerColor;
	unsigned long soundInnerColor;
	unsigned long spectralInnerGlowColor;
	unsigned long materialInnerGlowColor;
	unsigned long sunlightInnerGlowColor;
	unsigned long waterInnerGlowColor;
	unsigned long stoneInnerGlowColor;
	unsigned long fireInnerGlowColor;
	unsigned long spiritInnerGlowColor;
	unsigned long soundInnerGlowColor;
	unsigned long icon_colors[24];
};

struct ObjectAccess
{
	char* objectName;
	Object* object;
};

void WriteCallToAddress(int address, void* newAddress);
void InitializeDebugMenu();
void ShutdownDebugMenu();