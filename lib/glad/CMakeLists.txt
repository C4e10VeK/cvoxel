cmake_minimum_required(VERSION 3.19)
project(glad LANGUAGES C)

file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/include/*.h")

add_library(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c" ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

