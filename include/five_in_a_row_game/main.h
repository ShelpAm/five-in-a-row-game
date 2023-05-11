#ifndef APPLICATION_MAIN_H_
#define APPLICATION_MAIN_H_
#include <iostream>

#include "GLFW/glfw3.h"
inline void ClearScreen() { std::cout << "\033[2J\033[1;1H"; }
void cursor_pos_callback(GLFWwindow *, double xpos, double ypos);
void key_callback(GLFWwindow *, int, int, int, int);
void scroll_callback(GLFWwindow *, double xoffset, double yoffset);
#endif  // APPLICATION_MAIN_H_
