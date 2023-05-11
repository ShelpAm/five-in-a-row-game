add_executable(${PROJECT_NAME}
  ai_player.cc
  application.cc
  # application_state.cc
  board.cc
  board_coordinate.cc
  camera.cc
  easy_ai_player.cc
  easy_ai_player_factory.cc
  five_in_a_row_game.cc
  human_player.cc
  human_player_factory.cc
  main.cc
  player.cc
  shader.cc
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${FIVE_IN_A_ROW_GAME_INCLUDE_DIR}
  ${GLAD_INCLUDE_DIR}
  ${GLFW_INCLUDE_DIR}
  ${GLM_INCLUDE_DIR}
  ${STB_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  ${LIB_OPENGL}
  glad
  glfw
  stb
  # X11
  # pthread
  # Xrandr
  # Xi
  # dl
)

add_definitions(-DGLFW_INCLUDE_NONE)
