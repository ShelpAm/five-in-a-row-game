add_executable(${PROJECT_NAME}
  ai_player.cc
  application.cc
  board.cc board_coordinate.cc easy_ai_player.cc
  easy_ai_player_factory.cc five_in_a_row_game.cc
  human_player.cc human_player_factory.cc main.cc player.cc)
target_include_directories(${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/third_party/imgui
  ${PROJECT_SOURCE_DIR}/third_party/glfw/include
)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui glfw)
