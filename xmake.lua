add_rules("mode.debug", "mode.release")

set_arch("x86")


add_requires("sol2", {configs = {includes_lua = true}}) -- Use sol2 with Lua included

target("d3d9")
    set_kind("shared")
    add_files("src/Proxy/*.cpp")
    add_files("src/Proxy/d3d9.def")
    add_includedirs("src")
    set_languages("c++20")
    add_syslinks("user32")
    add_packages("sol2")
    
    -- Ensure it's named d3d9.dll
    set_filename("d3d9.dll")
    
    -- Link with the mod logic
    add_deps("KaamoModApi")
    
    after_build(function (target)
        -- Copy to build directory for easy access
        os.cp(target:targetfile(), "$(buildir)/dist/")
    end)

target("KaamoModApi")
    set_kind("static") -- Logic as a static lib linked into the proxy
    add_files("src/*.cpp")
    add_files("src/Core/*.cpp")
    add_files("src/Game/*.cpp")
    add_files("src/Lua/*.cpp")
    add_includedirs("src")
    
    add_includedirs("src")
    add_packages("sol2")
    
    set_languages("c++20")
    add_defines("NOMINMAX", "WIN32_LEAN_AND_MEAN")
