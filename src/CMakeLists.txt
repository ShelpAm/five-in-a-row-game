add_library(${LIB_NAME} 
  ai_player.cc
  application.cc
  # application_state.cc
  board_coordinate.cc
  callbacks.cc
  camera.cc
  easy_ai_player.cc
  easy_ai_player_factory.cc
  five_in_a_row_game.cc
  fragment_shader.cc
  game_board.cc
  game_object_selector.cc
  human_player.cc
  human_player_factory.cc
  logger.cc
  player.cc
  shader_program.cc
  texture2d.cc
  time.cc
  utility.cc
  vertex_shader.cc
  window.cc
)

target_include_directories(${LIB_NAME} PRIVATE
  ${FIVE_IN_A_ROW_GAME_INCLUDE_DIR}
  ${GLAD_INCLUDE_DIR}
  ${GLFW_INCLUDE_DIR}
  ${GLM_INCLUDE_DIR}
  ${STB_INCLUDE_DIR}
)

target_link_libraries(${LIB_NAME} PRIVATE
  # ${LIB_OPENGL}
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

add_executable(${PROJECT_NAME}
  main.cc
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${FIVE_IN_A_ROW_GAME_INCLUDE_DIR}
  ${GLAD_INCLUDE_DIR}
  ${GLFW_INCLUDE_DIR}
  ${GLM_INCLUDE_DIR}
  ${STB_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} ${LIB_NAME})

