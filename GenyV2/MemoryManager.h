#pragma once

#include <windows.h>

// ============================
// Memory Management Functions
// ============================

namespace MemoryManager {
    // Get the base address of a module in a process
    uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
	uintptr_t GetPlayerBaseAddress(DWORD procId, HANDLE hProc, uintptr_t moduleBase);

    // Apply or remove the radar patch
    bool RadarHack(HWND hwnd, bool enable, bool isAdvanced);

    // Apply or remove the money cheat
    bool ApplyMoneyCheat(HWND hwnd, bool enable);

	bool ApplyXPCheat(HWND hwnd, bool enable);

	bool ApplyStarsCheat(HWND hwnd, bool enable);
	bool ApplySpecialPowerCheat(HWND hwnd, bool enable);
}
