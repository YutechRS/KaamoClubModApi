#pragma once

#include "core/types.h"
#include "core/game_structure.h"
#include "core/event_system.h"
#include <sol/sol.hpp>
#include <string_view>
#include <type_traits>

namespace kaamo {

class LuaBridge {
public:
    static LuaBridge& instance();
    
    void initialize();
    [[nodiscard]] sol::state& get_state() noexcept { return lua_; }
    
    bool execute_file(std::string_view filepath);
    
    template<typename T>
    void register_game_structure(std::string_view lua_name, T& structure);
    
    void register_core_functions();
    void register_event_system();
    
private:
    LuaBridge() = default;
    sol::state lua_;
};

template<typename T>
void LuaBridge::register_game_structure(std::string_view lua_name, T& structure) {
    static_assert(std::is_base_of_v<GameStructure, T>, "T must derive from GameStructure");
    
    lua_[std::string(lua_name)] = &structure;
}

}
