#pragma once

#include "trainer.h"

class Hook
{
public:
	uint8_t* targetAddr; // Address of where we are going to put our hook in the game.
	void* callAddr; // The call address, e.g. hook_onGameInit()

	std::vector<uint8_t> replacedBytes;

	Hook(); // We set addresses in this function.
	void StoreBytes(int c, ...); // We enter the bytes that are going to be saved.
	void Install(uint8_t* targetAddr, void* callAddr); // Installing our hook.
	void Remove(); // Remove our hook if needed.
};

void InstallHooks();

void onGameInit();

static Hook Render2DStuff;