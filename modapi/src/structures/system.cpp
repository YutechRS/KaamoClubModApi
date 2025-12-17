#include "structures/system.h"

namespace kaamo::structures {

System::System(Address base) : GameStructure(base) {}

void System::bind_to_lua(sol::state& lua) {
    lua.new_usertype<System>("System",
        sol::no_constructor,
        KAAMO_BIND_PROPERTY(System, system_id, "id"),
        KAAMO_BIND_PROPERTY(System, risk_level, "risk"),
        KAAMO_BIND_PROPERTY(System, faction, "faction"),
        KAAMO_BIND_PROPERTY(System, jump_gate_station_id, "jumpgatestationid"),
        KAAMO_BIND_PROPERTY(System, map_coordinate_x, "mapcoordinate_x"),
        KAAMO_BIND_PROPERTY(System, map_coordinate_y, "mapcoordinate_y"),
        KAAMO_BIND_PROPERTY(System, map_coordinate_z, "mapcoordinate_z")
    );
}

}
