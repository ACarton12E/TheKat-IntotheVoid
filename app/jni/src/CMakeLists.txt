cmake_minimum_required(VERSION 3.6)

project(MY_APP)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GAME_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../src")

add_library(main SHARED 
    ${GAME_ROOT}/main.cpp
    ${GAME_ROOT}/assets/download/assets.cpp
    ${GAME_ROOT}/code/Collectoon/collectoon.cpp
    ${GAME_ROOT}/code/Platform/platform.cpp
    ${GAME_ROOT}/code/Player/player.cpp
)

target_include_directories(main PRIVATE 
    "/home/thekat/c++/TheKat:IntotheVoid++/app/jni/SDL2/SDL_ttf"
    "/home/thekat/c++/TheKat:IntotheVoid++/app/jni/SDL2/SDL_mixer/include"
    "/home/thekat/c++/TheKat:IntotheVoid++/app/jni/SDL2/SDL_image/include"
    "/home/thekat/c++/TheKat:IntotheVoid++/app/jni/SDL2/SDL/include"
)

target_link_libraries(main 
    SDL2 
    SDL2_image 
    SDL2_ttf 
    SDL2_mixer 
    log 
    android
)
