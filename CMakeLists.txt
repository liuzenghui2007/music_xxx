cmake_minimum_required(VERSION 3.29)
project(music)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 CONFIG REQUIRED)

add_executable(music main.cpp)

target_include_directories(music PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    /opt/homebrew/include/SDL2
)

target_link_libraries(music
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
