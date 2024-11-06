#pragma once

#include "SoulReaverStructures.h"

extern __Player& Raziel;
extern long* RazielCommands;
extern Camera& theCamera;
extern short& theCamera_LagZ;
extern _Instance* Raziel_Possessed;
extern _Instance*& gameTrackerX_playerInstance;
extern _Instance*& gameTrackerX_instanceList_first;
extern short& gameTrackerX_gameData_asmData_MorphType;
extern unsigned long& Raziel_Senses_EngagedMask;
extern __EngagedInstance*& Raziel_Senses_EngagedList;

/*int RazielCommands[] =
{
	 32768, // Glyph Menu
	 64,    // Devour Soul
	 32,    // Action
	 128,   // Jump
	 1024,  // Pan Left
	 2048,  // Pan Right
	 256,   // Crouch
	 512,   // Sneak
	 3072,  // Manual Aim
	 16
};*/

void __stdcall ProcessMovementPossessed(long* controlCommand, struct GameTracker* GT);