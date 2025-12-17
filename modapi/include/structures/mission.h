#pragma once

#include "core/game_structure.h"
#include "core/property_macros.h"
#include <sol/sol.hpp>

namespace kaamo::structures {

class Mission : public GameStructure {
public:
    explicit Mission(Address base);
    
    KAAMO_PROPERTY_INT(mission_id, 0x1B0)
    KAAMO_PROPERTY_INT(completed_side_missions, 0x18C)
    
    static void bind_to_lua(sol::state& lua);
};

}
