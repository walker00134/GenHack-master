#include "MemoryManager.h"
#include "Config.h"
#include <tlhelp32.h>
#include <iostream>
// ============================
// Memory Management Implementation
// ============================

namespace MemoryManager {
    uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName) {
        uintptr_t modBaseAddr = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

        if (hSnap != INVALID_HANDLE_VALUE) {
            MODULEENTRY32 modEntry{ sizeof(modEntry) };
            if (Module32First(hSnap, &modEntry)) {
                do {
                    if (!_wcsicmp(modEntry.szModule, modName)) {
                        modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                        break;
                    }
                } while (Module32Next(hSnap, &modEntry));
            }
        }
        CloseHandle(hSnap);
        return modBaseAddr;
    }

    bool RadarHack(HWND hwnd, bool enable, bool isAdvanced = false) {
        DWORD procId = 0;
        HWND hGame = FindWindow(NULL, Config::WINDOW_TITLE);
        GetWindowThreadProcessId(hGame, &procId);

        if (!procId) {
			std::cout << "Process not found." << std::endl;
            return false;
        }

        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
        uintptr_t base = GetModuleBaseAddress(procId, Config::PROCESS_NAME);

        if (!base) {
			std::cout << "Failed to get module base address." << std::endl;
            CloseHandle(hProc);
            return false;
        }

		// Simple radar hack implementation
        if (!isAdvanced) {
            uintptr_t addr1 = base + Config::SIMPLE_RADAR_OFFSET;
            BYTE value = enable ? 0x01 : 0x00;

            DWORD oldProtect;
            VirtualProtectEx(hProc, (LPVOID)(addr1 + 1), sizeof(value),
                PAGE_EXECUTE_READWRITE, &oldProtect);

            WriteProcessMemory(hProc, (LPVOID)(addr1 + 1), &value, sizeof(value), nullptr);
            VirtualProtectEx(hProc, (LPVOID)(addr1 + 1), sizeof(value),
                oldProtect, &oldProtect);

            CloseHandle(hProc);
            return true;
        }
        else {
			uintptr_t addr1 = base + Config::ADVANCED_RADAR_OFFSET_1; // for showing units
			uintptr_t addr2 = base + Config::ADVANCED_RADAR_OFFSET_2; // for showing buildings
			BYTE value1 = enable ? 0x01 : 0x03; // 0x01 to enable, 0x03 to disable
            BYTE value2 = enable ? 0x01 : 0x04; // 0x01 to enable, 0x04 to disable

            DWORD oldProtect;
            VirtualProtectEx(hProc, (LPVOID)(addr1 + 2), sizeof(value1),
                PAGE_EXECUTE_READWRITE, &oldProtect);
            VirtualProtectEx(hProc, (LPVOID)(addr2 + 2), sizeof(value2),
                PAGE_EXECUTE_READWRITE, &oldProtect);

            WriteProcessMemory(hProc, (LPVOID)(addr1 + 2), &value1, sizeof(value1), nullptr);
            WriteProcessMemory(hProc, (LPVOID)(addr2 + 2), &value2, sizeof(value2), nullptr);
            VirtualProtectEx(hProc, (LPVOID)(addr1 + 2), sizeof(value1),
                oldProtect, &oldProtect);
            VirtualProtectEx(hProc, (LPVOID)(addr2 + 2), sizeof(value1),
                oldProtect, &oldProtect);
            CloseHandle(hProc);
            return true;
        }

        
    }

    bool ApplyMoneyCheat(HWND hwnd, bool enable) {
        if (!enable) {
            // If disabling, we don't need to do anything for now
            return true;
        }

        DWORD procId = 0;
        HWND hGame = FindWindow(NULL, Config::WINDOW_TITLE);
        GetWindowThreadProcessId(hGame, &procId);

        if (!procId) {
			std::cout << "Process not found." << std::endl;
            return false;
        }

        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
        uintptr_t base = GetModuleBaseAddress(procId, Config::PROCESS_NAME);

        if (!base) {
			std::cout << "Failed to get module base address." << std::endl;
            CloseHandle(hProc);
            return false;
        }

        // Pointer chain navigation using config values
		uintptr_t moneyAddress = GetPlayerBaseAddress(procId, hProc, base) + Config::MONEY_ADDRESS_OFFSET;


        // Read current money value
        int currentMoney = 0;
        if (!ReadProcessMemory(hProc, (LPCVOID)moneyAddress, &currentMoney, sizeof(currentMoney), NULL)) {
			std::cout << "Failed to read current money value." << std::endl;
            return false;
        }

        // Calculate new money amount (add cheat amount to current)
        int newAmount = currentMoney + Config::MONEY_CHEAT_AMOUNT;

        // Write the new money value
        DWORD oldProtect;
        VirtualProtectEx(hProc, (LPVOID)moneyAddress, sizeof(newAmount),
            PAGE_EXECUTE_READWRITE, &oldProtect);

        WriteProcessMemory(hProc, (LPVOID)moneyAddress, &newAmount, sizeof(newAmount), NULL);

        VirtualProtectEx(hProc, (LPVOID)moneyAddress, sizeof(newAmount),
            oldProtect, &oldProtect);

        CloseHandle(hProc);
        return true;
    }
    bool ApplyXPCheat(HWND hwnd, bool enable) {
        if (!enable) {
            // If disabling, we don't need to do anything for now
            return true;
        }
        DWORD procId = 0;
        HWND hGame = FindWindow(NULL, Config::WINDOW_TITLE);
        GetWindowThreadProcessId(hGame, &procId);
        if (!procId) {
            std::cout << "Process not found." << std::endl;
            return false;
        }
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
        uintptr_t base = GetModuleBaseAddress(procId, Config::PROCESS_NAME);
        if (!base) {
            std::cout << "Failed to get module base address." << std::endl;
            CloseHandle(hProc);
            return false;
        }
        // Pointer chain navigation using config values
		uintptr_t pointerBase = GetPlayerBaseAddress(procId, hProc, base);
        uintptr_t targetAddress = pointerBase + Config::XP_POINTER_OFFSET;
        // Write the new value
        DWORD oldProtect;
        int newAmount = Config::XP_CHEAT_AMOUNT;
        VirtualProtectEx(hProc, (LPVOID)targetAddress, sizeof(newAmount),
            PAGE_EXECUTE_READWRITE, &oldProtect);
        WriteProcessMemory(hProc, (LPVOID)targetAddress, &newAmount, sizeof(newAmount), NULL);
        VirtualProtectEx(hProc, (LPVOID)targetAddress, sizeof(newAmount),
            oldProtect, &oldProtect);
        CloseHandle(hProc);
        return true;
    }

    bool ApplyStarsCheat(HWND hwnd, bool enable) {
        if (!enable) {
            // If disabling, we don't need to do anything for now
            return true;
        }
        DWORD procId = 0;
        HWND hGame = FindWindow(NULL, Config::WINDOW_TITLE);
        GetWindowThreadProcessId(hGame, &procId);
        if (!procId) {
            std::cout << "Process not found." << std::endl;
            return false;
        }
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
        uintptr_t base = GetModuleBaseAddress(procId, Config::PROCESS_NAME);
        if (!base) {
            std::cout << "Failed to get module base address." << std::endl;
            CloseHandle(hProc);
            return false;
        }
        // Pointer chain navigation using config values
		uintptr_t pointerBase = GetPlayerBaseAddress(procId, hProc, base);
       
        uintptr_t targetAddress = pointerBase + Config::STARS_POINTER_OFFSET;
        
        // Write the new value
        DWORD oldProtect;
        int newAmount = Config::STARS_CHEAT_AMOUNT;
        VirtualProtectEx(hProc, (LPVOID)targetAddress, sizeof(newAmount),
            PAGE_EXECUTE_READWRITE, &oldProtect);
        WriteProcessMemory(hProc, (LPVOID)targetAddress, &newAmount, sizeof(newAmount), NULL);
        VirtualProtectEx(hProc, (LPVOID)targetAddress, sizeof(newAmount),
            oldProtect, &oldProtect);
        CloseHandle(hProc);
        return true;
	}

    uintptr_t GetPlayerBaseAddress(DWORD procId, HANDLE hProc, uintptr_t moduleBase) {
        uintptr_t pointerBase = moduleBase + Config::PLAYER_BASE_OFFSET_1;
        DWORD playerPointer1 = 0;
        if (!ReadProcessMemory(hProc, (LPCVOID)pointerBase, &playerPointer1, sizeof(DWORD), NULL) || playerPointer1 == 0) {
            std::cout << "Failed to read player address." << std::endl;
            return 0;
        }
		uintptr_t playerAddr = playerPointer1 + Config::PLAYER_BASE_OFFSET_2;
		DWORD playerAddrFinal = 0;
		if (!ReadProcessMemory(hProc, (LPCVOID)playerAddr, &playerAddrFinal, sizeof(DWORD), NULL) || playerAddrFinal == 0) {
			std::cout << "Failed to read final player address." << std::endl;
			return 0;
		}
        return playerAddrFinal;
	}
    bool ApplySpecialPowerCheat(HWND hwnd, bool enable) {
        DWORD procId = 0;
        HWND hGame = FindWindow(NULL, Config::WINDOW_TITLE);
        GetWindowThreadProcessId(hGame, &procId);
        if (!procId) {
            std::cout << "Process not found." << std::endl;
            return false;
        }
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
        uintptr_t base = GetModuleBaseAddress(procId, Config::PROCESS_NAME);
        if (!base) {
            std::cout << "Failed to get module base address." << std::endl;
            CloseHandle(hProc);
            return false;
        }
        uintptr_t SWaddr = base + Config::SPECIAL_POWER_OFFSET;
		uintptr_t upgradesAddr = base + Config::SPECIAL_UPGRADES_OFFSET;
        //nop the instruction "add eax,[edx+18]" which means we need to inject 3 0x90 bytes
        // Define the bytes for both states
        BYTE nops[] = { 0x90, 0x90, 0x90 };          // NOP NOP NOP
        BYTE originalSW[] = { 0x03, 0x42, 0x18 };      // add eax, [edx+18]
		BYTE originalUpgrades[] = { 0x89, 0x86, 0x0C }; // mov [esi+0C],eax

        // Choose which buffer to use
        BYTE* patchSW = enable ? nops : originalSW;
		BYTE* patchUpgrades = enable ? nops : originalUpgrades;
        size_t size = sizeof(originalSW); // 3 bytes
        DWORD oldProtect;
        // 1. Change protection
        if (VirtualProtectEx(hProc, (LPVOID)SWaddr, size, PAGE_EXECUTE_READWRITE, &oldProtect)) {
            // 2. Write the 3-byte buffer
            WriteProcessMemory(hProc, (LPVOID)SWaddr, patchSW, size, nullptr);

            // 3. Restore protection
            VirtualProtectEx(hProc, (LPVOID)SWaddr, size, oldProtect, &oldProtect);
        }
        if (VirtualProtectEx(hProc, (LPVOID)upgradesAddr, size, PAGE_EXECUTE_READWRITE, &oldProtect)) {
            WriteProcessMemory(hProc, (LPVOID)upgradesAddr, patchUpgrades,
                size, nullptr);
            VirtualProtectEx(hProc, (LPVOID)upgradesAddr, size, oldProtect, &oldProtect);
        }
            CloseHandle(hProc);
        return true;
    }

}
