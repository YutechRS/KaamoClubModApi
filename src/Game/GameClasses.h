#pragma once
#include <cstdint>
#include "Core/Memory.h"

#pragma pack(push, 1)

struct ShipInfo {
    int32_t max_cargo;      // 0x00
    char _pad0[0xC];
    int32_t cargo;          // 0x10
    char _pad1[0xC];
    int32_t armor;          // 0x20
};

struct SystemInfo {
    char _pad0[0x14];
    int32_t system_id;      // 0x14
};

// The main game object layout
struct GameContext {
    char _pad0[0x154];      // 0x000
    ShipInfo* ship_info;    // 0x154
    char _pad1[0x10];       // 0x158
    SystemInfo* system_info;// 0x168
    char _pad2[0x8];        // 0x16C
    int32_t money;          // 0x174
};

#pragma pack(pop)

// API Classes wrapping the structs

class Player {
public:
    static Player* Get() {
        // Player effectively wraps the GameContext for money, and provides access to Ship
        return (Player*)GetContext();
    }

    static GameContext* GetContext() {
        static uintptr_t base = Memory::GetModuleBase();
        uintptr_t ctxAddr = Memory::Read<uintptr_t>(base + 0x20AD6C);
        return (GameContext*)ctxAddr;
    }

    int GetMoney() {
        auto ctx = GetContext();
        return ctx ? ctx->money : 0;
    }

    void SetMoney(int value) {
        auto ctx = GetContext();
        if (ctx) ctx->money = value;
    }

    // For Lua property
    ShipInfo* ship_info() {
        auto ctx = GetContext();
        return ctx ? ctx->ship_info : nullptr;
    }
};

class System {
public:
    static System* Get() {
        auto ctx = Player::GetContext();
        return ctx ? (System*)ctx->system_info : nullptr;
    }

    // Mapped to SystemInfo struct
    int32_t system_id; // This needs to match offset 0 if we cast SystemInfo* to System*
                       // But SystemInfo starts with padding.
                       // We can't just cast SystemInfo* to System* if System has no padding.
                       // Better to bind SystemInfo directly or use accessors.
};

// Actually, let's just bind the structs directly in LuaManager for simplicity and efficiency.
// But the user wants "Player" class.
// So in LuaManager, I'll bind 'Player' as a usertype that holds nothing but static methods or retrieves the singleton.
