#include "game_event_monitor.h"

namespace kaamo {

GameEventMonitor::GameEventMonitor(structures::Player& player, 
                                  structures::System& system, 
                                  structures::Mission& mission)
    : player_(player), system_(system), mission_(mission) {}

void GameEventMonitor::check_events() {
    EventSystem::instance().trigger("OnUpdate");
    
    check_game_state();
    check_system_changed();
    check_money_changed();
}

void GameEventMonitor::check_system_changed() {
    int current_system = system_.get_system_id();
    
    if (current_system != last_system_id_ && current_system > 0 && current_system < 1000) {
        EventSystem::instance().trigger("OnSystemChanged", current_system);
        last_system_id_ = current_system;
    }
}

void GameEventMonitor::check_money_changed() {
    int current_money = player_.get_money();
    
    if (current_money != last_money_) {
        EventSystem::instance().trigger("OnMoneyChanged", current_money);
        last_money_ = current_money;
    }
}

void GameEventMonitor::check_game_state() {
    int mission_id = mission_.get_mission_id();
    bool is_in_game = (mission_id > 0 && mission_id < 1000);
    
    if (is_in_game && !was_in_game_) {
        EventSystem::instance().trigger("IsInGame");
        was_in_game_ = true;
    } else if (!is_in_game && was_in_game_) {
        if (mission_id == 0) {
            EventSystem::instance().trigger("IsInMainMenu");
        }
        was_in_game_ = false;
    }
}

}
