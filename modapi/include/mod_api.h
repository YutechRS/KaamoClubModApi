#pragma once

#include "core/memory_accessor.h"
#include "core/lua_bridge.h"
#include "core/event_system.h"
#include "structures/player.h"
#include "structures/system.h"
#include "structures/station.h"
#include "structures/mission.h"
#include "structures/asset.h"
#include "game_event_monitor.h"
#include "mod_loader.h"
#include <memory>
#include <atomic>

namespace kaamo {

class ModApi {
public:
    static ModApi& instance();
    
    bool initialize();
    void shutdown();
    void run_event_loop();
    void stop_event_loop();
    
    [[nodiscard]] bool is_initialized() const noexcept { return initialized_; }
    
private:
    ModApi() = default;
    ~ModApi() = default;
    
    void initialize_memory();
    void initialize_lua();
    void initialize_structures();
    void load_mods();
    
    std::unique_ptr<structures::Player> player_;
    std::unique_ptr<structures::System> system_;
    std::unique_ptr<structures::Station> station_;
    std::unique_ptr<structures::Mission> mission_;
    std::unique_ptr<structures::Asset> asset_;
    std::unique_ptr<GameEventMonitor> event_monitor_;
    
    std::atomic<bool> initialized_{false};
    std::atomic<bool> running_{false};
    
    static constexpr Address kGameBaseOffset = 0x20AD6C;
    static constexpr Address kAssetBaseOffset = 0x20AE68;
};

}
