//
// Created by small-sheep on 11/10/22.
//
#include "five_in_a_row_game/main.h"

#include <math.h>

#include <exception>
#include <fstream>
#include <iostream>
#include <memory>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/application.h"

std::string GetFileContents(const char * filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file");
  }
  std::string contents((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
  return contents;
}

int main() {
  try {
    Application application("application", 800, 660);
    application.Run();
    return 0;
  } catch (const std::exception & e) {
    std::cout << e.what();
    throw;
  } catch (...) {
    std::cout << "Error::main exception caught." << std::endl;
    throw;
  }
}
