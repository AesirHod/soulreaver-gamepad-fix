#pragma once

struct _Position
{
	short x;
	short y;
	short z;
};

struct _Rotation
{
	short x;
	short y;
	short z;
	short pad;
};

struct _Normal
{
	short x;
	short y;
	short z;
	short pad;
};

struct _PlaneConstants
{
	short a;
	short b;
	short c;
	short flags;
	long d;
};

struct _Vector
{
	long x;
	long y;
	long z;
};

struct _SVector
{
	short x;
	short y;
	short z;
	short pad;
};

struct _PrimPool
{
	long numPrims;
	unsigned long* nextPrim;
	unsigned long* lastPrim;
	unsigned long prim[24000];
};

struct VECTOR
{
	long vx;
	long vy;
	long vz;
	long pad;
};

struct DVECTOR
{
	short vx;
	short vy;
};

struct CVECTOR
{
	unsigned char r, g, b, cd;
};

struct MATRIX
{
	short m[3][3];
	long t[3];
};

struct _ColorType // hashcode: 0x440E837C (dec: 1141801852)
{
	unsigned char r; // size=0, offset=0
	unsigned char g; // size=0, offset=1
	unsigned char b; // size=0, offset=2
	unsigned char code; // size=0, offset=3
};

struct CameraCore_Type
{
	struct _Position position;
	short pad1;
	struct MATRIX vvNormalWorVecMat[2];
	long vvPlaneConsts[6];
	struct MATRIX* wcTransform;
	long farPlane;
	long projDistance;
	long nearPlane;
	struct MATRIX* wcTransform2;
	struct MATRIX* cwTransform2;
	struct _Normal viewVolumeNormal[5];
	int leftX;
	int rightX;
	int topY;
	int bottomY;
	struct _Rotation rotation;
	short pad2;
	struct _SVector screenScale;
	short pad3;
	struct _Position debugPos;
	short pad4;
	struct _Rotation debugRot;
	short pad5;
	struct _Position nondebugPos;
	short pad6;
};

// Don't need the whole Camera struct right now
struct Camera
{
	CameraCore_Type core;
};

struct __Event 
{
	int ID; // size=0, offset=0
	int Data; // size=0, offset=4
};

struct __MessageQueue 
{
	int Head; // size=0, offset=0
	int Tail; // size=0, offset=4
	struct __Event Queue[16]; // size=128, offset=8
};

struct __State 
{
	void (*Process)(struct __CharacterState*, int, int); // size=0, offset=0
	struct __MessageQueue Event; // size=136, offset=4
	struct __MessageQueue Defer; // size=136, offset=140
	int Data1; // size=0, offset=276
	int Data2; // size=0, offset=280
};

struct __CharacterState 
{
	struct _Instance* CharacterInstance; // size=668, offset=0
	int TotalSections; // size=0, offset=4
	struct __State SectionList[3]; // size=852, offset=8
};

struct __EngagedInstance 
{
	struct _Instance* instance; // size=668, offset=0
	unsigned long distance; // size=0, offset=4
};

struct __SensoryData 
{
	int Flags; // size=0, offset=0
	struct _SVector ForwardNormal; // size=8, offset=4
	struct _SVector AboveNormal; // size=8, offset=12
	struct _SVector BelowNormal; // size=8, offset=20
	struct _SVector BelowPoint; // size=8, offset=28
	struct _SVector Delta; // size=8, offset=36
	struct _Instance* HitMonster; // size=668, offset=44
	struct _Instance* CurrentAutoFace; // size=668, offset=48
	struct _Instance* LastAutoFace; // size=668, offset=52
	struct _Instance* Portal; // size=668, offset=56
	struct __EngagedInstance* EngagedList; // size=8, offset=60
	unsigned long EngagedMask; // size=0, offset=64
	struct _Vector lookAtPoint; // size=12, offset=68
	unsigned long heldClass; // size=0, offset=80
};

struct _G2SVector3_Type
{
	short x;
	short y;
	short z;
};

