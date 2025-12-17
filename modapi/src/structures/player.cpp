#include "structures/player.h"

namespace kaamo::structures {

Player::Player(Address base) : GameStructure(base) {}

void Player::bind_to_lua(sol::state& lua) {
    lua.new_usertype<Player>("Player",
        sol::no_constructor,
        KAAMO_BIND_PROPERTY(Player, money, "money"),
        KAAMO_BIND_PROPERTY(Player, cargo, "cargo"),
        KAAMO_BIND_PROPERTY(Player, max_cargo, "maxcargo"),
        KAAMO_BIND_PROPERTY(Player, ship_armor, "armor"),
        KAAMO_BIND_PROPERTY(Player, max_ship_health, "maxhealth"),
        KAAMO_BIND_PROPERTY(Player, enemies_killed, "enemieskilled"),
        KAAMO_BIND_PROPERTY(Player, level, "level"),
        KAAMO_BIND_PROPERTY(Player, visited_stations, "visitedstations"),
        KAAMO_BIND_PROPERTY(Player, jump_gate_used_count, "jumpgateusedcount"),
        KAAMO_BIND_PROPERTY(Player, cargo_took_count, "cargotookcount"),
        KAAMO_BIND_METHOD(Player, has_ship_armor, "HasShipArmor")
    );
}

}
