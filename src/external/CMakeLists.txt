############################
### Imgui and Imgui SFML ###
############################
set(IMGUI_INCLUDE_DIRS_INTERNAL
    imgui/
    imgui-sfml/
)
set(IMGUI_INCLUDE_DIRS ${IMGUI_INCLUDE_DIRS_INTERNAL} PARENT_SCOPE)

set(IMGUI_PATH "${CMAKE_CURRENT_LIST_DIR}/imgui")
set(IMGUI_SFML_PATH "${CMAKE_CURRENT_LIST_DIR}/imgui-sfml")

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
set(FASTNOISE_INCLUDE_DIRS
    FastNoise/

    PARENT_SCOPE
)

add_library(fastnoise
    FastNoise/FastNoise.cpp
)

target_include_directories(fastnoise PRIVATE
    ${FASTNOISE_INCLUDE_DIRS}
)
