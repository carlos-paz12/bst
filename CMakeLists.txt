cmake_minimum_required(VERSION 4.0)
project(bst)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES src/*.cpp)
add_executable(bst ${SOURCES})

target_include_directories(bst PRIVATE ${PROJECT_SOURCE_DIR}/include)