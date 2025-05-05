cmake_minimum_required(VERSION 3.30)
project(snake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Unterordner mit den SDL3\-Quellen
add_subdirectory(vendor/SDL3 EXCLUDE_FROM_ALL)
add_subdirectory(vendor/SDL_ttf EXCLUDE_FROM_ALL)
file(COPY ${CMAKE_SOURCE_DIR}/ressources DESTINATION ${CMAKE_BINARY_DIR})

add_executable(snake main.cpp
        Head.cpp
        Head.h
        GlobalState.cpp
        GlobalState.h
        Tail.cpp
        Tail.h
        Direction.h
        Apple.cpp
        Apple.h)

# Linke zu den SDL3 Bibliotheken
target_link_libraries(snake PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)