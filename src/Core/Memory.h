#pragma once
#include <windows.h>
#include <vector>
#include <optional>
#include <concepts>
#include "Logger.h"

class Memory {
public:
    static uintptr_t GetModuleBase(const std::string& moduleName = "") {
        return (uintptr_t)GetModuleHandleA(moduleName.empty() ? nullptr : moduleName.c_str());
    }

    template<typename T>
    static T Read(uintptr_t address) {
        if (IsBadReadPtr((void*)address, sizeof(T))) {
            Logger::Log("Invalid read at {:x}", address);
            return T{};
        }
        return *(T*)address;
    }

    template<typename T>
    static void Write(uintptr_t address, T value) {
        if (IsBadWritePtr((void*)address, sizeof(T))) {
            DWORD oldProtect;
            VirtualProtect((void*)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);
            *(T*)address = value;
            VirtualProtect((void*)address, sizeof(T), oldProtect, &oldProtect);
        } else {
            *(T*)address = value;
        }
    }

    static uintptr_t ResolvePointerChain(uintptr_t base, const std::vector<uintptr_t>& offsets) {
        uintptr_t addr = base;
        for (size_t i = 0; i < offsets.size(); ++i) {
            addr = Read<uintptr_t>(addr);
            if (!addr) return 0;
            addr += offsets[i];
        }
        return addr;
    }
    
    // Simple wrapper for safe pointer access
    template<typename T>
    static T* SafePtr(uintptr_t address) {
        if (!address || IsBadReadPtr((void*)address, sizeof(T))) return nullptr;
        return (T*)address;
    }
};
