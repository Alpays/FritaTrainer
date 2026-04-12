/*

FritaTrainer v0.1 (C++)

This is a simple yet useful trainer for GTA: Vice City written in C++
It runs as an .asi file (which is a renamed .dll file) so unlike other trainers you don't have to run an application
all the time to use cheats. The cheats have keyboard shortcuts ranging from F5 to F12, it has various cheats like
changing skin, spawning a vehicle and infinite money/health etc.

I tried to write the code in a very simple and understandable way so if you are into gta modding it might be useful to
learn how to edit memory / call functions addresses etc.

The code to call scmScript has been written based on vcmp 0.1c source code, it executes a scm script
using game's internal function ProcessOneCommand() to execute a scm script, it has its own interpeter
and we call the function from Assembly after saving some values to the interpeter we made just like a vm, the source code 
helped me with the ASM part and with the script structure.

Keys

F5 - Change Skin
F6 - Spawn a Supercar / Heli / PCJ
F7 - Infinite Health toggle
F8 - Eliminate nearby peds
F9 - Change Weather (0-6)
F10 - Fix vehicle
F11 - Infinite Money
F12 - Toggle Taxi boost jump.

- syaplA

*/

#include "game.h"
Game game;

DWORD WINAPI MainThread(LPVOID lpParam)
{
    srand(time(NULL));

    while (1)
    {
        game.process();
        Sleep(10);
    }

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            CreateThread(0, 0, MainThread, hModule, 0, 0);
    }
    return TRUE;
}

