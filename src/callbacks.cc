#include "five_in_a_row_game/callbacks.h"

#include <iostream>

#include "five_in_a_row_game/application.h"
#include "five_in_a_row_game/window.h"

void error_callback(int error, const char * msg) {
  std::string s;
  s = " ERROR::error_callback [GLFW " + std::to_string(error) + "] " + msg +
      '\n';
  std::cerr << s << std::endl;
}

void cursor_pos_callback(GLFWwindow * window, double x_pos, double y_pos) {
  Window::Get(window)->CursorPosCallback(x_pos, y_pos);
}

void key_callback(GLFWwindow * window, int key, int scancode, int action,
                  int mods) {
  Window::Get(window)->KeyCallback(key, scancode, action, mods);
}

void scroll_callback(GLFWwindow * window, double x_offset, double y_offset) {
  Window::Get(window)->ScrollCallback(x_offset, y_offset);
}
