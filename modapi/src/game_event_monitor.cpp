#include "game_event_monitor.h"

namespace kaamo {

namespace {
    constexpr int MIN_VALID_SYSTEM_ID = 0;
    constexpr int MAX_VALID_SYSTEM_ID = 1000;
    constexpr int MIN_VALID_MISSION_ID = 0;
    constexpr int MAX_VALID_MISSION_ID = 1000;
    constexpr int MAIN_MENU_MISSION_ID = 0;
}

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
    
    if (current_system != last_system_id_ && 
        current_system > MIN_VALID_SYSTEM_ID && 
        current_system < MAX_VALID_SYSTEM_ID) {
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
    bool is_in_game = (mission_id > MIN_VALID_MISSION_ID && mission_id < MAX_VALID_MISSION_ID);
    
    if (is_in_game && !was_in_game_) {
        EventSystem::instance().trigger("IsInGame");
        was_in_game_ = true;
    } else if (!is_in_game && was_in_game_) {
        if (mission_id == MAIN_MENU_MISSION_ID) {
            EventSystem::instance().trigger("IsInMainMenu");
        }
        was_in_game_ = false;
    }
}

}