struct __Player 
{
	int footPrint; // size=0, offset=0
	struct __CharacterState State; // size=860, offset=4
	int Mode; // size=0, offset=864
	int Anim; // size=0, offset=868
	int RotationSegment; // size=0, offset=872
	struct _SVector iVelocity; // size=8, offset=876
	int Magnitude; // size=0, offset=884
	int input; // size=0, offset=888
	int lastInput; // size=0, offset=892
	int ZDirection; // size=0, offset=896
	short Bearing; // size=0, offset=900
	short LastBearing; // size=0, offset=902
	int steeringMode; // size=0, offset=904
	short steeringVelocity; // size=0, offset=908
	short steeringAcceleration; // size=0, offset=910
	int steeringLockRotation; // size=0, offset=912
	short movementMinRate; // size=0, offset=916
	short movementMaxRate; // size=0, offset=918
	short movementMinAnalog; // size=0, offset=920
	short movementMaxAnalog; // size=0, offset=922
	struct __SensoryData Senses; // size=84, offset=924
	struct _Instance* attachedPlatform; // size=668, offset=1008
	short dropOffHeight; // size=0, offset=1012
	short fallZVelocity; // size=0, offset=1014
	short HealthScale; // size=0, offset=1016
	short HealthBalls; // size=0, offset=1018
	int HitPoints; // size=0, offset=1020
	int DamageFrequency; // size=0, offset=1024
	int invincibleTimer; // size=0, offset=1028
	int Abilities; // size=0, offset=1032
	struct _Instance* GlyphSystem; // size=668, offset=1036
	unsigned short GlyphManaBalls; // size=0, offset=1040
	unsigned short GlyphManaMax; // size=0, offset=1042
	struct __FitPoint* constrictData; // size=4, offset=1044
	short constrictIndex; // size=0, offset=1048
	short constrictWaitIndex; // size=0, offset=1050
	struct _SVector constrictCenter; // size=8, offset=1052
	short constrictFlag; // size=0, offset=1060
	short constrictGoodCircle; // size=0, offset=1062
	unsigned long constrictXTotal; // size=0, offset=1064
	unsigned long constrictYTotal; // size=0, offset=1068
	struct _Instance* soulReaver; // size=668, offset=1072
	unsigned long currentSoulReaver; // size=0, offset=1076
	int CurrentPlane; // size=0, offset=1080
	int slipSlope; // size=0, offset=1084
	unsigned long idleCount; // size=0, offset=1088
	struct _Instance* idleInstance; // size=668, offset=1092
	struct __AttackItem* attack; // size=36, offset=1096
	int attackFlags; // size=0, offset=1100
	int currentAttack; // size=0, offset=1104
	struct _Instance* attackCurrentHit; // size=668, offset=1108
	struct _Instance* attackLastHit; // size=668, offset=1112
	struct _FXGlowEffect* glowEffect; // size=44, offset=1116
	struct _Instance* attackedBy; // size=668, offset=1120
	struct __ThrowItem* throwData; // size=32, offset=1124
	int throwMode; // size=0, offset=1128
	struct _Position throwTarget; // size=6, offset=1132
	struct _Instance* throwInstance; // size=668, offset=1140
	short throwXRot; // size=0, offset=1144
	short throwZRot; // size=0, offset=1146
	int throwReturnRot; // size=0, offset=1148
	struct __MessageQueue padCommands; // size=136, offset=1152
	void (*returnState)(struct __CharacterState*, int, int); // size=0, offset=1288
	unsigned long passedMask; // size=0, offset=1292
	struct _G2SVector3_Type extraRot; // size=6, offset=1296
	long blankPad; // size=0, offset=1304
	int effectsFlags; // size=0, offset=1308
	short effectsFadeSource; // size=0, offset=1312
	short effectsFadeDest; // size=0, offset=1314
	int effectsFadeStep; // size=0, offset=1316
	int effectsFadeSteps; // size=0, offset=1320
	short autoFaceZone; // size=0, offset=1324
	short autoFaceAngle; // size=0, offset=1326
	int autoFaceLastRootAngle; // size=0, offset=1328
	int autoFaceRootAngle; // size=0, offset=1332
	int autoFaceTrueAngle; // size=0, offset=1336
	int autoFaceAnim; // size=0, offset=1340
	int autoFaceLastAnim; // size=0, offset=1344
	int nothingCounter; // size=0, offset=1348
	int timeAccumulator; // size=0, offset=1352
	struct _Position puppetMoveToPoint; // size=6, offset=1356
	struct _Position puppetRotToPoint; // size=6, offset=1362
	int soundModifier; // size=0, offset=1368
	short alarmTable; // size=0, offset=1372
	short terminator; // size=0, offset=1374
	short swimSpeedAdjustment; // size=0, offset=1376
	short swimTargetSpeed; // size=0, offset=1378
	unsigned long soundHandle; // size=0, offset=1380
	long soundTimer; // size=0, offset=1384
	long soundTotalTime; // size=0, offset=1388
	unsigned long soundDistance; // size=0, offset=1392
	short soundStartPitch; // size=0, offset=1396
	short soundEndPitch; // size=0, offset=1398
	short soundStartVolume; // size=0, offset=1400
	short soundEndVolume; // size=0, offset=1402
	unsigned long soundHandle2; // size=0, offset=1404
	long soundTimer2; // size=0, offset=1408
	long soundTotalTime2; // size=0, offset=1412
	unsigned long soundDistance2; // size=0, offset=1416
	short soundStartPitch2; // size=0, offset=1420
	short soundEndPitch2; // size=0, offset=1422
	short soundStartVolume2; // size=0, offset=1424
	short soundEndVolume2; // size=0, offset=1426
	long soundTimerNext; // size=0, offset=1428
	unsigned long soundTimerData; // size=0, offset=1432
	unsigned long forcedGlideSpeed; // size=0, offset=1436
	struct _SVector collisionEdgeOffset; // size=8, offset=1440
	struct __SAnim* currentSAnim; // size=16, offset=1448
	unsigned long playerEvent; // size=0, offset=1452
	unsigned long playerEventHistory; // size=0, offset=1456
	int currentHint; // size=0, offset=1460
};

