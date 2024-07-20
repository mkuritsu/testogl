cmake_minimum_required(VERSION 3.5)

project(test-ogl)

set(SDL_SHARED OFF)

add_subdirectory("thirdparty/sdl")
add_subdirectory("thirdparty/glad")
add_subdirectory("thirdparty/stb_image")

set(SOURCES 
    "src/main.cpp"
    "src/window.cpp"
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3 glad stb_image)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "thirdparty/sdl/include" "thirdparty/glad/include" "thirdparty/stb_image")

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-assets.cmake)

add_dependencies(${CMAKE_PROJECT_NAME} copy_assets)