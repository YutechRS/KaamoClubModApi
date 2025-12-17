#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <chrono>

class Logger {
public:
    static void Init(const std::string& path) {
        log_file.open(path, std::ios::out | std::ios::trunc);
    }

    template<typename... Args>
    static void Log(std::format_string<Args...> fmt, Args&&... args) {
        std::string msg = std::format(fmt, std::forward<Args>(args)...);
        std::string timestamp = std::format("{:%H:%M:%S}", std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now()));
        
        std::string full_msg = std::format("[{}] [KaamoMod] {}\n", timestamp, msg);
        
        if (log_file.is_open()) {
            log_file << full_msg;
            log_file.flush();
        }
        std::cout << full_msg;
    }

private:
    static inline std::ofstream log_file;
};
