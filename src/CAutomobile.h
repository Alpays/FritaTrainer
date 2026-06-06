#pragma once

#include "trainer.h"

class CPed;

class CAutomobile
{
public:
	PAD(0, 0x204);
	float health;

	PAD(1, 0x94);
	int vehicleType;

	PAD(2, 0x10);
	byte lights;
public:
	void Fix();
	void ToggleLights();
};
