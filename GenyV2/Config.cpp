#include "Config.h"

// ============================
// Configuration Constants Implementation
// ============================

namespace Config {
    // menu option arrays
    const char* singlePlayerOptions[] = {
        "Hack Money 1000000+",
        "Get 5000 XP",
        "GET 20 Stars", 
		"Instant Special Power Recharge(SW, Upgrades)",
    };
    const int singlePlayerOptionsCount = static_cast<int>(sizeof(singlePlayerOptions) / sizeof(singlePlayerOptions[0]));

    const char* multiPlayerOptions[] = {
        "Radar Hack",
		"Advanced Radar Hack (Activate before match start) "
    };
    const int multiPlayerOptionsCount = static_cast<int>(sizeof(multiPlayerOptions) / sizeof(multiPlayerOptions[0]));

    // Process configuration
    const wchar_t* const PROCESS_NAME = L"GeneralsOnlineZH_60.exe";
    const wchar_t* const WINDOW_TITLE = L"GeneralsOnline ~2075 By Generals Online Development Team | GitHub Buildserver for Command & Conquer (TM) Generals Zero Hour Version 1.04";
    uintptr_t SIMPLE_RADAR_OFFSET = 0x3C6351; // "push 00" 

	//advanced radar hack needs patch at two offsets
	uintptr_t ADVANCED_RADAR_OFFSET_1 = 0x1D0EF0; //for showing units
	uintptr_t ADVANCED_RADAR_OFFSET_2 = 0x1D0F5C; //for showing buildings

    // Money cheat configuration
    uintptr_t PLAYER_BASE_OFFSET_1 = 0x006A21F8; // pointer that points to the player when adding the next offset 0xC
    uintptr_t PLAYER_BASE_OFFSET_2 = 0xC; // player object
    int MONEY_CHEAT_AMOUNT = 1000000;
    uintptr_t MONEY_ADDRESS_OFFSET = 0x38; // Final offset to money value

	//XP cheats Offsets
	uintptr_t XP_POINTER_OFFSET = 0x02D8; // Offset for XP pointer dereference
	uintptr_t STARS_POINTER_OFFSET = 0x02DC; // Offset for Stars pointer dere
	//XP and Stars cheat amounts
	const int XP_CHEAT_AMOUNT = 5000;
	const int STARS_CHEAT_AMOUNT = 20;

	//special power cheat offset
	uintptr_t SPECIAL_POWER_OFFSET = 0x2BE243; // 
	uintptr_t SPECIAL_UPGRADES_OFFSET = 0x155098; // mov [esi+0C],eax

	// ASCII art as wide raw literal
    const wchar_t* const ASCII_ART = LR"(
         ██████╗ ███████╗███╗   ██╗██╗  ██╗ █████╗  ██████╗██╗  ██╗ 
        ██╔════╝ ██╔════╝████╗  ██║██║  ██║██╔══██╗██╔════╝██║ ██╔╝
        ██║  ███╗█████╗  ██╔██╗ ██║███████║███████║██║     █████╔╝ 
        ██║   ██║██╔══╝  ██║╚██╗██║██╔══██║██╔══██║██║     ██╔═██╗ 
        ╚██████╔╝███████╗██║ ╚████║██║  ██║██║  ██║╚██████╗██║  ██╗ 
         ╚═════╝ ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝ 
    )";
}
