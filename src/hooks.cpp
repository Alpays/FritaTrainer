#include "hooks.h"

Hook::Hook()
{

}

void Hook::StoreBytes(int c, ...)
{
	va_list bytes;

	va_start(bytes, c);

	for (int i = 0; i < c; ++i) {
		replacedBytes.push_back(va_arg(bytes, uint8_t));
	}

	va_end(bytes);
}

void Hook::Install(uint8_t* t, void* c)
{
    targetAddr = t;
    callAddr = c;
    DWORD jumpAddr = (DWORD)callAddr - ((DWORD)targetAddr + 5);

    DWORD oldProtect, np;
    VirtualProtect((void*)targetAddr, replacedBytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);

    memset(targetAddr,     0xE9, 1);
    memset(targetAddr + 1, jumpAddr & 0xFF, 1);
    memset(targetAddr + 2, (jumpAddr >> 8)  & 0xFF, 1);
    memset(targetAddr + 3, (jumpAddr >> 16) & 0xFF, 1);
    memset(targetAddr + 4, (jumpAddr >> 24) & 0xFF, 1);
    memset(targetAddr + 5, 0x00, 1);

    VirtualProtect((void*)targetAddr, replacedBytes.size(), oldProtect, &np);
}

void Hook::Remove()
{
    DWORD oldProtect, np;

    VirtualProtect(targetAddr, replacedBytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
        
    for (uint8_t i = 0; i < replacedBytes.size(); ++i)
    {
        memset((uint8_t*)targetAddr + i, replacedBytes[i], 1);
    }
        
    VirtualProtect(targetAddr, replacedBytes.size(), oldProtect, &np);
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

    Render2DStuff.Remove();
}

void InstallHooks()
{
    Render2DStuff.StoreBytes(6, 0x53, 0x83, 0xEC, 0x70, 0x6A, 0x00);
    Render2DStuff.Install((uint8_t*)0x4A6190, &hook_onGameInit);
}
