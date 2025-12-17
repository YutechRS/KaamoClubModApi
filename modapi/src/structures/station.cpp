#include "structures/station.h"

namespace kaamo::structures {

Station::Station(Address base) : GameStructure(base) {}

void Station::bind_to_lua(sol::state& lua) {
    lua.new_usertype<Station>("Station",
        sol::no_constructor,
        KAAMO_BIND_PROPERTY(Station, station_id, "id"),
        KAAMO_BIND_PROPERTY(Station, station_name, "name"),
        KAAMO_BIND_PROPERTY(Station, tech_level, "level")
    );
}

}
