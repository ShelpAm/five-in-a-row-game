#include "five_in_a_row_game/window.h"

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/application.h"
#include "five_in_a_row_game/callbacks.h"
#include "five_in_a_row_game/main.h"
#include "glad/glad.h"
#include "stb/stb_image.h"

const Window * Window::Get(GLFWwindow * window) {
  // std::cout << "INFO::Window::Get invoked." << std::endl;
  if (window_map_.contains(window)) {
    return window_map_.at(window);
  }
  return nullptr;
}

Window::Window() : Window(nullptr, "untitled window", 800, 600) {}

Window::Window(Application * parent, const char * title, const int width,
               const int height)
    : parent_(parent),
      window_(glfwCreateWindow(width, height, title, NULL, NULL)),
      title_(title),
      width_(width),
      height_(height) {
  if (!window_) {
    glfwTerminate();
    throw GlfwWindowNotCreated();
  }
  MakeContextCurrent();
  glfwSwapInterval(1);
  glfwSetCursorPosCallback(window_, &cursor_pos_callback);
  glfwSetKeyCallback(window_, &key_callback);
  glfwSetScrollCallback(window_, &scroll_callback);
  // `x_pos` and `y_pos` doesn't work properly with `GLFW_CURSOR_DISABLED` (only
  // in VMWARE). So here we use `GLFW_CURSOR_NORMAL` to avoid that problem.
  // glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  if (glfwRawMouseMotionSupported()) {
    glfwSetInputMode(window_, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  }

  glViewport(0, 0, width_, height_);
  UpdateGLStates();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_set_flip_vertically_on_load(true);

  RegisterForCallbacks();
}

Window::~Window() { UnregisterForCallbacks(); }

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

void Window::MakeContextCurrent() const {
  glfwMakeContextCurrent(window_);
  if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
    glfwTerminate();
    throw GladUninitialized();
  }
}

void Window::UpdateGLStates() const {
  UpdateDepthTestState();
  UpdateBlendState();
}

void Window::UpdateDepthTestState() const {
  if (depth_test_enabled_) {
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }
}

void Window::UpdateBlendState() const {
  if (blend_enabled_) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  } else {
    glDisable(GL_BLEND);
  }
}

std::map<const GLFWwindow *, const Window *> Window::window_map_{};
