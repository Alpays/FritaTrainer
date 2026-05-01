#include "player.h"

bool isPlayerInVehicle()
{
	CAutomobile* playerVeh = *(CAutomobile**)0x7E49C0;
	// Player vehicle pointer points to player itself when not driving so we are checking if player is driving a vehicle. 
	if ((uintptr_t)playerVeh != (uintptr_t)player)
	{
		return true;
	}
	return false;
}

void onPlayerKeyDown(WPARAM key)
{
	if(player == nullptr) player = *(CPed**)0x94AD28;
	switch (key)
	{
	case Key::ChangeSkin:
		if (time(NULL) - game.lastSkinChange > 1) {
			if (isPlayerInVehicle() == false)
			{
				player->changeSkin(rand() % 99);
			}
		}
		break;
	case Key::SpawnCar:
		if (time(NULL) - game.lastVehicleSpawned > 1) {
			if (isPlayerInVehicle() == false) {
				player->spawnCarNearby(game.randomVeh());
			}
		}
		break;
	case Key::InfSprint:
		game.toggleInfRun();
		break;
	case Key::KillNearby:
	{
		for (int i = 0; i < 10; ++i)
		{
			CPed* p = (CPed*)player->nearestPeds[i];
			if (p) {
				p->RemoveBodyPart(2, 0);
				p->health = 0.00f;
			}
		}
		break;
	}
	case Key::Weather:
		game.setWeather(rand() % 7);
		break;
	case Key::FixVehicle:
	{
		if (isPlayerInVehicle()) 
		{
			CAutomobile* playerVeh = *(CAutomobile**)0x7E49C0;
			playerVeh->Fix();
		}
		break;
	}
	case Key::InfMoney:
		game.giveMoney(99999999);
		break;
	case Key::TaxiJump:
		game.toggleTaxiBoostJump();
		break;
	case Key::ToggleLights:
	{
		if (isPlayerInVehicle())
		{
			CAutomobile* playerVeh = *(CAutomobile**)0x7E49C0;
			playerVeh->ToggleLights();
		}
		break;
	}
	}
}
