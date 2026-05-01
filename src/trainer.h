#pragma once


#define PAD(x, n) BYTE pad ## x[n]

extern int c; // Spawned car.

#include <Windows.h>
#include <random>
#include <stdint.h>

#include "scmscript.h"
#include "CPed.h"
#include "CAutomobile.h"
#include "player.h"

namespace Key
{
	const int ChangeSkin = VK_F5;
	const int SpawnCar = VK_F6;
	const int InfSprint = VK_F7;
	const int KillNearby = VK_F8;
	const int Weather = VK_F9;
	const int FixVehicle = 0x58; // X
	const int InfMoney = VK_F11;
	const int TaxiJump = VK_F12;
	const int ToggleLights = 0x32; // 2
}

typedef uint8_t byte;

class Trainer
{
public:
	void setMoonSize(int scale);
	void setWeather(short weatherID);
	void toggleTaxiBoostJump();
	void toggleInfRun();
	void giveMoney(int amount);
	void setMoney(int amount);

	short randomVeh();
public:
	int lastSkinChange = 0;
	int lastVehicleSpawned = 0;
};

extern Trainer game;