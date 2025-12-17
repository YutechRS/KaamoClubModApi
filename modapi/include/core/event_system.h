#pragma once

#include <string>
#include <string_view>
#include <functional>
#include <vector>
#include <unordered_map>
#include <memory>
#include <any>
#include <span>

namespace kaamo {

class Event {
public:
    explicit Event(std::string_view name) : name_(name) {}
    virtual ~Event() = default;
    
    [[nodiscard]] std::string_view get_name() const noexcept { return name_; }
    
    template<typename T>
    void add_parameter(T&& value) {
        parameters_.emplace_back(std::forward<T>(value));
    }
    
    template<typename T>
    [[nodiscard]] const T* get_parameter(std::size_t index) const {
        if (index >= parameters_.size()) {
            return nullptr;
        }
        return std::any_cast<T>(&parameters_[index]);
    }
    
    [[nodiscard]] std::size_t parameter_count() const noexcept { return parameters_.size(); }
    
private:
    std::string name_;
    std::vector<std::any> parameters_;
};

using EventCallback = std::function<void(const Event&)>;

enum class EventPriority : std::uint8_t {
    Lowest = 0,
    Low = 64,
    Normal = 128,
    High = 192,
    Highest = 255
};

struct EventListener {
    EventCallback callback;
    EventPriority priority;
    
    bool operator<(const EventListener& other) const noexcept {
        return static_cast<std::uint8_t>(priority) > static_cast<std::uint8_t>(other.priority);
    }
};

class EventSystem {
public:
    static EventSystem& instance();
    
    void register_listener(std::string_view event_name, EventCallback callback, EventPriority priority = EventPriority::Normal);
    void unregister_listeners(std::string_view event_name);
    void clear_all();
    
    void trigger(std::string_view event_name);
    
    template<typename... Args>
    void trigger(std::string_view event_name, Args&&... args);
    
private:
    EventSystem() = default;
    std::unordered_map<std::string, std::vector<EventListener>> listeners_;
};

template<typename... Args>
void EventSystem::trigger(std::string_view event_name, Args&&... args) {
    Event event(event_name);
    (event.add_parameter(std::forward<Args>(args)), ...);
    
    auto it = listeners_.find(std::string(event_name));
    if (it == listeners_.end()) {
        return;
    }
    
    for (const auto& listener : it->second) {
        try {
            listener.callback(event);
        } catch (const std::exception& e) {
            // Log error but continue processing other listeners
        }
    }
}

}
