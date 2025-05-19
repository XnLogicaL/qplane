cmake_minimum_required(VERSION 3.20)

project(qplane_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

# Engine static library
add_subdirectory(engine)

# Game executable
add_executable(qplane_game game/main.cpp)

target_link_libraries(qplane_game PRIVATE qplane_engine)

target_include_directories(qplane_game PRIVATE engine/include)
