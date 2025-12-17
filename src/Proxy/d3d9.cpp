#include <windows.h>
#include <string>
#include "Core/ModEngine.h"

typedef void* (WINAPI* Direct3DCreate9_t)(UINT SDKVersion);
Direct3DCreate9_t Original_Direct3DCreate9 = nullptr;

void InitializeProxy() {
    char path[MAX_PATH];
    GetSystemDirectoryA(path, MAX_PATH);
    std::string d3d9Path = std::string(path) + "\\d3d9.dll";
    
    HMODULE hD3D9 = LoadLibraryA(d3d9Path.c_str());
    if (hD3D9) {
        Original_Direct3DCreate9 = (Direct3DCreate9_t)GetProcAddress(hD3D9, "Direct3DCreate9");
    }
}

extern "C" void* WINAPI Direct3DCreate9(UINT SDKVersion) {
    if (!Original_Direct3DCreate9) {
        InitializeProxy();
    }
    
    // Initialize Mod API on first call
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        ModEngine::Get().Initialize();
    }

    if (Original_Direct3DCreate9) {
        return Original_Direct3DCreate9(SDKVersion);
    }
    return nullptr;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        InitializeProxy();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
