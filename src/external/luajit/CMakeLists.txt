
set(LUAJIT_SOURCE_DIR_INTERNAL "${CMAKE_CURRENT_LIST_DIR}/LuaJIT")

# LuaJIT include directory
set(LUA_INCLUDE_DIRS "${LUAJIT_SOURCE_DIR_INTERNAL}/src" PARENT_SCOPE)

# Set the path to the LuaJIT source
set(LUAJIT_SOURCE_DIR "${LUAJIT_SOURCE_DIR_INTERNAL}")

# Call the script to configure LuaJIT
include(LuaJIT.cmake)
