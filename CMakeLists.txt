cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)
project(cvoxel VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDART 11)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/src/*.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} 
    "${CMAKE_SOURCE_DIR}/lib/cvector/src/cvector.c"
    "${CMAKE_SOURCE_DIR}/lib/stb_image/stb_image.c"
)

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -g -O3)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(
    "${CMAKE_SOURCE_DIR}/lib/cvector/include/"
    "${CMAKE_SOURCE_DIR}/lib/glfw/include/"
    "${CMAKE_SOURCE_DIR}/lib/cglm/include/"
    "${CMAKE_SOURCE_DIR}/lib/glad/include/"
    "${CMAKE_SOURCE_DIR}/lib/stb_image/"
)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw/)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/cglm/)

add_library(glad "${CMAKE_SOURCE_DIR}/lib/glad/src/gl.c")

target_link_libraries(${PROJECT_NAME} OpenGL::GL glad glfw cglm)