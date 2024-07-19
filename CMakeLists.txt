cmake_minimum_required(VERSION 3.5)

project(test-ogl)

set(SDL_SHARED OFF)

add_subdirectory("thirdparty/sdl")
add_subdirectory("thirdparty/glad")

set(SOURCES 
    "src/main.cpp"
    "src/window.cpp"
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3 glad)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "thirdparty/sdl/include" "thirdparty/glad/include")