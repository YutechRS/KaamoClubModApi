#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <expected>
#include <span>

namespace kaamo {

using Address = std::uintptr_t;
using Offset = std::uint32_t;
using OffsetChain = std::vector<Offset>;

enum class MemoryError {
    NullPointer,
    InvalidAddress,
    ReadFailed,
    WriteFailed,
    InvalidSize
};

template<typename T>
using MemoryResult = std::expected<T, MemoryError>;

enum class GameStructureType : std::uint8_t {
    Player,
    System,
    Station,
    Mission,
    Asset
};

struct GameStructureMetadata {
    const char* name;
    GameStructureType type;
    Address base_offset;
};

}
