#pragma once

#include "core/types.h"
#include <windows.h>
#include <concepts>
#include <type_traits>

namespace kaamo {

template<typename T>
concept Trivial = std::is_trivially_copyable_v<T>;

template<typename T>
concept IntegralType = std::integral<T>;

class MemoryAccessor {
public:
    static MemoryAccessor& instance();

    void initialize(const char* module_name);
    
    [[nodiscard]] Address get_module_base() const noexcept { return module_base_; }
    
    template<Trivial T>
    [[nodiscard]] MemoryResult<T> read(Address address) const noexcept;
    
    template<Trivial T>
    [[nodiscard]] bool write(Address address, const T& value) const noexcept;
    
    [[nodiscard]] MemoryResult<std::string> read_string(Address address, std::size_t max_size = 256) const noexcept;
    [[nodiscard]] MemoryResult<std::string> read_wide_string(Address address, std::size_t max_size = 256) const noexcept;
    
    [[nodiscard]] bool write_string(Address address, std::string_view str) const noexcept;
    [[nodiscard]] bool write_wide_string(Address address, std::string_view str) const noexcept;
    
    [[nodiscard]] MemoryResult<Address> resolve_pointer_chain(Address base, const OffsetChain& offsets) const noexcept;
    
private:
    MemoryAccessor() = default;
    Address module_base_ = 0;
};

template<Trivial T>
MemoryResult<T> MemoryAccessor::read(Address address) const noexcept {
    if (address == 0) {
        return std::unexpected(MemoryError::NullPointer);
    }
    
    T buffer{};
    SIZE_T bytes_read = 0;
    
    if (!ReadProcessMemory(GetCurrentProcess(), 
                          reinterpret_cast<LPCVOID>(address), 
                          &buffer, 
                          sizeof(T), 
                          &bytes_read) || bytes_read != sizeof(T)) {
        return std::unexpected(MemoryError::ReadFailed);
    }
    
    return buffer;
}

template<Trivial T>
bool MemoryAccessor::write(Address address, const T& value) const noexcept {
    if (address == 0) {
        return false;
    }
    
    SIZE_T bytes_written = 0;
    return WriteProcessMemory(GetCurrentProcess(), 
                             reinterpret_cast<LPVOID>(address), 
                             &value, 
                             sizeof(T), 
                             &bytes_written) && bytes_written == sizeof(T);
}

}
