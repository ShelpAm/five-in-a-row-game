#include "five_in_a_row_game/window.h"

#include <string>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/application.h"
#include "five_in_a_row_game/callbacks.h"
#include "five_in_a_row_game/logger.h"
#include "five_in_a_row_game/timer.h"
#include "five_in_a_row_game/utility.h"
#include "glad/gl.h"
#include "stb/stb_image.h"

void Window::Initialize() {
  Logger::instance().Info("Initializing Window");
  Logger::instance().Info("Initializing GLFW");
  if (const auto result = glfwInit(); result == GLFW_FALSE) {
    Logger::instance().Error("Failed to initialize GLFW");
    throw GlfwUninitialized();
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  // FIXME: We should enable Debug mode. But the following codes are wrong.
#ifdef DEBUG
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif  // DEBUG
}

const Window * Window::GetByGLFWwindow(GLFWwindow * window) {
  // std::cout << "INFO::Window::Get invoked." << std::endl;
  if (window_map_.contains(window)) {
    return window_map_.at(window);
  }
  return nullptr;
}

Window::Window() : Window(nullptr, "untitled window", 800, 600) {}

Window::Window(Application * parent, const char * title, const int width,
               const int height)
    : parent_(parent), title_(title), width_(width), height_(height) {
  Timer timer("Window creation");
  if (num_of_objects() == 0) {
    Initialize();
  }
  Logger::instance().Info("Creating window: width=" + std::to_string(width) +
                          ", height=" + std::to_string(height));
  window_ = glfwCreateWindow(width_, height_, title_.c_str(), NULL, NULL);
  if (!window_) {
    glfwTerminate();
    throw GlfwWindowNotCreated();
  }
  Window * previous = MakeContextCurrent();
  glfwSwapInterval(1);
  glfwSetCursorPosCallback(window_, &cursor_pos_callback);
  glfwSetMouseButtonCallback(window_, &mouse_button_callback);
  glfwSetKeyCallback(window_, &key_callback);
  glfwSetScrollCallback(window_, &scroll_callback);
  // `x_pos` and `y_pos` doesn't work properly with `GLFW_CURSOR_DISABLED` (only
  // in VMWARE). So here we use `GLFW_CURSOR_NORMAL` to avoid that problem.
  // glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  if (glfwRawMouseMotionSupported()) {
    glfwSetInputMode(window_, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  }

  UpdateGLSettings();

  glDebugMessageCallback(&glDebugOutput, NULL);
  glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR,
                        GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  stbi_set_flip_vertically_on_load(true);

  RegisterForCallbacks();
  if (previous) {
    previous->MakeContextCurrent();
  }
  ++num_of_objects();
}

Window::~Window() {
  UnregisterForCallbacks();
  glfwDestroyWindow(window_);
  if (--num_of_objects() == 0) {
    glfwTerminate();
  }
}

void Window::RegisterForCallbacks() const { window_map_[window_] = this; }

void Window::UnregisterForCallbacks() const {
  if (window_map_.contains(window_)) {
    window_map_.erase(window_map_.find(window_));
  }
}

void Window::CursorPosCallback(double x_pos, double y_pos) const {
  if (parent_) {
    parent_->CursorPosCallback(x_pos, y_pos);
  }
}

void Window::KeyCallback(int key, int scancode, int action, int mods) const {
  if (parent_) {
    parent_->KeyCallback(key, scancode, action, mods);
  }
}

void Window::MouseButtonCallback(int button, int action, int mods) const {
  if (parent_) {
    parent_->MouseButtonCallback(button, action, mods);
  }
}

void Window::ScrollCallback(double x_offset, double yoffset) const {
  if (parent_) {
    parent_->ScrollCallback(x_offset, yoffset);
  }
}

void Window::Clear() {
  if (clear_color_changed_) {
    glClearColor(clear_color_.x, clear_color_.y, clear_color_.z,
                 clear_color_.w);
    clear_color_changed_ = false;
  }
  int being_used_buffer_bit = GL_COLOR_BUFFER_BIT;
  if (depth_test_enabled_) {
    being_used_buffer_bit |= GL_DEPTH_BUFFER_BIT;
  }
  glClear(being_used_buffer_bit);
}

void Window::SwapBuffers() const { glfwSwapBuffers(window_); }

void Window::PollEvents() { glfwPollEvents(); }

Window * Window::MakeContextCurrent() {
  static Window * last_used_window;
  Window * last_used_window_buffer = last_used_window;
  glfwMakeContextCurrent(window_);
  if (!gladLoadGL(glfwGetProcAddress)) {
    glfwTerminate();
    throw GladUninitialized();
  }
  last_used_window = this;
  return last_used_window_buffer;
}

void Window::UpdateGLSettings() const {
  glViewport(0, 0, width_, height_);
  UpdateDepthTestSetting();
  UpdateBlendSetting();
}

void Window::UpdateDepthTestSetting() const {
  if (depth_test_enabled_) {
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }
}

void Window::UpdateBlendSetting() const {
  if (blend_enabled_) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  } else {
    glDisable(GL_BLEND);
  }
}

std::map<const GLFWwindow *, const Window *> Window::window_map_{};
unsigned & Window::num_of_objects() {
  static unsigned num_of_objects = 0;
  return num_of_objects;
}
