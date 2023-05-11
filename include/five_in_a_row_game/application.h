//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_APPLICATION_H_
#define FIVE_IN_A_ROW_GAME_APPLICATION_H_

#include <cstddef>
#include <map>
#include <memory>
#include <vector>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/camera.h"
#include "five_in_a_row_game/five_in_a_row_game.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/shader.h"
#include "five_in_a_row_game/state.h"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"

class Application {
 public:
  static void Initialize();
  static void Terminate();
  static Application * Get(GLFWwindow * window) {
    return window_application_map_.at(window);
  }

 public:
  Application(const std::size_t window_width, const std::size_t window_height,
              const char * window_title);
  ~Application();
  void AttachThis();
  void DetachThis() const;
  void Run();
  void CursorPosCallback(double xpos, double ypos);
  void KeyCallback(int key, int scancode, int action, int mods);
  void ScrollCallback(double xoffset, double yoffset);

 private:
  friend class ApplicationState;
  void Update(const float delta_time);
  void Render() const;

 private:
  // TODO: to be refactored
  static std::map<const GLFWwindow *, Application *> window_application_map_;
  GLFWwindow * window_{};
  bool keys_[512]{false};
  Camera camera_;
  const std::size_t window_width_, window_height_;
  std::unique_ptr<Shader> shader_;
  double previous_frame_time_{0}, current_frame_time_{0};
  std::size_t frame_per_second_{0};
  std::vector<FiveInARowGame *> history_games_{};
  FiveInARowGame * game_{nullptr};
  std::vector<std::shared_ptr<Player>> players_{};
};

class ApplicationUninitialized {};
class GladUninitialized : public ApplicationUninitialized {};
class GlfwUninitialized : public ApplicationUninitialized {};
class GlfwWindowNotCreated : public ApplicationUninitialized {};

#endif  // FIVE_IN_A_ROW_GAME_APPLICATION_H_
