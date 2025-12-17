#pragma once

#include "core/game_structure.h"
#include "core/property_macros.h"
#include <sol/sol.hpp>

namespace kaamo::structures {

class Station : public GameStructure {
public:
    explicit Station(Address base);
    
    KAAMO_PROPERTY_INT(station_id, 0x160, 0x8)
    KAAMO_PROPERTY_WSTRING(station_name, 0x160, 0x0, 0x0)
    KAAMO_PROPERTY_INT(tech_level, 0x160, 0x1C)
    
    static void bind_to_lua(sol::state& lua);
};

}
