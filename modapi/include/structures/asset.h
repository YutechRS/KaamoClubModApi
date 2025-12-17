#pragma once

#include "core/game_structure.h"
#include "core/property_macros.h"
#include <sol/sol.hpp>

namespace kaamo::structures {

class Asset : public GameStructure {
public:
    explicit Asset(Address base);
    
    [[nodiscard]] std::string get_asset_file_path(unsigned int offset) const noexcept {
        auto result = read_string_field({0x148, offset, 0xC, 0x0, 0x0});
        return result.value_or("");
    }
    
    void set_asset_file_path(unsigned int offset, const std::string& value) noexcept {
        write_string_field({0x148, offset, 0xC, 0x0, 0x0}, value);
    }
    
    static void bind_to_lua(sol::state& lua);
};

}
