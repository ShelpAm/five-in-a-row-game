cmake_minimum_required(VERSION 3.18)
project(five_in_a_row_game LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(include_dir include)

file(GLOB_RECURSE src_file CONFIGURE_DEPENDS src/*.cc include/*.h)
add_executable(${PROJECT_NAME} ${src_file})
target_include_directories(five_in_a_row_game PUBLIC ${include_dir})