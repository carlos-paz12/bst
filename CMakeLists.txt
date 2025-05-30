# cmake_minimum_required(VERSION 3.10)
cmake_minimum_required(VERSION 4.0)
project(bst)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB SOURCES src/*.cpp)
add_executable(bst src/main.cpp)

target_include_directories(bst PRIVATE ${PROJECT_SOURCE_DIR}/include)
