#pragma once

#include "structures/player.h"
#include "structures/system.h"
#include "structures/mission.h"
#include "core/event_system.h"
#include <memory>

namespace kaamo {

class GameEventMonitor {
public:
    GameEventMonitor(structures::Player& player, 
                    structures::System& system, 
                    structures::Mission& mission);
    
    void check_events();
    
private:
    void check_system_changed();
    void check_money_changed();
    void check_game_state();
    
    structures::Player& player_;
    structures::System& system_;
    structures::Mission& mission_;
    
    int last_system_id_ = -1;
    int last_money_ = -1;
    bool was_in_game_ = false;
};

}
