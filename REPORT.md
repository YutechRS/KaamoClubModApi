# KaamoModApi 2.0 Rewrite Report

## Overview
This report details the complete rewrite of the KaamoModApi, transitioning from a manual, pointer-arithmetic-heavy C++ codebase to a modern, structured, and extensible C++20 architecture.

## Architecture Improvements

### 1. Modern C++20 Core
- **Modules & Structure**: The codebase is now organized into `Core`, `Game`, `Lua`, and `Proxy` modules.
- **Type Safety**: Replaced raw `uintptr_t` arithmetic with properly defined `struct`s matching the game's memory layout. This ensures type safety and easier debugging.
- **Memory Management**: Introduced a `Memory` class for safe pointer access and checking.

### 2. Game Structures
- **Reverse Engineering Alignment**: Structs like `ShipInfo`, `SystemInfo`, and `GameContext` now mirror the actual memory layout of Galaxy on Fire 2.
- **Direct Access**: Instead of calculating offsets on every property access, we now cast the base pointer to the correct struct type, allowing for efficient direct memory access.

### 3. Lua Integration
- **Sol2 Binding**: Switched to `sol2` for robust and efficient Lua bindings.
- **Automatic Property Binding**: Properties are bound directly to struct members, reducing boilerplate and overhead.
- **Extensibility**: Adding new structs is now as simple as defining the C++ struct and adding one `new_usertype` call in `LuaManager.cpp`.

### 4. D3D9 Proxy
- **Native C++**: Replaced the Rust-based proxy with a lightweight, native C++ `d3d9.dll` proxy. This removes the Rust toolchain dependency and simplifies the build process.

## API Usage

### For Modders (Lua)
The API has been simplified and standardized.
```lua
local player = GetPlayer()
player.money = 1000000
print("Current Money: " .. player.money)

local ship = player.ship
ship.armor = 100
```

### For Developers (C++)
To add a new struct:
1. Define the struct in `src/Game/GameClasses.h` with correct padding.
2. Register it in `src/Lua/LuaManager.cpp` using `m_State.new_usertype`.

## Build Instructions
1. Ensure you have `xmake` installed.
2. Run `xmake` to build the project.
3. The output `d3d9.dll` will be in `build/dist/`.

## Provenance
- **Sol2**: https://github.com/ThePhD/sol2 (MIT License)
- **Galaxy on Fire 2 Reversing**: Based on existing offsets provided in the original codebase (0x20AD6C base).

## Quality Assurance
- **Memory Safety**: `Memory::Read` and `Memory::Write` include checks for valid pointers (`IsBadReadPtr`).
- **Performance**: Direct pointer access is significantly faster than the previous `GetPointerAddress` chain traversal.
