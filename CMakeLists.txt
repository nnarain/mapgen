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

add_subdirectory(src/external)

include_directories(
    include/
    ${IMGUI_INCLUDE_DIRS}
    ${FASTNOISE_INCLUDE_DIRS}
)

# Map Generator
add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
	imgui
	fastnoise
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

