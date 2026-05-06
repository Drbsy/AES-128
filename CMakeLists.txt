cmake_minimum_required(VERSION 3.16)

project(AES)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "scr/*.cpp")

add_executable(AES_Tool ${SOURCES})

target_include_directories(AES_Tool PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

set_target_properties(AES_Tool PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")