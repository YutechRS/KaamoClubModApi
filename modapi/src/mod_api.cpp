#include "mod_api.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace kaamo {

ModApi& ModApi::instance() {
    static ModApi instance;
    return instance;
}

bool ModApi::initialize() {
    if (initialized_.exchange(true)) {
        return true;
    }
    
    std::cout << "[KaamoModAPI] Initializing..." << std::endl;
    
    try {
        initialize_memory();
        initialize_structures();
        initialize_lua();
        load_mods();
        
        std::cout << "[KaamoModAPI] Initialization complete!" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[KaamoModAPI] Initialization failed: " << e.what() << std::endl;
        initialized_ = false;
        return false;
    }
}

void ModApi::shutdown() {
    if (!initialized_.exchange(false)) {
        return;
    }
    
    stop_event_loop();
    EventSystem::instance().clear_all();
    
    event_monitor_.reset();
    asset_.reset();
    mission_.reset();
    station_.reset();
    system_.reset();
    player_.reset();
    
    std::cout << "[KaamoModAPI] Shutdown complete" << std::endl;
}

void ModApi::initialize_memory() {
    MemoryAccessor::instance().initialize("GoF2.exe");
    
    auto base = MemoryAccessor::instance().get_module_base();
    if (base == 0) {
        throw std::runtime_error("Failed to get module base address");
    }
    
    std::cout << "[KaamoModAPI] Module base: 0x" << std::hex << base << std::dec << std::endl;
}

void ModApi::initialize_structures() {
    auto& mem = MemoryAccessor::instance();
    Address game_base = mem.get_module_base() + kGameBaseOffset;
    Address asset_base = mem.get_module_base() + kAssetBaseOffset;
    
    player_ = std::make_unique<structures::Player>(game_base);
    system_ = std::make_unique<structures::System>(game_base);
    station_ = std::make_unique<structures::Station>(game_base);
    mission_ = std::make_unique<structures::Mission>(game_base);
    asset_ = std::make_unique<structures::Asset>(asset_base);
    
    event_monitor_ = std::make_unique<GameEventMonitor>(*player_, *system_, *mission_);
    
    std::cout << "[KaamoModAPI] Game structures initialized" << std::endl;
}

void ModApi::initialize_lua() {
    auto& lua = LuaBridge::instance();
    lua.initialize();
    
    structures::Player::bind_to_lua(lua.get_state());
    structures::System::bind_to_lua(lua.get_state());
    structures::Station::bind_to_lua(lua.get_state());
    structures::Mission::bind_to_lua(lua.get_state());
    structures::Asset::bind_to_lua(lua.get_state());
    
    lua.get_state()["player"] = player_.get();
    lua.get_state()["system"] = system_.get();
    lua.get_state()["station"] = station_.get();
    lua.get_state()["mission"] = mission_.get();
    lua.get_state()["asset"] = asset_.get();
    
    std::cout << "[KaamoModAPI] Lua bindings registered" << std::endl;
}

void ModApi::load_mods() {
    ModLoader::instance().scan_and_load_mods("mods");
}

void ModApi::run_event_loop() {
    running_ = true;
    
    while (running_) {
        if (event_monitor_) {
            event_monitor_->check_events();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void ModApi::stop_event_loop() {
    running_ = false;
}

}
