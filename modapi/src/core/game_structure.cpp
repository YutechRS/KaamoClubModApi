#include "core/game_structure.h"

namespace kaamo {

MemoryResult<std::string> GameStructure::read_string_field(const OffsetChain& offsets) const noexcept {
    auto& mem = MemoryAccessor::instance();
    auto addr_result = mem.resolve_pointer_chain(base_address_, offsets);
    
    if (!addr_result) {
        return std::unexpected(addr_result.error());
    }
    
    return mem.read_string(addr_result.value());
}

MemoryResult<std::string> GameStructure::read_wide_string_field(const OffsetChain& offsets) const noexcept {
    auto& mem = MemoryAccessor::instance();
    auto addr_result = mem.resolve_pointer_chain(base_address_, offsets);
    
    if (!addr_result) {
        return std::unexpected(addr_result.error());
    }
    
    return mem.read_wide_string(addr_result.value());
}

bool GameStructure::write_string_field(const OffsetChain& offsets, std::string_view value) const noexcept {
    auto& mem = MemoryAccessor::instance();
    auto addr_result = mem.resolve_pointer_chain(base_address_, offsets);
    
    if (!addr_result) {
        return false;
    }
    
    return mem.write_string(addr_result.value(), value);
}

bool GameStructure::write_wide_string_field(const OffsetChain& offsets, std::string_view value) const noexcept {
    auto& mem = MemoryAccessor::instance();
    auto addr_result = mem.resolve_pointer_chain(base_address_, offsets);
    
    if (!addr_result) {
        return false;
    }
    
    return mem.write_wide_string(addr_result.value(), value);
}

}
