#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cwchar>
#include "Config.h"
#include "MemoryManager.h"
#include "resource.h"

using namespace std;

void clearScreen() {
    system("cls");
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void showMenu(bool selected[], int lastPressed) {
    clearScreen();

    // Print ASCII art from Config with color using wide console API
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    setColor(13); // bright magenta/cyan-ish for ASCII
    DWORD written = 0;
    if (hOut != INVALID_HANDLE_VALUE) {
        WriteConsoleW(hOut, Config::ASCII_ART, (DWORD)wcslen(Config::ASCII_ART), &written, nullptr);
        WriteConsoleW(hOut, L"\n", 1, &written, nullptr);
    } else {
        // fallback
        wcout << Config::ASCII_ART << L"\n";
    }

    setColor(14); // bright yellow for header
    cout << "=====================================\n";
    cout << "       GENHACK v2 BY SORIN        \n";
    cout << "=====================================\n\n";
    setColor(7); // reset to normal for menu items

    std::cout << "[SINGLE PLAYER OPTIONS]\n";
    for (int i = 0; i < Config::singlePlayerOptionsCount; i++) {
        if (selected[i]) {
            setColor(10); // green
            cout << " [X] ";
        }
        else {
            cout << " [ ] ";
        }

        setColor(11); // bright cyan for option text
        cout << "[F" << (i + 1) << "] " << Config::singlePlayerOptions[i] << "\n";
        setColor(7);
    }

    std::cout << "\n[MULTIPLAYER OPTIONS]\n";
    for (int j = 0; j < Config::multiPlayerOptionsCount; j++) {
        int idx = Config::singlePlayerOptionsCount + j; // overall option index
        if (selected[idx]) {
            setColor(10); // green
            cout << " [X] ";
        }
        else {
            cout << " [ ] ";
        }

        setColor(11); // bright cyan for option text
        cout << "[F" << (idx + 1) << "] " << Config::multiPlayerOptions[j] << "\n";
        setColor(7);
    }

    cout << "\n=====================================\n";
    cout << "F1–F5 toggle | ENTER confirm | ESC exit\n";
}

int main() {
    // Keep CP settings optional; WriteConsoleW outputs wide text directly.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Optional: enable virtual terminal processing (useful for ANSI sequences later)
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (hOut != INVALID_HANDLE_VALUE && GetConsoleMode(hOut, &mode)) {
        SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

    int totalOptions = Config::singlePlayerOptionsCount + Config::multiPlayerOptionsCount;
    bool* selected = new bool[totalOptions]();
    int lastPressed = -1;

    while (true) {
        showMenu(selected, lastPressed);

        int key = _getch();

        if (key == 27) // ESC
            break;
        // Function keys
        if (key == 0 || key == 224) {
            key = _getch();

            int option = -1;

            switch (key) {
            case 59: option = 0; break; // F1
            case 60: option = 1; break;
            case 61: option = 2; break;
            case 62: option = 3; break;
            case 63: option = 4; break;
			case 64: option = 5; break;
            }

            if (option != -1 && option < totalOptions) {
                selected[option] = !selected[option];
                lastPressed = option;
                switch (option) {
                case 0: // Hack Money
                    MemoryManager::ApplyMoneyCheat(NULL, selected[option]);
                    break;
                case 1: // Get 5000 XP
					MemoryManager::ApplyXPCheat(NULL, selected[option]);
                    break;
                case 2: // Get 20 Stars
					MemoryManager::ApplyStarsCheat(NULL, selected[option]);
					break;
				case 3: // Instant Special Power Recharge
					MemoryManager::ApplySpecialPowerCheat(NULL, selected[option]);

                case 4: // Radar Hack
                    MemoryManager::RadarHack(NULL, selected[option], false);
                    break;
				case 5: // Advanced Radar Hack
                    MemoryManager::RadarHack(NULL, selected[option], true);
					break;
                }
                showMenu(selected, lastPressed);
                Sleep(700);
            }
        }
    }

    delete[] selected;
    setColor(7);
    return 0;
}
