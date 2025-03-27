cmake_minimum_required(VERSION 3.16)
project(firstSdlWindow)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendor/SDL3 EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(firstSdlWindow main.cpp
        classes/Vec2D.cpp
        classes/Vec2D.h
        classes/MovingPoint.cpp
        classes/MovingPoint.h
        classes/GlobalState.cpp
        classes/GlobalState.h
)

# Link to the actual SDL3 library.
target_link_libraries(firstSdlWindow PRIVATE SDL3::SDL3)