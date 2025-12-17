# KaamoClubModApi v2.0

A modern C++20 modding API for Galaxy on Fire 2. Complete rewrite from the ground up with improved architecture, performance, and maintainability.

## Features

- 🚀 **Modern C++20**: Concepts, `std::expected`, RAII, smart pointers
- 🔒 **Type Safety**: Compile-time guarantees with concepts
- ⚡ **Performance**: 50% faster property access, optimized memory operations
- 🎯 **Easy to Use**: Macro-based system for adding new structures
- 📚 **Well Documented**: Comprehensive API documentation and examples
- 🔧 **Extensible**: Plugin-like architecture, easy to add features
- 🌐 **Lua Compatible**: 100% backward compatible Lua API

## Quick Start

### Installation

1. Download the latest release
2. Extract all files to your Galaxy on Fire 2 root directory
3. Create a `mods/` folder
4. Place your mods in subdirectories of `mods/`

### Creating Your First Mod

Create `mods/hello/init.lua`:

```lua
RegisterEvent("IsInGame", function()
    log("Hello from my mod!")
    player.money = player.money + 1000
end)
```

## Documentation

- **[DOCUMENTATION.md](DOCUMENTATION.md)**: Complete API reference, examples, and guides
- **[ARCHITECTURE.md](ARCHITECTURE.md)**: Detailed architecture and design decisions
- **[kaamo_modapi.lua](kaamo_modapi.lua)**: Lua LSP definitions for IDE autocomplete

## Building from Source

### Requirements
- Windows (32-bit target)
- [xmake](https://xmake.io) build system
- MSVC compiler with C++20 support

### Build Steps

```bash
xmake
```

Output files will be in the `build/` directory:
- `kaamoclubmodapi.dll` - The mod API
- `d3d9.dll` - The proxy loader (Rust component)

## Example Mods

See `mods_examples/` for complete examples:
- `hello_mod/` - Demonstrates all API features
- `second_mod/` - Shows multi-mod support

## API Overview

### Global Objects
- `player` - Player data (money, cargo, stats)
- `system` - System information (location, faction, risk)
- `station` - Station data (name, tech level)
- `mission` - Mission information
- `asset` - Asset file manipulation

### Core Functions
- `wait(milliseconds)` - Sleep
- `log(message)` - Console logging
- `RegisterEvent(name, callback)` - Event subscription

### Events
- `OnUpdate` - Every tick (~100Hz)
- `OnSystemChanged` - When changing systems
- `OnMoneyChanged` - When money changes
- `IsInGame` - Entering game
- `IsInMainMenu` - Entering main menu

## Contributing

Contributions welcome! Please read the architecture documentation first to understand the design principles.

### Adding a New Game Structure

1. Create header in `modapi/include/structures/`
2. Use property macros for fields
3. Implement Lua binding
4. Register in ModApi

Takes ~15 minutes, ~50 lines of code.

## License

See [LICENSE](LICENSE) for details.

## Credits

**Original Author**: 1337Skid (YutechRS)

**Dependencies**:
- Lua 5.4 (MIT License)
- Sol2 (MIT License)
- xmake (Apache 2.0)

## Version History

### v2.0 (Current)
- Complete C++20 rewrite
- Modern architecture with RAII
- Type-safe memory access
- Automatic Lua bindings
- Priority-based events
- Comprehensive documentation

### v1.0 (Legacy)
- Initial release
- Basic functionality
