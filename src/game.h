#pragma once

#include <Windows.h>
#include <random>

#include "scmscript.h"

namespace Key
{
	const int ChangeSkin =	VK_F5;
	const int SpawnCar =	VK_F6;
	const int InfHealth =	VK_F7;
	const int InfArmor =	VK_F8;
	const int Weather =		VK_F9;
	const int InfRunning =	VK_F10;
	const int InfMoney =	VK_F11;
	const int TaxiJump =	VK_F12;
}

struct Game
{
	bool infiniteHealth = false;

	int lastSkinChange = 0;


	void checkKey();
	void process();
	short randomVeh();

	void changeSkin(int skinID);
	void spawnVeh(int model = 145);
	void changeWeather(int weather = 4);
	void giveMoney(int money);
	void repairVehicle();
	void setHealth(float health);
	void eliminateNearbyPeds();

	bool isPlayerMoving();

};
