#include "five_in_a_row_game/utility.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <map>

#include "GLFW/glfw3.h"

std::string GetFileContents(const char * filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file");
  }
  std::string contents((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
  return contents;
}
std::string KeyToString(const int key) {
  static std::map<int, std::string> key_to_string_map{
      {GLFW_KEY_A, "A"},        {GLFW_KEY_D, "D"},
      {GLFW_KEY_G, "G"},        {GLFW_KEY_S, "S"},
      {GLFW_KEY_W, "W"},        {GLFW_KEY_LEFT_CONTROL, "Control"},
      {GLFW_KEY_SPACE, "Space"}};
  if (key_to_string_map.contains(key)) {
    return key_to_string_map.at(key);
  } else {
    // TODO: Implement the keys.
    return "unimplemented key";
  }
}
