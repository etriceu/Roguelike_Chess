cmake_minimum_required(VERSION 3.3)
project(Roguelike_Chess)

add_compile_options(-std=c++11 -O3 -Wall -g)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB DATA res/*)
add_executable(Roguelike_Chess ${SOURCES} ${DATA})
file(COPY ${DATA} DESTINATION .)


find_package(SFML 2.5 COMPONENTS window graphics system REQUIRED)

target_link_libraries(Roguelike_Chess pthread sfml-window sfml-graphics sfml-system sfml-audio)

install(TARGETS Roguelike_Chess DESTINATION Roguelike_Chess)
