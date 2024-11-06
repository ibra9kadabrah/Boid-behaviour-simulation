cmake_minimum_required(VERSION 3.15)
project(my_game C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find packages
find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.c)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    raylib
    glfw
    m
)