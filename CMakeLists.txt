cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER "g++")
project(better-valheim)

# Include source files 
file(GLOB SOURCES "src/*.cpp")

# Find required libraries 
find_package(glfw3 3.3 REQUIRED)

add_library(glad include/glad/gl.h src/gl.c)
target_include_directories(glad PUBLIC include/)

# Add executable and set compile options
add_executable(better-valheim ${SOURCES})
target_compile_options(better-valheim PRIVATE -Werror -Wall -Wpedantic)

# Link libraries
target_link_libraries(better-valheim glfw)
target_link_libraries(better-valheim glad)