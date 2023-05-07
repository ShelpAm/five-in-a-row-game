//
// Created by small-sheep on 11/10/22.
//
#include <memory>

#include "five_in_a_row_game/application.h"

int main() {
  Application::Initialize();
  auto application = std::make_unique<Application>(800, 600, "application");
  application->Run();
  application.reset();
  Application::Terminate();
  return 0;
}
