#include "mod_loader.h"
#include <iostream>

namespace kaamo {

ModLoader& ModLoader::instance() {
    static ModLoader instance;
    return instance;
}

void ModLoader::scan_and_load_mods(const std::filesystem::path& mods_directory) {
    if (!std::filesystem::exists(mods_directory) || !std::filesystem::is_directory(mods_directory)) {
        std::cerr << "[ModLoader] Mods directory not found: " << mods_directory << std::endl;
        return;
    }
    
    std::cout << "[ModLoader] Scanning mods directory: " << mods_directory << std::endl;
    
    for (const auto& entry : std::filesystem::directory_iterator(mods_directory)) {
        if (entry.is_directory()) {
            load_mod(entry.path());
        }
    }
    
    std::cout << "[ModLoader] Loaded " << loaded_mods_.size() << " mod(s)" << std::endl;
}

bool ModLoader::load_mod(const std::filesystem::path& mod_path) {
    auto init_lua = mod_path / "init.lua";
    
    if (!std::filesystem::exists(init_lua)) {
        return false;
    }
    
    std::string mod_name = mod_path.filename().string();
    std::cout << "[ModLoader] Loading mod: " << mod_name << std::endl;
    
    if (LuaBridge::instance().execute_file(init_lua.string())) {
        loaded_mods_.push_back(mod_name);
        return true;
    }
    
    return false;
}

}
