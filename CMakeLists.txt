cmake_minimum_required(VERSION 3.24)
project(PolyRPG)

set(CMAKE_CXX_STANDARD 23)

set(INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/")

file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h)

add_executable(PolyRPG src/main.cpp src/glad.c libs/stb/stb_image.h src/stb.cpp ${HEADER_FILES} ${SOURCE_FILES})

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(PolyRPG glfw)


find_package(OpenGL REQUIRED)
target_link_libraries(PolyRPG OpenGL::GL)

target_include_directories(PolyRPG PUBLIC ${INCLUDE_DIR})

#Copy shaders
file(GLOB_RECURSE SHADER_FILES
        ${CMAKE_SOURCE_DIR}/src/shaders/*.glsl)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/shaders")
add_custom_command(TARGET PolyRPG PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SHADER_FILES} "${CMAKE_CURRENT_BINARY_DIR}/shaders")

#Copy textures
file(GLOB_RECURSE TEXTURE_FILES
        ${CMAKE_SOURCE_DIR}/assets/textures/*.jpg)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/textures")
add_custom_command(TARGET PolyRPG PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TEXTURE_FILES} "${CMAKE_CURRENT_BINARY_DIR}/textures")


