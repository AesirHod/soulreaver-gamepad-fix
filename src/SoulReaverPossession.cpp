#include "stdafx.h"
#include "SoulReaverPossession.h"

__Player& Raziel = *reinterpret_cast<__Player*>(0x00B08418);
long* RazielCommands = reinterpret_cast<long*>(0x004FAD90);
Camera& theCamera = *reinterpret_cast<Camera*>(0x00C64560);
short& theCamera_LagZ = *reinterpret_cast<short*>(0x00C6465C);
_Instance* Raziel_Possessed = NULL;
unsigned long Raziel_possessedCheckMask = 0;
_Instance*& gameTrackerX_playerInstance = *reinterpret_cast<_Instance**>(0x00C66D4C);
_InstanceList*& gameTrackerX_instanceList = *reinterpret_cast<_InstanceList**>(0x00C66D54);
short& gameTrackerX_gameData_asmData_MorphType = *reinterpret_cast<short*>(0x00C66D2A);
unsigned long& Raziel_Senses_EngagedMask = *reinterpret_cast<unsigned long*>(0);
__EngagedInstance*& Raziel_Senses_EngagedList = *reinterpret_cast<__EngagedInstance**>(0);

inline __declspec(naked) int INSTANCE_Post(struct _Instance* Inst, int Message, int Data)
{
	__asm
	{
		mov eax, 0x004B1C70;
		jmp eax;
	}
}

inline __declspec(naked) int INSTANCE_Query(struct _Instance* Inst, int Query)
{
	__asm
	{
		mov eax, 0x004B1C50;
		jmp eax;
	}
}

inline __declspec(naked) int INSTANCE_InPlane(struct _Instance* instance, int plane)
{
	__asm
	{
		mov eax, 0x004B1DF0;
		jmp eax;
	}
}

inline __declspec(naked) void CAMERA_SetInstanceFocus(struct Camera* camera, struct _Instance *instance)
{
	__asm
	{
		mov eax, 0x00482FA0;
		jmp eax;
	}
}

inline __declspec(naked) int GetControllerInput(int* ZDirection, long* controlCommand)
{
	__asm
	{
		mov eax, 0x00454050;
		jmp eax;
	}
}

__declspec(dllexport) void MONAPI_PossessNext()
{
	struct _Instance* Inst;

	if (!Raziel_Possessed)
	{
		Raziel_Possessed = gameTrackerX_playerInstance;
	}

	Inst = Raziel_Possessed->next;

	if (!Inst)
	{
		Inst = gameTrackerX_instanceList->first;
	}

	if (Inst == Raziel_Possessed)
	{
		return;
	}

	while ((INSTANCE_Query(Inst, 1) & 0x0B) == 0 ||
		!INSTANCE_InPlane(Inst, gameTrackerX_gameData_asmData_MorphType))
	{
		Inst = Inst->next;
		if (!Inst)
		{
			Inst = gameTrackerX_instanceList->first;
		}

		if (Inst == Raziel_Possessed)
		{
			break;
		}
	}

	if (Inst == Raziel_Possessed)
	{
		return;
	}

	CAMERA_SetInstanceFocus(&theCamera, Inst);

	// Default checkmask = 0x803E002E - See InitStates

	if (Inst == gameTrackerX_playerInstance)
	{
		INSTANCE_Post(gameTrackerX_playerInstance, 0x01000010, 0);
		//gameTrackerX_playerInstance->checkMask = 0x803E002E;
		//gameTrackerX_playerInstance->flags2 |= 0x00000400;
		//Raziel_Possessed->checkMask = Raziel_possessedCheckMask;
		//Raziel_Possessed = NULL;
	}
	else
	{
		if (Raziel_Possessed != gameTrackerX_playerInstance)
		{
			INSTANCE_Post(Raziel_Possessed, 0x01000010, 0);
			//((_MonsterVars*)Raziel_Possessed->extraData)->mvFlags &= 0xFFF7FFFB;
		}

		INSTANCE_Post(Inst, 0x0100000F, 0);
		//((_MonsterVars*)Inst->extraData)->mvFlags |= 0x00080004;

		INSTANCE_Post(gameTrackerX_playerInstance, 0x0100000F, (int)Inst);
		//Raziel_Possessed = Inst;
		//gameTrackerX_playerInstance->checkMask = 0;
		//gameTrackerX_playerInstance->flags2 &= 0xFFFFFBFF;
		//Raziel_possessedCheckMask = Raziel_Possessed->checkMask;
		//Raziel_Possessed->checkMask |= 0x00000020;
	}

	Raziel_Possessed = Inst;

	//printf("Switching possession to %s\n", Inst->object->name);
}