struct NodeType
{
	struct NodeType* prev;
	struct NodeType* next;
};

struct SoundInstance
{
	unsigned char channel;
	unsigned char state;
	unsigned char delay;
};

// Don't need the whole _G2Anim_Type struct right now
struct _G2Anim_Type
{
	char dummy[180];
};

struct EventAliasCommandStruct
{
	struct _Instance* hostInstance;
	short newanim;
	short newframe;
	short interpframes;
	short speed;
};

struct _Instance
{
	struct NodeType node;
	struct _Instance* next;
	struct _Instance* prev;
	long instanceID;
	long flags;
	long flags2;
	struct Object* object;
	struct Intro* intro;
	void* data;
	void* introData;
	struct _Instance* parent;
	long introNum;
	long birthStreamUnitID;
	long currentStreamUnitID;
	long introUniqueID;
	struct MATRIX* matrix;
	struct MATRIX* oldMatrix;
	struct SoundInstance soundInstanceTbl[4];
	unsigned long maxCheckDistance;
	unsigned long checkMask;
	struct _Position position;
	unsigned char lightGroup;
	struct _Position oldPos;
	unsigned char spectralLightGroup;
	short currentTextureAnimFrame;
	struct _Position initialPos;
	struct _Rotation rotation;
	struct _Rotation oldRotation;
	struct _SVector scale;
	long attachedID;
	long attachedSegment;
	struct MATRIX relativeMatrix;
	struct _TFace* tface;
	struct _TFace* oldTFace;
	void* tfaceLevel;
	void* collideInfo;
	long bspTree;
	short cachedTFace;
	short cachedBSPTree;
	void* cachedTFaceLevel;
	struct _Normal oldWNormal;
	struct _Normal wNormal;
	struct _SVector offset;
	//void* dsignal;
	//void* shadow0;
	//void* shadow1;
	//void* extraLight;
	//struct _Position extraLightDir;
	//short extraLightScale;
	struct _HModel* hModelList;
	short fadeValue;
	short lightMatrix;
	void (*processFunc)();
	void (*collideFunc)();
	void (*additionalCollideFunc)();
	//void* additionalDrawFunc;
	unsigned long (*queryFunc)();
	void (*messageFunc)();
	struct _Position shadowPosition;
	short currentModel;
	struct _TFace* waterFace;
	struct _TFace* oldWaterFace;
	struct _Terrain* waterFaceTerrain;
	struct _PlaneConstants halvePlane;
	struct _SVector splitPoint;
	struct _Instance* LinkParent;
	struct _Instance* LinkChild;
	struct _Instance* LinkSibling;
	long ParentLinkNode;
	void* InstanceState;
	char introName[16];
	void* extraData;
	short constrictAngle;
	short petrifyValue;
	long xVel;
	long yVel;
	long zVel;
	long xAccl;
	long yAccl;
	long zAccl;
	long maxXVel;
	long maxYVel;
	long maxZVel;
	long currentMainState;
	long currentSubState;
	long work0;
	long work1;
	long work2;
	long work3;
	long work4;
	long work5;
	long work6;
	long work7;
	long work8;
	long work9;
	struct _G2Anim_Type anim;
	enum _G2Bool_Enum(*rebuildCallback)();
	short splineFlags;
	short targetFrame;
	short clipBeg;
	short clipEnd;
	struct EventAliasCommandStruct aliasCommand;
	long light_color;
	struct CVECTOR* perVertexColor;
};

struct _InstanceList
{
	long numInstances;
	struct _Instance* first;
	struct _InstancePool* pool;
	struct NodeType group[32];
};
