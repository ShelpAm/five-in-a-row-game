cmake_minimum_required(VERSION 3.18)
project(five-in-a-row-game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_CXX_COMPILER "clang++")
if (${CMAKE_CXX_COMPILER} STREQUAL "clang++")
  set(CMAKE_CXX_FLAGS " \
  -Werror -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic \
  -Wno-exit-time-destructors -Wno-padded -Wno-sign-conversion \
  -Wno-unused-variable \
  ")
elseif(${CMAKE_CXX_COMPILER} STREQUAL "vs2022")
  set(CMAKE_CXX_FLAGS "")
endif()
set(CMAKE_CXX_STANDARD "20")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(main_executable "${PROJECT_NAME}")

add_executable(${main_executable} "")
target_sources(${main_executable} PRIVATE src/ai_player.cc
  src/application.cc src/board.cc
  src/board_coordinate.cc src/easy_ai_player.cc src/easy_ai_player_factory.cc
  src/five_in_a_row_game.cc
  src/human_player.cc src/human_player_factory.cc
  src/main.cc src/player.cc)
target_include_directories(${main_executable} PRIVATE include src)

