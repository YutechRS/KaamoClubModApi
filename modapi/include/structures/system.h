#pragma once

#include "core/game_structure.h"
#include "core/property_macros.h"
#include <sol/sol.hpp>

namespace kaamo::structures {

class System : public GameStructure {
public:
    explicit System(Address base);
    
    KAAMO_PROPERTY_INT(system_id, 0x168, 0x14)
    KAAMO_PROPERTY_INT(risk_level, 0x168, 0x18)
    KAAMO_PROPERTY_INT(faction, 0x168, 0x1C)
    KAAMO_PROPERTY_INT(jump_gate_station_id, 0x168, 0x2C)
    KAAMO_PROPERTY_INT(map_coordinate_x, 0x168, 0x20)
    KAAMO_PROPERTY_INT(map_coordinate_y, 0x168, 0x24)
    KAAMO_PROPERTY_INT(map_coordinate_z, 0x168, 0x28)
    
    static void bind_to_lua(sol::state& lua);
};

}
