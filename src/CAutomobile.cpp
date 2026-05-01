#include "CAutomobile.h"

void CAutomobile::Fix()
{
	// Fix the engine
	health = 1000.0f;
	// Call CAutomobile::Fix(), cosmetic fix.
	((void(__thiscall*)(CAutomobile*))0x588530)(this);
}

void CAutomobile::ToggleLights()
{
	lights = lights ^ 0xFF;
}