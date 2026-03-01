cmake_minimum_required(VERSION 3.21)

# C++20 is the sweet spot for Geode v5 stability
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name and version should match your mod.json
project(GoIndicator VERSION 1.2.1)

# The modern way to link Geode - let the CLI find the SDK path
find_package(Geode CONFIG REQUIRED)

# List all your source files. 
# Ensure these paths are exactly where the files sit on your disk.
add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    src/nodes/ColorPicker.cpp
    src/nodes/FloatSlider.cpp
    src/nodes/FontPicker.cpp
    src/nodes/IndicatorNode.cpp
    src/layers/LevelIndicatorsList.cpp
)

# This function automates the packaging, 
# architecture settings, and linking to Geode/Cocos2d
setup_geode_mod(${PROJECT_NAME})

# If you have custom headers in these folders, 
# this line ensures the compiler finds them
target_include_directories(${PROJECT_NAME} PUBLIC src)
