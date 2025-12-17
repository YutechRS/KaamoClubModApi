#include "ModEngine.h"
#include "Logger.h"
#include <thread>
#include <Windows.h>

void ModEngine::Initialize() {
    // Create console for debug
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    
    Logger::Init("KaamoModApi.log");
    Logger::Log("Initializing KaamoModApi...");

    m_LuaManager = std::make_unique<LuaManager>();
    m_LuaManager->Initialize();

    std::thread([this]() {
        Logger::Log("Loading scripts...");
        m_LuaManager->LoadScripts("mods/");
    }).detach();
}

void ModEngine::Run() {
    // Main loop hooks could go here
}
