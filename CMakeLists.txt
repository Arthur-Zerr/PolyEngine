cmake_minimum_required(VERSION 3.24)
project(PolyEditor)

set(CMAKE_CXX_STANDARD 23)

set(INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/")

# Engine

file(GLOB_RECURSE ENGINE_SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/engine/*.cpp)

file(GLOB_RECURSE ENGINE_HEADER_FILES
        ${CMAKE_SOURCE_DIR}/engine/*.h)

# Editor

file(GLOB_RECURSE EDITOR_SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/editor/*.cpp)

file(GLOB_RECURSE EDITOR_HEADER_FILES
        ${CMAKE_SOURCE_DIR}/editor/*.h)

file(GLOB_RECURSE INCLUDE_SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/libs/*.cpp)

add_executable(PolyEditor main.cpp glad.c stb.cpp tinygltf.cpp ${EDITOR_SOURCE_FILES} ${EDITOR_HEADER_FILES} ${ENGINE_SOURCE_FILES} ${ENGINE_HEADER_FILES} ${INCLUDE_SOURCE_FILES} libs/tinyobj/tiny_obj_loader.h tinyobj.cpp editor/CustomImGuiStyle.h)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(PolyEditor glfw)


find_package(OpenGL REQUIRED)
target_link_libraries(PolyEditor OpenGL::GL)

target_include_directories(PolyEditor PUBLIC ${INCLUDE_DIR})

#Copy shaders
file(GLOB_RECURSE SHADER_FILES
        ${CMAKE_SOURCE_DIR}/shaders/*.glsl)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/shaders")
add_custom_command(TARGET PolyEditor PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SHADER_FILES} "${CMAKE_CURRENT_BINARY_DIR}/shaders")

#Copy textures
file(GLOB_RECURSE TEXTURE_FILES
        ${CMAKE_SOURCE_DIR}/assets/textures/*.jpg)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/textures")
add_custom_command(TARGET PolyEditor PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TEXTURE_FILES} "${CMAKE_CURRENT_BINARY_DIR}/textures")


#Copy Objects
file(GLOB_RECURSE OBJECT_FILES
        ${CMAKE_SOURCE_DIR}/assets/objects/*.obj)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/objects")
add_custom_command(TARGET PolyEditor PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${OBJECT_FILES} "${CMAKE_CURRENT_BINARY_DIR}/objects")

#Copy MTL
file(GLOB_RECURSE MTL_FILES
        ${CMAKE_SOURCE_DIR}/assets/objects/*.mtl)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/objects")
add_custom_command(TARGET PolyEditor PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MTL_FILES} "${CMAKE_CURRENT_BINARY_DIR}/objects")

#Copy Fonts
file(GLOB_RECURSE FONT_FILES
        ${CMAKE_SOURCE_DIR}/assets/fonts/*.ttf)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/fonts")
add_custom_command(TARGET PolyEditor PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FONT_FILES} "${CMAKE_CURRENT_BINARY_DIR}/fonts/")