/*

FritaTrainer v0.3 (C++)

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

F4 - Fast forward time.
F5 - Change Skin
F6 - Spawn a vehicle.
F7 - Toggle Infinite health.
F8 - Eliminate nearby peds
F9 - Change Weather (0-6)
F11 - Give yourself money.
F12 - Reset moon size.

Vehicle Controls

X - Fix a vehicle
2- Toggle vehicle lights

Other Functionality: Taxi Boost Jump & Running Infinite has been activated by default.

v0.2 Updates

- Trainer code has been rewritten with a more clean and crash safe code
There are now memory protections, no assembly code, rewritten some of the game's
classes to access members through C++ instead of casting memory addresses.
- Added ability to run infinite
- Added ability to toggle vehicle lights.

v0.3 Updates

- Added a key to fast forward game hour by six hours.
- Fixed game crashing when trying to fix bikes.
- Added godmode.
- Added a hack to incrase moon size infinitely (F12 to manually reset back to smallest size)
- Infinite run and taxi boost jump has been enabled by default now.
- Added ability to high jump (X when not driving or holding sniper.)
- Eliminating nearby peds have various animmations now.
- Optimizations to the code.


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
        game.InstallHooks();
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

