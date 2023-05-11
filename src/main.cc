//
// Created by small-sheep on 11/10/22.
//
#include "five_in_a_row_game/main.h"

#include <memory>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/application.h"

void cursor_pos_callback(GLFWwindow * window, double xpos, double ypos) {
  Application::Get(window)->CursorPosCallback(xpos, ypos);
}

void key_callback(GLFWwindow * window, int key, int scancode, int action,
                  int mods) {
  Application::Get(window)->KeyCallback(key, scancode, action, mods);
}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {
  Application::Get(window)->ScrollCallback(xoffset, yoffset);
}

int main() {
  Application::Initialize();
  auto application = std::make_unique<Application>(800, 600, "application");
  application->Run();
  application.reset();
  Application::Terminate();
  return 0;
}
