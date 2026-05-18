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
	// Trainer Keys
	const int SetHour = VK_F4;
	const int ChangeSkin = VK_F5;
	const int SpawnCar = VK_F6;
	const int GodMode = VK_F7;
	const int KillNearby = VK_F8;
	const int Weather = VK_F9;
	const int InfMoney = VK_F11;
	const int ResetMoon = VK_F12;
	// Vehicle Controls
	const int FixVehicle = 0x58; // X
	const int ToggleLights = 0x32; // 2
}

typedef uint8_t byte;

class Trainer
{
public:
	void setHour(int h = -1);
	void setMoonSize(int scale);
	void setWeather(short weatherID);
	void toggleTaxiBoostJump(uint8_t c = -1);
	void toggleInfRun(uint8_t c = -1);
	void toggleGodMode(int c = -1);
	void giveMoney(int amount);
	void setMoney(int amount);

	short randomVeh();
public:
	int lastSkinChange = 0;
	int lastVehicleSpawned = 0;
	bool godMode = false;
public:
	void InstallHooks();
};

void onGameInit();

extern Trainer game;