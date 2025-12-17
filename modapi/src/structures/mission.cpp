#include "structures/mission.h"

namespace kaamo::structures {

Mission::Mission(Address base) : GameStructure(base) {}

void Mission::bind_to_lua(sol::state& lua) {
    lua.new_usertype<Mission>("Mission",
        sol::no_constructor,
        KAAMO_BIND_PROPERTY(Mission, mission_id, "id"),
        KAAMO_BIND_PROPERTY(Mission, completed_side_missions, "completedsidemissions")
    );
}

}
