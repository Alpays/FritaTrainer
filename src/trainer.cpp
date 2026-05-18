#include "trainer.h"

typedef unsigned short ushort;
typedef unsigned int uint;

int c = 0;

short vehiclePool[] =
{
    166, 178, 191, 192, 193, 198, // Bikes
    138, 137, 146, 150, 188, 216, 153, 163, 167, 161, // Cop cars Taxis Busses etc
    206, 141, 145, 207, 210, 211, 232, 132, 159, 142, // Sports/Gang cars
    155, 177, 199, 217, 218, 227, // Helis
    176, 160, 182, 202, 214, 223, // Boats
    225, 153, 154, 215 // Misc
};

void Trainer::setMoonSize(int scale)
{
    DWORD oldProtect, np;
    DWORD* addr = (DWORD*)0x695680;

    VirtualProtect(addr, sizeof(int), PAGE_EXECUTE_READWRITE, &oldProtect);
    *addr = scale;
    VirtualProtect(addr, sizeof(int), oldProtect, &np);
}

void Trainer::setWeather(short weatherID)
{
    // Memory address of CWeather::ForceWeatherNow()
    ((void(__cdecl*)(short id))0x57D550)(weatherID);
}

void Trainer::toggleTaxiBoostJump(uint8_t c)
{
    DWORD oldProtect, np;
    uint8_t* addr = (uint8_t*)0xA10B3A;

    VirtualProtect(addr, sizeof(byte), PAGE_EXECUTE_READWRITE, &oldProtect);
    if (c == -1)
        *addr = ~*addr;
    else
        *addr = c;
    VirtualProtect(addr, sizeof(byte), oldProtect, &np);
}

short Trainer::randomVeh()
{
    int r = (rand() % (sizeof(vehiclePool) / sizeof(short)));
    return vehiclePool[r];
}

void Trainer::toggleInfRun(uint8_t c)
{
    DWORD oldProtect, np;
    uint8_t* addr = (uint8_t*)0x94AE68;

    VirtualProtect(addr, sizeof(byte), PAGE_EXECUTE_READWRITE, &oldProtect);
    if (c == -1)
        *addr = ~*addr;
    else
        *addr = c;
    VirtualProtect(addr, sizeof(byte), oldProtect, &np);
}

void Trainer::toggleGodMode(int c)
{
    if (c == -1) game.godMode = !game.godMode;
    else game.godMode = c;

    uint8_t* armorAddr = (uint8_t*)0x5266E6;

    uint8_t restoredBytes[] = { 0xD8, 0x64, 0x24, 0x6C };


    DWORD oldProtect, np;

    CPed* player = (CPed*)getPlayer();

    switch (game.godMode)
    {
        case 0:
            VirtualProtect((void*)armorAddr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
            for (int i = 0; i < 4; ++i) {
                memset((uint8_t*)armorAddr + i, restoredBytes[i], 1);
            }
            VirtualProtect((void*)armorAddr, 4, oldProtect, &np);

            player->armor = 1.0f;

            break;
        case 1:
            VirtualProtect((void*)armorAddr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
            memset((void*)armorAddr, 0x90, 4);
            VirtualProtect((void*)armorAddr, 4, oldProtect, &np);

            player->armor = 255.0f;
            break;
    }
}

void Trainer::giveMoney(int amount)
{
    DWORD oldProtect, np;
    DWORD* addr = (DWORD*)0x94ADC8;

    VirtualProtect(addr, sizeof(int), PAGE_EXECUTE_READWRITE, &oldProtect);
    *addr = *addr + amount;
    VirtualProtect(addr, sizeof(int), oldProtect, &np);
}

void Trainer::setMoney(int amount)
{
    DWORD oldProtect, np;
    DWORD* addr = (DWORD*)0x94ADC8;

    VirtualProtect(addr, sizeof(int), PAGE_EXECUTE_READWRITE, &oldProtect);
    *addr = amount;
    VirtualProtect(addr, sizeof(int), oldProtect, &np);
}

void Trainer::setHour(int hour)
{
    DWORD oldProtect, np;
    DWORD* addr = (DWORD*)0xA10B6B;

    VirtualProtect(addr, sizeof(uint8_t), PAGE_EXECUTE_READWRITE, &oldProtect);
    if (hour == -1)
        *addr = *addr + 6;
    else
        *addr = hour;

    if (*addr > 24) 
        *addr =  *addr % 24;
    VirtualProtect(addr, sizeof(uint8_t), oldProtect, &np);
}

// -- Game Internal Function Hooks --

static __declspec(naked) void hook_onGameInit()
{

    // Call our hooked init function, then execute the overrode bytes, then resume execution.
    _asm
    {
        pushad
        call onGameInit
        popad

        push ebx
        sub esp, 70h
        push 0

        mov eax, 0x4A6196
        jmp eax
    }    
}

void onGameInit()
{
    
    DWORD oldProtect, np;
   
    // Set Infinite Run & Taxi Boost jump by default

    game.toggleInfRun(1);
    game.toggleTaxiBoostJump(1);
    

    // Install our hack to prevent moon size resetting.
    
    DWORD moonAddr = 0x5CC8B1;

    VirtualProtect((void*)moonAddr, 3, PAGE_EXECUTE_READWRITE, &oldProtect);
    memset((void*)moonAddr, 0x90, 3);
    VirtualProtect((void*)moonAddr, 3, oldProtect, &np);
    
    // Since we executed our code lets remove our hook as we are not going to call it again.
    
    uint8_t* Render2DStuff = (uint8_t*)0x4A6190;
    uint8_t oldBytes[6] = { 0x53, 0x83, 0xEC, 0x70, 0x6A, 0x00 };
    

    VirtualProtect((void*)Render2DStuff, 6, PAGE_EXECUTE_READWRITE, &oldProtect);

    for (int i = 0; i < 6; ++i)
    {
        memset(Render2DStuff + i, oldBytes[i], 1);
    }

    VirtualProtect((void*)Render2DStuff, 6, oldProtect, &np);

    
}

void Trainer::InstallHooks()
{
    // Hook onGameInit() on Render2DStuff()
    uint8_t* Render2DStuff = (uint8_t*)0x4A6190;
    uintptr_t GameInit = (uintptr_t)hook_onGameInit;
    DWORD jumpAddr = (DWORD)GameInit - ((DWORD)Render2DStuff + 5);

    DWORD oldProtect, np;
    VirtualProtect((void*)Render2DStuff, 6, PAGE_EXECUTE_READWRITE, &oldProtect);

    memset(Render2DStuff, 0xE9, 1);
    memset(Render2DStuff + 1, jumpAddr         & 0xFF, 1);
    memset(Render2DStuff + 2, (jumpAddr >> 8)  & 0xFF, 1);
    memset(Render2DStuff + 3, (jumpAddr >> 16) & 0xFF, 1);
    memset(Render2DStuff + 4, (jumpAddr >> 24) & 0xFF, 1);
    memset(Render2DStuff + 5, 0x00, 1);

    VirtualProtect((void*)Render2DStuff, 6, oldProtect, &np);
}