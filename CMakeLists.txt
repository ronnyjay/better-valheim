cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER "g++")
set(PROJECT_NAME "better-valheim")
project(${PROJECT_NAME})

add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

# Include source files 
file(GLOB SOURCES
  "src/*.cpp"
  "src/engine/*.cpp"
  "src/game/*.cpp"
)

# Find required libraries 
find_package(glfw3 3.3 REQUIRED)
find_package(glm)

add_library(glad include/glad/gl.h src/gl.c)
target_include_directories(glad PUBLIC include/)

# Add executable and set compile options
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wpedantic -g)

# Link libraries
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glm)
