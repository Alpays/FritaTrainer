#include "player.h"

uintptr_t getPlayer()
{
	return *(uintptr_t*)0x94AD28;
}


bool isPlayerInVehicle()
{
	CAutomobile* playerVeh = *(CAutomobile**)0x7E49C0;
	// Player vehicle pointer points to player itself when not driving so we are checking if player is driving a vehicle. 
	if ((uintptr_t)playerVeh != getPlayer())
	{
		return true;
	}
	return false;
}

void onPlayerKeyDown(WPARAM key)
{
	CPed* player = (CPed*)getPlayer();
	switch (key)
	{
	case Key::SetHour:
		game.setHour();
		break;
	case Key::ChangeSkin:
		if (time(NULL) - game.lastSkinChange > 1) {
			if (isPlayerInVehicle() == false)
			{
				player->changeSkin(rand() % 99);
				game.cheatEnabled();
			}
		}
		break;
	case Key::SpawnCar:
		if (time(NULL) - game.lastVehicleSpawned > 1) {
			if (isPlayerInVehicle() == false) {
				player->spawnCarNearby(game.randomVeh());
				game.cheatEnabled();
			}
		}
		break;
	case Key::GodMode:
		game.toggleGodMode();
		if(game.godMode)
			game.cheatEnabled();
		break;
	case Key::KillNearby:
	{
		CPed* p = (CPed*)getPlayer();
		for (int i = 0; i < 10; ++i)
		{
			CPed* nearestPed = p->nearestPeds[i];
			if (nearestPed) {
				nearestPed->RemoveBodyPart(rand() % 10 + 1, 0);
				nearestPed->health = 0.00f;
				game.cheatEnabled();
			}
		}
		break;
	}
	case Key::Weather:
		game.setWeather(rand() % 7);
		game.cheatEnabled();
		break;
	case Key::FixVehicle:
	{
		if (isPlayerInVehicle())
		{
			CAutomobile* playerVeh = *(CAutomobile**)0x7E49C0;
			playerVeh->Fix();
			game.cheatEnabled();
		}
		else
		{
			// also check if player is sniping as x key is used for sniper scope.
			if(player->weaponSlot != 8)
				player->z += 5.00f;
		}
		break;
	}
	case Key::InfMoney:
		game.giveMoney(99999999);
		game.cheatEnabled();
		break;
	case Key::ResetMoon:
		game.setMoonSize(0);
		game.cheatEnabled();
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
