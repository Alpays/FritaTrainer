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

static ushort* GetGxtPointer(const char* gxt_key)
{
    void* gxt_class = (void*)0x94B220;
    return ((ushort * (__thiscall*)(void*, const char*))0x584F30)(gxt_class, gxt_key);
}

void Trainer::cheatEnabled()
{
    SetHelpMessage("CHEAT1", true, 0);
}

void Trainer::SetHelpMessage(const char* gxt_key, bool isShort, int isPerma)
{
    ushort* gxtPointer = GetGxtPointer(gxt_key);
    ((void(__cdecl*)(ushort * gxtPointer, bool isShort, int isPerma))0x55BFC0)(gxtPointer, true, 0);
}

void Trainer::Announce(const char* gxt_key, uint milliseconds, uint style)
{
    ushort* gxtPointer = GetGxtPointer(gxt_key);
    ((void(__cdecl*)(ushort * gxtPointer, uint ms, uint style))0x583F40)(gxtPointer, milliseconds, style);
}