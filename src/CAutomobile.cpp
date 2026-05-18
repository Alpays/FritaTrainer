#include "CAutomobile.h"

void CAutomobile::Fix()
{
	// Fix the engine
	health = 1000.0f;
	// Call CAutomobile::Fix(), cosmetic fix.
	if(vehicleType == 0) // calling this for vehicles other than cars crash the game.
		((void(__thiscall*)(CAutomobile*))0x588530)(this);
}

void CAutomobile::ToggleLights()
{
	lights = lights ^ 0xFF;
}