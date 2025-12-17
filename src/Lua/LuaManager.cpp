#include "LuaManager.h"
#include "Core/Logger.h"
#include "Game/GameClasses.h"
#include "Core/EventManager.h"

void LuaManager::Initialize() {
    m_State.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::os);
    BindAPI();
}

void LuaManager::LoadScripts(const std::string& directory) {
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directory(directory);
        return;
    }

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".lua") {
            LoadScriptFile(entry.path());
        }
        else if (entry.is_directory()) {
            std::filesystem::path initPath = entry.path() / "init.lua";
            if (std::filesystem::exists(initPath)) {
                // Add the mod folder to package.path so requires work
                std::string modDir = std::filesystem::absolute(entry.path()).string();
                std::replace(modDir.begin(), modDir.end(), '\\', '/'); // Lua prefers forward slashes
                
                std::string packagePath = m_State["package"]["path"];
                packagePath += ";" + modDir + "/?.lua;" + modDir + "/?/init.lua";
                m_State["package"]["path"] = packagePath;

                LoadScriptFile(initPath);
            }
        }
    }
}

void LuaManager::LoadScriptFile(const std::filesystem::path& path) {
    Logger::Log("Loading script: {}", path.string());
    auto result = m_State.script_file(path.string(), sol::script_pass_on_error);
    if (!result.valid()) {
        sol::error err = result;
        Logger::Log("Error loading script: {}", err.what());
    }
}

void LuaManager::BindAPI() {
    // Helper to bind singletons or global pointers
    m_State.set_function("GetPlayer", []() -> Player* {
        return Player::Get();
    });

    m_State.set_function("GetSystem", []() -> SystemInfo* {
        auto ctx = Player::GetContext();
        return ctx ? ctx->system_info : nullptr;
    });

    m_State.set_function("RegisterEvent", [](std::string name, sol::protected_function callback) {
        EventManager::Get().RegisterListener(name, callback);
    });

    // Register Player Type
    m_State.new_usertype<Player>("Player",
        sol::no_constructor,
        "money", sol::property(&Player::GetMoney, &Player::SetMoney),
        "ship", sol::property(&Player::ship_info)
    );

    // Register ShipInfo Type
    m_State.new_usertype<ShipInfo>("ShipInfo",
        sol::no_constructor,
        "max_cargo", &ShipInfo::max_cargo,
        "cargo", &ShipInfo::cargo,
        "armor", &ShipInfo::armor
    );
    
    // Register System Type
    m_State.new_usertype<SystemInfo>("System",
        sol::no_constructor,
        "id", &SystemInfo::system_id
    );

    Logger::Log("Lua API Bound");
}