int GetControllerMessagesPossession(long* controlCommand)
{
	int Event;

	if ((controlCommand[1] & RazielCommands[3]))
	{
		Event = 0x80000001;
	}
    else if ((controlCommand[2] & RazielCommands[3]))
    {
        Event = 0x20000001;
    }
    else if ((controlCommand[1] & RazielCommands[2]))
    {
        Event = 0x80000000;
    }
    else if ((controlCommand[2] & RazielCommands[2]))
    {
        Event = 0x20000000;
    }
    else if ((controlCommand[1] & RazielCommands[1]))
    {
        Event = 0x80000002;
    }
    else if ((controlCommand[2] & RazielCommands[1]))
    {
        Event = 0x20000002;
    }
    else if ((controlCommand[1] & RazielCommands[7]))
    {
        Event = 0x80000004;
    }
    else if ((controlCommand[2] & RazielCommands[7]))
    {
        Event = 0x20000004;
    }
    else if ((controlCommand[1] & RazielCommands[6]))
    {
        Event = 0x80000008;
    }
    else if ((controlCommand[2] & RazielCommands[6]))
    {
        Event = 0x20000008;
    }
    else if ((controlCommand[1] & RazielCommands[0]))
    {
        Event = 0x80000010;
    }
    else if ((controlCommand[1] & RazielCommands[9]))
    {
        Event = 0x80000020;
    }
    else if ((controlCommand[2] & RazielCommands[9]))
    {
        Event = 0x20000020;
    }
    else
    {
        Event = 0;
    }

	return Event;
}

void __stdcall ProcessMovementPossessed(long* controlCommand, struct GameTracker* GT)
{
	int ID = GetControllerMessagesPossession(controlCommand);
	int ZDirection;

	if (ID == 0)
	{
		ID = GetControllerInput(&ZDirection, controlCommand);
		ZDirection += theCamera_LagZ;

		if ((controlCommand[0] & RazielCommands[7]))
		{
			ID |= 0x00001000;
		}
	}
	else
	{
		ZDirection = 0;
	}

	INSTANCE_Post(Raziel_Possessed, ID, ZDirection);

	if ((Raziel_Senses_EngagedMask & 1) != 0)
	{
		INSTANCE_Post(Raziel_Possessed, 0x2000000, (int)(Raziel_Senses_EngagedList[0].instance));
	}
	if ((Raziel_Senses_EngagedMask & 8) != 0)
	{
		INSTANCE_Post(Raziel_Possessed, 0x2000008, (int)(Raziel_Senses_EngagedList[3].instance));
	}

	// Default checkmask = 0x803E002E - See InitStates
}

extern "C" __declspec(naked) void __stdcall SetStatesMod()
{
	__asm
	{
		mov eax, [0x00C66D4C]; // gameTrackerX.playerInstance
		mov ecx, [eax + 0x14]; // gameTrackerX.playerInstance->flags
		test ch, 0x01;
		jne SetStatesNone;
		mov eax, Raziel_Possessed;	
		test eax, eax;		
		jne SetStatesPossessed;
//SetStatesRaziel:
		mov eax, 0x00453157; // if ((ControlFlag & 0x800000))
		jmp eax;
SetStatesPossessed:
		call ProcessMovementPossessed;
		nop;
SetStatesNone:
		mov eax, 0x004538DE; // razSetPlayerEvent();
		jmp eax;
	}

	// PSX
	// if (!(gameTrackerX.playerInstance->flags & 0x100))
	// PC
	// v9 = *(dword_C66D4C + 20);
	// if ( BYTE1(v9) & 1 )
	// goto LABEL_130; // 0x004538DE - razSetPlayerEvent

	// PSX
	// if ((ControlFlag & 0x800000))
	// else GetControllerMessages(controlCommand);
	// PC
	// if (&unk_800000 & ControlFlag) // 0x00453157 - NoMovement?
	// else // 0x00453192 - GetControllerMessages

	// PSX
	// while ((message = DeMessageQueue(&Raziel.padCommands)) != NULL)
	// PC
	// v11 = DeMessageQueue(&unk_B08898); // 0x004532CF

	// PC sub_454050 - GetControllerInput
}