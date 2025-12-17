#pragma once
#include <memory>
#include "Lua/LuaManager.h"

class ModEngine {
public:
    static ModEngine& Get() {
        static ModEngine instance;
        return instance;
    }

    void Initialize();
    void Run();

    LuaManager& GetLua() { return *m_LuaManager; }

private:
    ModEngine() = default;
    std::unique_ptr<LuaManager> m_LuaManager;
};
