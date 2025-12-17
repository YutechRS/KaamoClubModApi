#pragma once

#define KAAMO_PROPERTY_INT(name, ...) \
    [[nodiscard]] int get_##name() const noexcept { \
        auto result = read_field<int>({__VA_ARGS__}); \
        return result.value_or(0); \
    } \
    void set_##name(int value) noexcept { \
        write_field<int>({__VA_ARGS__}, value); \
    }

#define KAAMO_PROPERTY_FLOAT(name, ...) \
    [[nodiscard]] float get_##name() const noexcept { \
        auto result = read_field<float>({__VA_ARGS__}); \
        return result.value_or(0.0f); \
    } \
    void set_##name(float value) noexcept { \
        write_field<float>({__VA_ARGS__}, value); \
    }

#define KAAMO_PROPERTY_STRING(name, ...) \
    [[nodiscard]] std::string get_##name() const noexcept { \
        auto result = read_string_field({__VA_ARGS__}); \
        return result.value_or(""); \
    } \
    void set_##name(const std::string& value) noexcept { \
        write_string_field({__VA_ARGS__}, value); \
    }

#define KAAMO_PROPERTY_WSTRING(name, ...) \
    [[nodiscard]] std::string get_##name() const noexcept { \
        auto result = read_wide_string_field({__VA_ARGS__}); \
        return result.value_or(""); \
    } \
    void set_##name(const std::string& value) noexcept { \
        write_wide_string_field({__VA_ARGS__}, value); \
    }

#define KAAMO_PROPERTY_BOOL(name, ...) \
    [[nodiscard]] bool get_##name() const noexcept { \
        auto result = read_field<int>({__VA_ARGS__}); \
        return result.value_or(0) != 0; \
    } \
    void set_##name(bool value) noexcept { \
        write_field<int>({__VA_ARGS__}, value ? 1 : 0); \
    }

#define KAAMO_BIND_PROPERTY(usertype, cpp_name, lua_name) \
    lua_name, sol::property(&usertype::get_##cpp_name, &usertype::set_##cpp_name)

#define KAAMO_BIND_READONLY(usertype, cpp_name, lua_name) \
    lua_name, sol::property(&usertype::get_##cpp_name)

#define KAAMO_BIND_METHOD(usertype, cpp_name, lua_name) \
    lua_name, &usertype::cpp_name

