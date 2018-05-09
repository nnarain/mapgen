############################
### Imgui and Imgui SFML ###
############################
set(IMGUI_PATH "${CMAKE_CURRENT_LIST_DIR}/imgui")
set(IMGUI_SFML_PATH "${CMAKE_CURRENT_LIST_DIR}/imgui-sfml")

set(IMGUI_INCLUDE_DIRS_INTERNAL
    ${IMGUI_PATH}
    ${IMGUI_SFML_PATH}
)
set(IMGUI_INCLUDE_DIRS ${IMGUI_INCLUDE_DIRS_INTERNAL} PARENT_SCOPE)

set(IMCONFIG "<imconfig-SFML.h>")

find_package(SFML REQUIRED COMPONENTS system graphics)

add_library(imgui
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_SFML_PATH}/imgui-SFML.cpp
    ${SFML_INCLUDE_DIRS}
)

target_include_directories(imgui PUBLIC
    ${IMGUI_INCLUDE_DIRS_INTERNAL}
    ${SFML_INCLUDE_DIR}
)

set_target_properties(imgui PROPERTIES
    COMPILE_FLAGS "-DIMGUI_USER_CONFIG=${IMCONFIG}"
)

target_link_libraries(imgui
    ${SFML_LIBARIES}
)

#################
### FastNoise ###
#################
set(FASTNOISE_INCLUDE_DIRS_INTERNAL
    ${CMAKE_CURRENT_LIST_DIR}/FastNoise/
)
set(FASTNOISE_INCLUDE_DIRS ${FASTNOISE_INCLUDE_DIRS_INTERNAL} PARENT_SCOPE)

add_library(fastnoise
    FastNoise/FastNoise.cpp
)

target_include_directories(fastnoise PRIVATE
    ${FASTNOISE_INCLUDE_DIRS}
)

################
### YAML CPP ###
################

set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "Enable testing")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "Enable parse tools")
set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "Enable contrib")
add_subdirectory(yaml-cpp)

set(YAML_CPP_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/yaml-cpp/include" PARENT_SCOPE)

##########################
### LuaJIT and Luabind ###
##########################

add_subdirectory(luajit)
add_subdirectory(luabind)

set(LUA_INCLUDE_DIRS ${LUA_INCLUDE_DIRS} PARENT_SCOPE)
set(LUABIND_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/luabind" PARENT_SCOPE)
