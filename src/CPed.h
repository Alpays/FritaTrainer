#pragma once

#include "trainer.h"

class CPed
{
public:
	PAD(0, 0x34);
	float x, y, z;
	PAD(1, 0x30);
	float sX, sY, sZ;
	PAD(2, 0x2D8);
	float health;
	float armor;
	PAD(3, 0x210);
	uintptr_t* nearestPeds[10];

	void RemoveBodyPart(int nodeId, int direction);
	void changeSkin(int skinID);
	void spawnCarNearby(int carID); // This one is not a function call/not an original CPed func from the game.

	bool isMoving();

};

extern CPed* player;