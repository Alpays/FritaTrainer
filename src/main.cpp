/*

FritaTrainer v0.2 (C++)

This is a simple yet useful trainer for GTA: Vice City written in C++
It runs as an .asi file (which is a renamed .dll file) so unlike other trainers you don't have to run an application
all the time to use cheats. The cheats have keyboard shortcuts It has various cheats like
changing skin, spawning a vehicle etc.

The code to call scmScript has been written based on vcmp 0.1c source code, it executes a scm script
using game's internal function ProcessOneCommand() to execute a scm script, it has its own interpeter
and we call the function from Assembly after saving some values to the interpeter we made just like a vm, the source code
helped me with the ASM part and with the script structure.

Trainer Functions

Trainer Keys

F5 - Change Skin
F6 - Spawn a vehicle.
F7 - Toggle Infinite Run
F8 - Eliminate nearby peds
F9 - Change Weather (0-6)
F11 - Give yourself money.
F12 - Toggle Taxi boost jump.

Vehicle Controls

X - Fix a vehicle
2- Toggle vehicle lights

TO DO 
    Add Infinite Health
    Hook for Game Frame
    Hook for Game Init
    Remove Moon size resetting after shooting 7 times

v0.2 Updates

- Trainer code has been rewritten with a more clean and crash safe code
There are now memory protections, no assembly code, rewritten some of the game's
classes to access members through C++ instead of casting memory addresses.
- Added ability to run infinite
- Added ability to toggle vehicle lights.

- syaplA

*/


#include "trainer.h"

static LONG oldWndProc;

CPed* player = nullptr;
Trainer game;

static LRESULT CALLBACK WndProcSubclass(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_KEYDOWN:
    {
        onPlayerKeyDown(wParam);
    }
    default:
        return CallWindowProc((WNDPROC)oldWndProc, hWnd, uMsg, wParam, lParam);

    }
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        srand(time(NULL));
        oldWndProc = SetWindowLong(*(HWND*)0x7897A4, -4, (LONG)WndProcSubclass);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        player = nullptr;
        break;
    }
    return TRUE;
}

