cmake_minimum_required(VERSION 3.18)
project(five_in_a_row_game LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-Werror -Weverything -Wno-c++98-compat \
  -Wno-c++98-compat-pedantic -Wno-exit-time-destructors -Wno-padded \
  -Wno-sign-conversion")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(include_dir include)

file(GLOB_RECURSE src_file CONFIGURE_DEPENDS src/*.cc include/five_in_a_row_game/*.h)
add_executable(${PROJECT_NAME} ${src_file})
target_include_directories(${PROJECT_NAME} PUBLIC ${include_dir})


