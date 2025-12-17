#pragma once

#include "core/types.h"
#include "core/memory_accessor.h"
#include <string_view>
#include <functional>
#include <type_traits>

namespace kaamo {

template<typename T>
concept GameStructureMember = requires {
    { T::offset } -> std::convertible_to<Offset>;
    { T::offsets } -> std::convertible_to<OffsetChain>;
};

struct FieldDescriptor {
    const char* name;
    OffsetChain offsets;
    
    enum class Type {
        Int32,
        Float,
        String,
        WideString,
        Bool
    } type;
    
    bool read_only = false;
};

class GameStructure {
public:
    explicit GameStructure(Address base_address) : base_address_(base_address) {}
    virtual ~GameStructure() = default;
    
    [[nodiscard]] Address get_base() const noexcept { return base_address_; }
    
    template<IntegralType T>
    [[nodiscard]] MemoryResult<T> read_field(const OffsetChain& offsets) const noexcept;
    
    template<IntegralType T>
    bool write_field(const OffsetChain& offsets, T value) const noexcept;
    
    [[nodiscard]] MemoryResult<std::string> read_string_field(const OffsetChain& offsets) const noexcept;
    [[nodiscard]] MemoryResult<std::string> read_wide_string_field(const OffsetChain& offsets) const noexcept;
    
    bool write_string_field(const OffsetChain& offsets, std::string_view value) const noexcept;
    bool write_wide_string_field(const OffsetChain& offsets, std::string_view value) const noexcept;
    
protected:
    Address base_address_;
};

template<IntegralType T>
MemoryResult<T> GameStructure::read_field(const OffsetChain& offsets) const noexcept {
    auto& mem = MemoryAccessor::instance();
    auto addr_result = mem.resolve_pointer_chain(base_address_, offsets);
    
    if (!addr_result) {
        return std::unexpected(addr_result.error());
    }
    
    return mem.read<T>(addr_result.value());
}

template<IntegralType T>
bool GameStructure::write_field(const OffsetChain& offsets, T value) const noexcept {
    auto& mem = MemoryAccessor::instance();
    auto addr_result = mem.resolve_pointer_chain(base_address_, offsets);
    
    if (!addr_result) {
        return false;
    }
    
    return mem.write<T>(addr_result.value(), value);
}

}
