cmake_minimum_required(VERSION 3.13)
project(f-simple)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.c" "generated/*.c" "generated/*.cc")
add_executable(ansi_c ${SOURCE_FILES})
target_link_libraries(ansi_c "stdc++")