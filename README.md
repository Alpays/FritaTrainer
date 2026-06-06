# FritaTrainer v0.4 (C++)

This is a trainer for GTA: Vice City written in C++
It runs as an .asi file (which is a renamed .dll file) so unlike other trainers you don't have to run an application
all the time to use cheats. The cheats have keyboard shortcuts It has various cheats like
changing skin, spawning a vehicle etc. 

I made this to learn more about reverse engineering and game hacking, there is no other open source GTA: Vice City trainer out there in GitHub and this trainer features various game hacking techniques such as function hooking, calling internal functions and memory editing. It can be useful if you want to make your own trainer for gta vc or your own mod for gta3/sa/vc games. 

<img width="1920" height="1080" alt="Ekran Görüntüsü (9994)" src="https://github.com/user-attachments/assets/5e26185a-8223-46c5-b441-26747edc0118" />


# Trainer Functions

-- Trainer Keys

- F5 - Change Skin 
- F6 - Spawn a vehicle.
- F7 - Toggle god mode.
- F8 - Eliminate nearby peds
- F9 - Change Weather (0-6)
- F11 - Give yourself money.
- F12 - Toggle Taxi boost jump.

-- Vehicle Controls

- X - Fix a vehicle (high jump when not in a vehicle.)
- 2- Toggle vehicle lights (The game only renders vehicle lights at night)

# v0.2 Updates

- Trainer code has been rewritten with a more clean and crash safe code
There are now memory protections, no assembly code, rewritten some of the game's
classes to access members through variables instead of casting memory addresses.
- Added ability to run infinite
- Added ability to toggle vehicle lights.

# v0.3 Updates

- Added a key to fast forward game hour by six hours.
- Fixed game crashing when trying to fix bikes.
- Added godmode.
- Added a hack to incrase moon size infinitely (F12 to manually reset back to smallest size)
- Infinite run and taxi boost jump has been enabled by default now.
- Added ability to high jump (X when not driving or holding sniper.)
- Nearby peds now have different death anims.
- Optimizations to the code.

  # v0.4 Updates

- Added a class to add hooks.
- Added 'Cheat Activated' message when using some cheats.
