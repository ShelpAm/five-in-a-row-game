#ifndef APPLICATION_MAIN_H_
#define APPLICATION_MAIN_H_

#include <map>
#include <string>

#include "GLFW/glfw3.h"

std::string GetFileContents(const char * filename);
std::string KeyToString(const int key);

#endif  // APPLICATION_MAIN_H_
