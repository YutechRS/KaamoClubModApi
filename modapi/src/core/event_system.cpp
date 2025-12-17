#include "core/event_system.h"
#include <algorithm>

namespace kaamo {

EventSystem& EventSystem::instance() {
    static EventSystem instance;
    return instance;
}

void EventSystem::register_listener(std::string_view event_name, EventCallback callback, EventPriority priority) {
    std::string key(event_name);
    auto& listeners = listeners_[key];
    
    listeners.push_back({std::move(callback), priority});
    
    std::sort(listeners.begin(), listeners.end());
}

void EventSystem::unregister_listeners(std::string_view event_name) {
    listeners_.erase(std::string(event_name));
}

void EventSystem::clear_all() {
    listeners_.clear();
}

void EventSystem::trigger(std::string_view event_name) {
    Event event(event_name);
    
    auto it = listeners_.find(std::string(event_name));
    if (it == listeners_.end()) {
        return;
    }
    
    for (const auto& listener : it->second) {
        try {
            listener.callback(event);
        } catch (const std::exception&) {
            // Continue processing
        }
    }
}

}
