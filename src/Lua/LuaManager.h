#pragma once
#include <sol/sol.hpp>
#include <string>
#include <filesystem>
#include <vector>

class LuaManager {
public:
    void Initialize();
    void LoadScripts(const std::string& directory);
    sol::state& GetState() { return m_State; }

private:
    void BindAPI();
    void LoadScriptFile(const std::filesystem::path& path);
    sol::state m_State;
};
