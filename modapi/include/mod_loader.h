#pragma once

#include "core/lua_bridge.h"
#include <filesystem>
#include <vector>
#include <string>

namespace kaamo {

class ModLoader {
public:
    static ModLoader& instance();
    
    void scan_and_load_mods(const std::filesystem::path& mods_directory);
    [[nodiscard]] std::size_t get_loaded_mod_count() const noexcept { return loaded_mods_.size(); }
    
private:
    ModLoader() = default;
    bool load_mod(const std::filesystem::path& mod_path);
    
    std::vector<std::string> loaded_mods_;
};

}
