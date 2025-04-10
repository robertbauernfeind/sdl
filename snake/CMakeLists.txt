cmake_minimum_required(VERSION 3.30)
project(snake)

set(CMAKE_CXX_STANDARD 20)
# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendor/SDL3 EXCLUDE_FROM_ALL)

add_executable(snake main.cpp
        Head.cpp
        Head.h
        GlobalState.cpp
        GlobalState.h
        Tail.cpp
        Tail.h
        Direction.h)

# Link to the actual SDL3 library.
target_link_libraries(snake PRIVATE SDL3::SDL3)