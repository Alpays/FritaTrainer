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

void Trainer::toggleTaxiBoostJump()
{
    DWORD oldProtect, np;
    DWORD* addr = (DWORD*)0xA10B3A;

    VirtualProtect(addr, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
    *addr = ~*addr;
    VirtualProtect(addr, 1, oldProtect, &np);
}

short Trainer::randomVeh()
{
    int r = (rand() % (sizeof(vehiclePool) / sizeof(short)));
    return vehiclePool[r];
}

void Trainer::toggleInfRun()
{
    DWORD oldProtect, np;
    DWORD* addr = (DWORD*)0x94AE68;

    VirtualProtect(addr, sizeof(byte), PAGE_EXECUTE_READWRITE, &oldProtect);
    *addr = ~*addr;
    VirtualProtect(addr, sizeof(byte), oldProtect, &np);
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
