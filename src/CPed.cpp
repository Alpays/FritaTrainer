#include "CPed.h"


void CPed::RemoveBodyPart(int nodeId, int direction)
{
	((void(__thiscall*)(CPed*, int, int))0x5259F0)(this, nodeId, direction);
}

void CPed::changeSkin(int skinID)
{
    game.lastSkinChange = (int)time(NULL);

    if (isMoving())
        return; // Changing skin while moving usually ends up in a crash.

    if (skinID >= 99) skinID = 0;

    // Request the game to load the model before setting it to prevent a game crash.

    scmScript(&request_model, skinID);
    scmScript(&load_reqmodels);

    while (!scmScript(&is_model_available, skinID))
        Sleep(1);

    ((int(__thiscall*)(CPed*, int skinID))0x50D900)(this, skinID);

    scmScript(&release_model, skinID);
}

bool CPed::isMoving()
{
    if (sX == sY && sX == 0.00f)
        return false;

    return true;
}

void CPed::spawnCarNearby(int model)
{
    game.lastVehicleSpawned = (int)time(NULL);

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

    scmScript(&create_vehicle, model, x + 1.50f, y + 1.50f, z + 0.33f, &c);
    scmScript(&release_model, model);
}