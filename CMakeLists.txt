cmake_minimum_required(VERSION 3.5)

project(test-ogl)

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory("thirdparty/sdl")
add_subdirectory("thirdparty/glad")
add_subdirectory("thirdparty/stb_image")
add_subdirectory("thirdparty/glm")
add_subdirectory("thirdparty/assimp")

set(SOURCES 
    "src/main.cpp"
    "src/window.cpp"
    "src/camera.cpp"
    "src/opengl/gl_buffer.cpp"
    "src/opengl/gl_program.cpp"
    "src/opengl/gl_shader.cpp"
    "src/opengl/gl_vertex_array.cpp"
    "src/opengl/layout_element.cpp"
    "src/opengl/vertex_layout.cpp"
    "src/opengl/gl_texture.cpp"
    "src/opengl/gl_debug.cpp"
)

set(INCLUDES
    "thirdparty/sdl/include"
    "thirdparty/glad/include"
    "thirdparty/stb_image"
    "thirdparty/glm"
    "thirdparty/assimp/include"
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3 glad stb_image glm assimp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${INCLUDES})

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-assets.cmake)

add_dependencies(${CMAKE_PROJECT_NAME} copy_assets)
