#pragma once

#include "trainer.h"

class CAutomobile
{
public:
	PAD(0, 0x204);
	float health;
	PAD(1, 0xA8);
	byte lights;
public:
	void Fix();
	void ToggleLights();
};
