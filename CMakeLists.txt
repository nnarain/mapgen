#
# Map Generator Build
#
# @author Natesh Narain
#

cmake_minimum_required(VERSION 3.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Project Paths
set(EXTERNAL_DIR "${CMAKE_CURRENT_LIST_DIR}/src/external")


project(mapgen)

find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED COMPONENTS system window graphics)

# Add Imgui and ImGui SFML Backend sources
set(IMGUI_ROOT "${EXTERNAL_DIR}/imgui")
set(IMGUI_SFML_ROOT "${EXTERNAL_DIR}/imgui-sfml")
set(IMGUI_INCLUDE_DIR "${IMGUI_ROOT}")
set(IMGUI_SFML_INCLUDE_DIR "${IMGUI_SFML_ROOT}")
set(IMCONFIG "<imconfig-SFML.h>")


set(IMGUI_SOURCES
    ${IMGUI_ROOT}/imgui.cpp
    ${IMGUI_ROOT}/imgui_draw.cpp
    ${IMGUI_ROOT}/imgui_demo.cpp
)

set(IMGUI_SFML_SOURCES
    ${IMGUI_SFML_ROOT}/imgui-SFML.cpp
)

include_directories(
    include/
    ${SFML_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIR}
    ${IMGUI_SFML_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
)

# Imgui Project Dependencies
add_library(imgui_deps
    ${IMGUI_SOURCES}
    ${IMGUI_SFML_SOURCES}
)

set_target_properties(imgui_deps PROPERTIES
    COMPILE_FLAGS "-DIMGUI_USER_CONFIG=${IMCONFIG}"
)

# Map Generator
add_executable(${PROJECT_NAME}
    src/main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_FLAGS "-DIMGUI_USER_CONFIG=${IMCONFIG}"
)

target_link_libraries(${PROJECT_NAME}
	imgui_deps
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

