#
# Map Generator Build
#
# @author Natesh Narain
#

cmake_minimum_required(VERSION 3.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")


project(mapgen)

find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED COMPONENTS system window graphics)

find_package(Boost REQUIRED)

add_subdirectory(src/external)

include_directories(
    include/
    ${IMGUI_INCLUDE_DIRS}
    ${FASTNOISE_INCLUDE_DIRS}
    ${YAML_CPP_INCLUDE_DIR}
    ${LUA_INCLUDE_DIRS}
    ${LUABIND_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

set(HEADERS
    include/windows/window.h
    include/windows/parameter_window.h
    include/windows/map_display_window.h

    include/parameters/parameter_loader.h
    include/parameters/noise_parameters.h
    include/parameters/parameter_value.h
    include/generator/map_generator.h
    include/generator/map_generator_manager.h
    include/generator/generator_buffer.h
    include/generator/generator_buffer_proxy.h
    include/generator/color.h
    include/generator/gradient.h

    include/script/script_engine.h
    include/script/generator_script.h
    include/script/layers.h

    include/imgui_extension/imgui_extension.h
    include/utils/utils.h

    include/factory/fastnoise_factory.h

    include/fastnoise_generator.h
    include/terrain_generator.h
    include/terrain2_generator.h
    include/mountain_generator.h
)

# Map Generator
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/parameters/parameter_loader.cpp
    src/imgui_extension/imgui_extension.cpp

    src/script/script_engine.cpp

    ${HEADERS}
)

target_link_libraries(${PROJECT_NAME}
	imgui
    fastnoise
    yaml-cpp
    lua
    luabind
    ${SFML_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
)

###########################################################
### Installation                                        ###
###########################################################
install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

