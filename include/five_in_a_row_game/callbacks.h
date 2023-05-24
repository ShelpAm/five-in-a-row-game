#ifndef FIVE_IN_A_ROW_GAME_CALLBACKS_H_
#define FIVE_IN_A_ROW_GAME_CALLBACKS_H_

struct GLFWwindow;
void error_callback(int error, const char * msg);
void cursor_pos_callback(GLFWwindow *, double x_pos, double y_pos);
void key_callback(GLFWwindow *, int, int, int, int);
void scroll_callback(GLFWwindow *, double x_offset, double y_offset);

#endif  // !FIVE_IN_A_ROW_GAME_CALLBACKS_H_
