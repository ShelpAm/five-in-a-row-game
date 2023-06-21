add_executable(${TEST_NAME} main.cc)

target_include_directories(${TEST_NAME} PRIVATE
  ${FIVE_IN_A_ROW_GAME_INCLUDE_DIR}
  # ${GLAD_INCLUDE_DIR}
  # ${GLFW_INCLUDE_DIR}
  # ${GLM_INCLUDE_DIR}
  # ${STB_INCLUDE_DIR}
)

target_link_libraries(${TEST_NAME} PRIVATE
  ${LIB_NAME}
  # ${LIB_OPENGL}
  # glad
  # glfw
  # stb
  # X11
  # pthread
  # Xrandr
  # Xi
  # dl
)

add_definitions(-DGLFW_INCLUDE_NONE)
