#pragma once

#include "core/game_structure.h"
#include "core/property_macros.h"
#include <sol/sol.hpp>

namespace kaamo::structures {

class Player : public GameStructure {
public:
    explicit Player(Address base);
    
    KAAMO_PROPERTY_INT(money, 0x174)
    KAAMO_PROPERTY_INT(max_cargo, 0x154, 0x0)
    KAAMO_PROPERTY_INT(cargo, 0x154, 0x10)
    KAAMO_PROPERTY_INT(ship_armor, 0x154, 0x20)
    KAAMO_PROPERTY_INT(max_ship_health, 0x154, 0x4)
    KAAMO_PROPERTY_INT(enemies_killed, 0x188)
    KAAMO_PROPERTY_INT(level, 0x190)
    KAAMO_PROPERTY_INT(visited_stations, 0x198)
    KAAMO_PROPERTY_INT(jump_gate_used_count, 0x19C)
    KAAMO_PROPERTY_INT(cargo_took_count, 0x1A8)
    
    [[nodiscard]] bool has_ship_armor() const noexcept {
        return get_ship_armor() != 0;
    }
    
    static void bind_to_lua(sol::state& lua);
};

}
