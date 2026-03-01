cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GoIndicator VERSION 1.2.1)

# 1. Try to find Geode via the modern way
find_package(Geode CONFIG QUIET)

# 2. If that fails (like in GitHub Actions), use the manual path
if(NOT Geode_FOUND)
    if(NOT DEFINED ENV{GEODE_SDK})
        message(FATAL_ERROR "Unable to find Geode SDK! Please set GEODE_SDK env var.")
    endif()
    add_subdirectory("$ENV{GEODE_SDK}" "${CMAKE_CURRENT_BINARY_DIR}/geode")
endif()

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    src/nodes/ColorPicker.cpp
    src/nodes/FloatSlider.cpp
    src/nodes/FontPicker.cpp
    src/nodes/IndicatorNode.cpp
    src/layers/LevelIndicatorsList.cpp
)

setup_geode_mod(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC src)
