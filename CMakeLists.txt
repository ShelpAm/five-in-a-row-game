cmake_minimum_required(VERSION 3.18)
project(five-in-a-row-game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_CXX_COMPILER "clang++")
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Weverything")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat -Wno-c++98-compat-pedantic")
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-exit-time-destructors")
  #set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-padded")
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-conversion")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
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

