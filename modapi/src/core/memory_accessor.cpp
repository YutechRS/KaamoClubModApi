#include "core/memory_accessor.h"
#include <vector>

namespace kaamo {

MemoryAccessor& MemoryAccessor::instance() {
    static MemoryAccessor instance;
    return instance;
}

void MemoryAccessor::initialize(const char* module_name) {
    module_base_ = reinterpret_cast<Address>(GetModuleHandleA(module_name));
}

MemoryResult<std::string> MemoryAccessor::read_string(Address address, std::size_t max_size) const noexcept {
    if (address == 0) {
        return std::unexpected(MemoryError::NullPointer);
    }
    
    std::vector<char> buffer(max_size);
    SIZE_T bytes_read = 0;
    
    if (!ReadProcessMemory(GetCurrentProcess(), 
                          reinterpret_cast<LPCVOID>(address), 
                          buffer.data(), 
                          buffer.size(), 
                          &bytes_read)) {
        return std::unexpected(MemoryError::ReadFailed);
    }
    
    buffer[max_size - 1] = '\0';
    return std::string(buffer.data());
}

MemoryResult<std::string> MemoryAccessor::read_wide_string(Address address, std::size_t max_size) const noexcept {
    if (address == 0) {
        return std::unexpected(MemoryError::NullPointer);
    }
    
    std::vector<wchar_t> buffer(max_size);
    SIZE_T bytes_read = 0;
    
    if (!ReadProcessMemory(GetCurrentProcess(), 
                          reinterpret_cast<LPCVOID>(address), 
                          buffer.data(), 
                          buffer.size() * sizeof(wchar_t), 
                          &bytes_read)) {
        return std::unexpected(MemoryError::ReadFailed);
    }
    
    buffer[max_size - 1] = L'\0';
    std::wstring wstr(buffer.data());
    
    if (wstr.empty()) {
        return std::string();
    }
    
    int required_size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), 
                                           static_cast<int>(wstr.size()), 
                                           nullptr, 0, nullptr, nullptr);
    if (required_size == 0) {
        return std::unexpected(MemoryError::ReadFailed);
    }
    
    std::string result(required_size, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), 
                       static_cast<int>(wstr.size()), 
                       result.data(), required_size, nullptr, nullptr);
    
    return result;
}

bool MemoryAccessor::write_string(Address address, std::string_view str) const noexcept {
    if (address == 0) {
        return false;
    }
    
    SIZE_T bytes_written = 0;
    return WriteProcessMemory(GetCurrentProcess(), 
                             reinterpret_cast<LPVOID>(address), 
                             str.data(), 
                             str.size() + 1, 
                             &bytes_written);
}

bool MemoryAccessor::write_wide_string(Address address, std::string_view str) const noexcept {
    if (address == 0) {
        return false;
    }
    
    int required_size = MultiByteToWideChar(CP_UTF8, 0, str.data(), 
                                           static_cast<int>(str.size()), 
                                           nullptr, 0);
    if (required_size == 0) {
        return false;
    }
    
    std::vector<wchar_t> buffer(required_size + 1);
    MultiByteToWideChar(CP_UTF8, 0, str.data(), 
                       static_cast<int>(str.size()), 
                       buffer.data(), required_size);
    buffer[required_size] = L'\0';
    
    SIZE_T bytes_written = 0;
    return WriteProcessMemory(GetCurrentProcess(), 
                             reinterpret_cast<LPVOID>(address), 
                             buffer.data(), 
                             buffer.size() * sizeof(wchar_t), 
                             &bytes_written);
}

MemoryResult<Address> MemoryAccessor::resolve_pointer_chain(Address base, const OffsetChain& offsets) const noexcept {
    if (base == 0) {
        return std::unexpected(MemoryError::NullPointer);
    }
    
    Address current = base;
    
    for (Offset offset : offsets) {
        auto result = read<Address>(current);
        if (!result) {
            return std::unexpected(result.error());
        }
        
        current = result.value();
        if (current == 0) {
            return std::unexpected(MemoryError::NullPointer);
        }
        
        current += offset;
    }
    
    return current;
}

}
