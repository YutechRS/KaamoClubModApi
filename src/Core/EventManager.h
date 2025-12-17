#pragma once
#include <string>
#include <map>
#include <vector>
#include <sol/sol.hpp>

class EventManager {
public:
    static EventManager& Get() {
        static EventManager instance;
        return instance;
    }

    void RegisterListener(const std::string& eventName, sol::protected_function callback) {
        m_Listeners[eventName].push_back(callback);
    }

    template<typename... Args>
    void TriggerEvent(const std::string& eventName, Args&&... args) {
        if (m_Listeners.find(eventName) != m_Listeners.end()) {
            for (auto& callback : m_Listeners[eventName]) {
                auto result = callback(std::forward<Args>(args)...);
                if (!result.valid()) {
                    sol::error err = result;
                    // Log error?
                }
            }
        }
    }

private:
    std::map<std::string, std::vector<sol::protected_function>> m_Listeners;
};
