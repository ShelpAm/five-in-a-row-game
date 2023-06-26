#ifndef FIVE_IN_IN_ROW_GAME_WINDOW_H_
#define FIVE_IN_IN_ROW_GAME_WINDOW_H_

#include <map>
#include <string>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/application_fwd.h"
#include "glm/ext/vector_float4.hpp"

class Window {
 public:
  /// @brief Initializes window system such as glfw library.
  static void Initialize();

  /// @brief Gets the window by a GLFW window pointer.
  /// @return nullptr if no application found.
  static const Window * GetByGLFWwindow(GLFWwindow * window);

 public:
  Window();
  Window(Application * parent_, const char * title, const int width,
         const int height);
  Window(Window &&) = delete;
  Window(const Window &) = delete;
  Window & operator=(Window &&) = delete;
  Window & operator=(const Window &) = delete;
  ~Window();
  void RegisterForCallbacks() const;
  void UnregisterForCallbacks() const;
  void CursorPosCallback(double x_pos, double y_pos) const;
  void MouseButtonCallback(int button, int action, int mods) const;
  void KeyCallback(int key, int scancode, int action, int mods) const;
  void ScrollCallback(double x_offset, double y_offset) const;
  void Clear();
  void SwapBuffers() const;
  static void PollEvents();
  /// @return The previously window context.
  Window * MakeContextCurrent();
  void UpdateGLSettings() const;
  void UpdateDepthTestSetting() const;
  void UpdateBlendSetting() const;

  GLFWwindow * window() const { return window_; }
  bool should_close() const { return glfwWindowShouldClose(window_); }
  void set_should_close(const bool value) {
    glfwSetWindowShouldClose(window_, value);
  }
  int width() const { return width_; }
  int height() const { return height_; }
  bool depth_test_enabled() const { return depth_test_enabled_; }
  void EnableDepthTest() { depth_test_enabled_ = true; }
  void DisableDepthTest() { depth_test_enabled_ = false; }
  void set_clear_color(const glm::vec4 & value) {
    clear_color_ = value;
    clear_color_changed_ = true;
  }

 private:
  static std::map<const GLFWwindow *, const Window *> window_map_;
  static unsigned & num_of_objects();

 private:
  Application * parent_;
  GLFWwindow * window_;
  std::string title_;
  int width_;
  int height_;
  bool depth_test_enabled_{true};
  bool blend_enabled_{true};
  glm::vec4 clear_color_{0.0f, 0.0f, 0.0f, 1.0f};
  bool clear_color_changed_ = true;
};

#endif  // FIVE_IN_IN_ROW_GAME_WINDOW_H_
