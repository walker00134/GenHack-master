# 🎮 GenyV2 (GENHACK v2)

**GENHACK v2 by Sorin** — Windows console tool that attaches to **GeneralsOnline** (C&C Generals Zero Hour, GitHub build ~2075) and toggles memory cheats via an F-key menu.

---

## ✨ Features

| Key       | Option                                    |
| --------- | ----------------------------------------- |
| **F1** 💰 | Hack Money (+1M)                          |
| **F2** ⭐ | Get 5000 XP                               |
| **F3** 🌟 | Get 20 Stars                              |
| **F4** ⚡ | Instant Special Power Recharge            |
| **F5** 📡 | Radar Hack                                |
| **F6** 📡 | Advanced Radar Hack (enable before match) |

Toggle with **F1–F6**, exit with **ESC**. **[X]** = enabled.

---

## 📋 Requirements

- **Windows** (x64 or x86)
- **Visual Studio 2022** (C++ Desktop)
- Game: `GeneralsOnlineZH_60.exe` with matching window title
- Run as **Administrator** if the game is elevated

---

## 📁 Project

- `GenyV2.cpp` — menu & F-key handling
- `Config.cpp` / `Config.h` — offsets, amounts, process name
- `MemoryManager.cpp` / `.h` — process attach, patches, RPM/WPM

---

## 🔨 Build

1. Open **GenyV2.slnx** in Visual Studio
2. Pick **Release | x64** (or Debug/Win32)
3. Build → `GenyV2\x64\Release\GenyV2.exe`

💡 If the icon fails, edit `GenyV2.rc` to point to your `.ico` or remove the icon.

---

## 🚀 Usage

1. Start **GeneralsOnline**, then run **GenyV2.exe**
2. Use **F1–F6** to toggle cheats
3. **ESC** to quit (patches stay until you turn them off or close the game)

"Process not found"? Check that the game window title and exe name match `Config.cpp`.

---

## ⚙️ Config

All values in **`Config.cpp`**: `PROCESS_NAME`, `WINDOW_TITLE`, money/XP/stars amounts and offsets, radar & special-power offsets. Edit and rebuild for other game versions.

---

## ⚠️ Disclaimer

For **educational / single-player use** only. Memory editing may violate ToS or server rules. Use at your own risk, the current offsets don't work on the updated patch, you have to find your own offsets using debuggers like cheatEngine. the offsets should be closer to the current ones -+ 0xFFF
