#include "mod_api.h"
#include <windows.h>
#include <cstdio>
#include <iostream>

namespace {
    DWORD WINAPI main_thread(LPVOID param) {
        FILE* console_file = nullptr;
        freopen_s(&console_file, "CONOUT$", "w", stdout);
        freopen_s(&console_file, "CONOUT$", "w", stderr);
        
        std::cout << "=====================================" << std::endl;
        std::cout << "  KaamoClubModAPI v2.0" << std::endl;
        std::cout << "  Modern C++20 Rewrite" << std::endl;
        std::cout << "=====================================" << std::endl;
        
        auto& api = kaamo::ModApi::instance();
        
        if (!api.initialize()) {
            std::cerr << "Failed to initialize ModAPI" << std::endl;
            if (console_file) {
                fclose(console_file);
            }
            FreeLibraryAndExitThread(static_cast<HMODULE>(param), 1);
            return 1;
        }
        
        api.run_event_loop();
        
        api.shutdown();
        
        if (console_file) {
            fclose(console_file);
        }
        
        FreeLibraryAndExitThread(static_cast<HMODULE>(param), 0);
        return 0;
    }
}

extern "C" BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH: {
            DisableThreadLibraryCalls(module);
            
            HANDLE thread = CreateThread(nullptr, 0, main_thread, module, 0, nullptr);
            if (thread) {
                CloseHandle(thread);
            }
            break;
        }
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    
    return TRUE;
}
