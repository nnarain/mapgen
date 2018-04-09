#
# Map Generator Build
#
# @author Natesh Narain
#

cmake_minimum_required(VERSION 3.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(IMGUI_ROOT "src/external/imgui")

project(mapgen)

find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED COMPONENTS system window graphics)

# Add Imgui and ImGui SFML Backend sources
add_subdirectory(src/external/imgui-sfml)

include_directories(
    include/
    "${IMGUI_SFML_INCLUDE_DIRS}"
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${IMGUI_SOURCES}
    ${IMGUI_SFML_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${IMGUI_SFML_DEPENDENCIES}
    ${OPENGL_gl_LIBRARY}
)

###########################################################
### Installation                                        ###
###########################################################
install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

