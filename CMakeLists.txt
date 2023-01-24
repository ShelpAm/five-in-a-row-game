cmake_minimum_required(VERSION 3.18)
project(five-in-a-row-game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_COMPILER "clang++")
if (${CMAKE_CXX_COMPILER} STREQUAL "clang++")
  set(CMAKE_CXX_FLAGS " \
  -Werror -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic \
  -Wno-exit-time-destructors -Wno-padded -Wno-sign-conversion")
elseif(${CMAKE_CXX_COMPILER} STREQUAL "vs2022")
  set(CMAKE_CXX_FLAGS "")
endif()
set(CMAKE_CXX_STANDARD "20")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(executable_name "${PROJECT_NAME}")

add_executable(${executable_name} "")
target_sources(${executable_name} PRIVATE src/ai_player.cc
  src/ai_player_factory.cc src/application.cc src/board.cc
  src/board_coordinate.cc src/easy_ai_player.cc src/easy_ai_player_factory.cc
  src/five_in_a_row_game.cc src/human_player.cc src/human_player_factory.cc
  src/main.cc src/player.cc src/player_factory.cc)
target_include_directories(${executable_name} PRIVATE include)

