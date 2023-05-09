#ifndef APPLICATION_MAIN_H_
#define APPLICATION_MAIN_H_
#include <iostream>

#include "GLFW/glfw3.h"
inline void ClearScreen() { std::cout << "\033[2J\033[1;1H"; }
void cursor_pos_callback(GLFWwindow *, double pos_x, double pos_y);
void cursor_pos_callback(GLFWwindow *, unsigned);
#endif  // APPLICATION_MAIN_H_
