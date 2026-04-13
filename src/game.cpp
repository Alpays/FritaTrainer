#include "game.h"

uintptr_t* playerPtr = (uintptr_t*)0x94AD28;
int c = -1; // Created vehicle.

// So instead of selecting a random vehicle out of 100+ vehicles gta vc has 
// we only select from vehicles that could be useful you can check the veh ids from gta wikis
// I excluded some stuff that i didnt like so those categories doesnt include every veh, you can add your own here.
short vehiclePool[] =
{
    166, 178, 191, 192, 193, 198, // Bikes
    138, 137, 146, 150, 188, 216, 153, 163, 167, 161, // Cop cars Taxis Busses etc
    206, 141, 145, 207, 210, 211, 232, 132, 159, 142, // Sports/Gang cars
    155, 177, 199, 217, 218, 227, // Helis
    176, 160, 182, 202, 214, 223, // Boats
    225, 153, 154, 215 // Misc
};

/* Main loop of trainer, check if a key is pressed, give player health every 100ms if infinite health is enabled. */

void Game::process()
{
    checkKey();
    
    if (infiniteHealth) setHealth(255.0f);
}

void Game::giveMoney(int amount)
{
    int* money = (int*)0x94ADC8; // Mem Address for Money
    if (*money + amount > 9999999) *money = 9999999;
    else *money += amount;
}

void Game::changeSkin(int skinID)
{
    if (isPlayerMoving()) 
        return; // Changing skin while moving usually ends up in a crash.

    if (lastSkinChange == 0) lastSkinChange = time(NULL);
    else if (time(NULL) - lastSkinChange < 5) return; // Change the skin once 5 seconds to prevent crashes.

    // There are more skins but IDs above 105 are not defined in an .ide file so they can't be loaded like this.
    if (skinID >= 106) skinID = 0;

    // Request the game to load the model before setting it to prevent a game crash.

    scmScript(&request_model, skinID);
    scmScript(&load_reqmodels);

    while(!scmScript(&is_model_available, skinID))
        Sleep(1);

    uintptr_t player = *(playerPtr);

    __asm
    {
        mov ecx, player
        push skinID
        mov edx, 0x50D900
        call edx
    }

    scmScript(&release_model, skinID);

    lastSkinChange = time(NULL);

}

void Game::changeWeather(int weather)
{
    // Memory address of CWeather::ForceWeatherNow()
    typedef void* (__cdecl* fSetWeather)(short id);
    fSetWeather SetWeather = (fSetWeather)0x57D550;

    SetWeather(weather);
}

void Game::setHealth(float newhealth)
{
    float* health = (float*)((*playerPtr) + 0x354);

    *health = newhealth;
}

void Game::repairVehicle()
{
    int* playerVehPtr = (int*)0x7E49C0;

    /* 
    This pointer points to the car player is driving but if player isn't driving/fully entered
    the vehicle it points to player so we check if this address actually points to a car to prevent crashes.
    */
    if (*(uintptr_t*)playerVehPtr != *playerPtr) 
    {
        // CAutomobile::Fix() -- Fixes the car's look
        int playerVeh = *playerVehPtr;
        __asm
        {
            mov ecx, playerVeh; pointer to player vehicle
            mov eax, 0x588530; CAutomobile::Fix()
            call eax
        }
        // Set vehicle health to 1000.0f (250<means on fire(?))
        float* carHealth = (float*)(playerVeh + 0x204);
        *carHealth = 1000.0f;
    }
}

void Game::eliminateNearbyPeds()
{
    for (int i = 0; i < 10; ++i)
    {
        uintptr_t pedPtr = *(uintptr_t*)(*(uintptr_t*)playerPtr + 0x56C + (i * 4));
        if (pedPtr) {
            *(float*)(pedPtr + 0x354) = 0.00f;
        }
    }
}

void Game::spawnVeh(int model)
{
    // Load the vehicle model
    scmScript(&request_model, model);
    scmScript(&load_reqmodels);
     
    // Don't spawn the car until vehicle is loaded.
    while (!scmScript(&is_model_available, model)) Sleep(1);
    
    if (c != -1) // If a car is created delete it before creating a new one.
    {
        scmScript(&delete_vehicle, &c);
        c = -1;
    }

    float* pointerToCoord = (float*)((*playerPtr) + 0x034);

    float x = *pointerToCoord + 4.0f;
    float y = *(pointerToCoord + 1) + 4.0f;
    float z = *(pointerToCoord + 2) + 0.20f;

    scmScript(&create_vehicle, model, x, y, z, &c);
    scmScript(&release_model, model);

    Sleep(250);
}

void Game::checkKey()
{
    if (GetAsyncKeyState(Key::ChangeSkin) & 1)
    {
        changeSkin(rand() % 106);
    }
    if (GetAsyncKeyState(Key::SpawnCar) & 1)
    {
        spawnVeh(randomVeh());
    }
    if (GetAsyncKeyState(Key::InfHealth) & 1)
    {
        infiniteHealth = !infiniteHealth;
    }
    if (GetAsyncKeyState(Key::InfArmor) & 1)
    {
        eliminateNearbyPeds();
    }
    if (GetAsyncKeyState(Key::Weather) & 1)
    {
        changeWeather(rand() % 7); // Weather IDs above 6 are corrupted.
    }
    if (GetAsyncKeyState(Key::InfRunning) & 1)
    {
        repairVehicle();
    }
    if (GetAsyncKeyState(Key::InfMoney) & 1)
    {
        giveMoney(9999999);
    }
    if (GetAsyncKeyState(Key::TaxiJump) & 1)
    {
        *(uint8_t*)0xA10B3A = ~*(uint8_t*)0xA10B3A;
    }
}

short Game::randomVeh()
{
    int r = (rand() % (sizeof(vehiclePool) / sizeof(short)));
    return vehiclePool[r];
}

bool Game::isPlayerMoving()
{
    float* pointerToSpeed = (float*)((*playerPtr) + 0x070);

    float x, y;

    x = *pointerToSpeed;
    y = *(pointerToSpeed + 1);

    if (x == y && x == 0.00f)
        return false;

    return true;
}