#include "core/lua_bridge.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace kaamo {

LuaBridge& LuaBridge::instance() {
    static LuaBridge instance;
    return instance;
}

void LuaBridge::initialize() {
    lua_.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, 
                       sol::lib::math, sol::lib::table);
    
    lua_["API_VERSION"] = "2.0";
    
    register_core_functions();
    register_event_system();
}

void LuaBridge::register_core_functions() {
    lua_.set_function("wait", [](int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    });
    
    lua_.set_function("log", [](const std::string& message) {
        std::cout << "[Lua] " << message << std::endl;
    });
}

void LuaBridge::register_event_system() {
    lua_.set_function("RegisterEvent", [](const std::string& event_name, sol::protected_function callback) {
        EventSystem::instance().register_listener(event_name, 
            [callback](const Event& event) mutable {
                auto result = callback();
                if (!result.valid()) {
                    sol::error err = result;
                    std::cerr << "[Lua Event Error] " << event.get_name() << ": " << err.what() << std::endl;
                }
            });
    });
    
    lua_.set_function("RegisterEventWithArgs", [](const std::string& event_name, sol::protected_function callback) {
        EventSystem::instance().register_listener(event_name, 
            [callback](const Event& event) mutable {
                sol::variadic_args va;
                std::vector<sol::object> args;
                
                for (std::size_t i = 0; i < event.parameter_count(); ++i) {
                    if (auto* int_val = event.get_parameter<int>(i)) {
                        args.push_back(sol::make_object(callback.lua_state(), *int_val));
                    } else if (auto* float_val = event.get_parameter<float>(i)) {
                        args.push_back(sol::make_object(callback.lua_state(), *float_val));
                    } else if (auto* str_val = event.get_parameter<std::string>(i)) {
                        args.push_back(sol::make_object(callback.lua_state(), *str_val));
                    }
                }
                
                auto result = callback(sol::as_args(args));
                if (!result.valid()) {
                    sol::error err = result;
                    std::cerr << "[Lua Event Error] " << event.get_name() << ": " << err.what() << std::endl;
                }
            });
    });
}

bool LuaBridge::execute_file(std::string_view filepath) {
    try {
        auto result = lua_.script_file(std::string(filepath));
        if (!result.valid()) {
            sol::error err = result;
            std::cerr << "[Lua Error] Failed to execute " << filepath << ": " << err.what() << std::endl;
            return false;
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[Lua Exception] " << filepath << ": " << e.what() << std::endl;
        return false;
    }
}

}
