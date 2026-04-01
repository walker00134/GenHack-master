#pragma once

#include <windows.h>

// ============================
// Configuration Constants
// ============================

namespace Config {

	//menu options
	extern const int singlePlayerOptionsCount;
	extern const int multiPlayerOptionsCount;
	extern const char* singlePlayerOptions[];
	extern const char* multiPlayerOptions[];

    // Process configuration
    extern const wchar_t* const PROCESS_NAME;
    extern const wchar_t* const WINDOW_TITLE;
    extern uintptr_t SIMPLE_RADAR_OFFSET;

	//advanced radar hack needs patch at two offsets
	extern uintptr_t ADVANCED_RADAR_OFFSET_1;
	extern uintptr_t ADVANCED_RADAR_OFFSET_2;

    // Money cheat configuration
    extern int MONEY_CHEAT_AMOUNT;
    extern uintptr_t MONEY_ADDRESS_OFFSET;

	//XP cheats consifguration
	extern uintptr_t PLAYER_BASE_OFFSET_1;
	extern uintptr_t PLAYER_BASE_OFFSET_2;
	extern uintptr_t XP_POINTER_OFFSET;
	extern uintptr_t STARS_POINTER_OFFSET;
	extern const int XP_CHEAT_AMOUNT;
	extern const int STARS_CHEAT_AMOUNT;

	//special power cheat configuration
	extern uintptr_t SPECIAL_POWER_OFFSET;
	extern uintptr_t SPECIAL_UPGRADES_OFFSET;

	// ASCII art as wide string
    extern const wchar_t* const ASCII_ART;
}
