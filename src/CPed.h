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
	CPed* nearestPeds[10];
	PAD(4, 0x78);
	uint8_t weaponSlot;

	void RemoveBodyPart(int nodeId, int direction);
	void changeSkin(int skinID);
	void spawnCarNearby(int carID); // This one is not a function call/not an original CPed func from the game.

	bool isMoving();

};
