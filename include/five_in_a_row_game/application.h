//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_APPLICATION_H
#define FIVE_IN_A_ROW_GAME_APPLICATION_H

#include <cstddef>
#include <exception>
#include <map>
#include <memory>
#include <vector>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/camera.h"
#include "five_in_a_row_game/five_in_a_row_game.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/shader_program.h"
#include "five_in_a_row_game/state.h"
#include "texture2d.h"
#include "five_in_a_row_game/window.h"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"

class Application {
 public:
  static void Initialize();
  static void Terminate();

 public:
  Application();
  Application(const char * window_title, const int window_width,
              const int window_height);
  Application(const Application &) = delete;
  Application(Application &&) = delete;
  Application & operator=(const Application &) = delete;
  Application & operator=(Application &&) = delete;
  ~Application();

  void Run();
  void CursorPosCallback(double x_pos, double y_pos);
  void KeyCallback(int key, int scancode, int action, int mods);
  void ScrollCallback(double x_offset, double y_offset);

  const Window & window() const { return window_; }

 private:
  void Update(const float delta_time);
  void Render() const;
  static void CheckErrors();

 private:
  // Window must be initialized first. So it is placed here the first.
  Window window_;
  bool keys_[512]{false};  // TODO: to be added to `Window` class
  Camera camera_;
  ShaderProgram shader_;
  ShaderProgram simple_shader_;
  double previous_frame_time_ = 0, current_frame_time_ = 0;
  std::size_t frame_per_second_ = 0;
  std::vector<FiveInARowGame *> history_games_;
  FiveInARowGame * game_ = nullptr;
  std::vector<std::shared_ptr<Player>> players_;
};

class ApplicationUninitialized : public std::exception {};

class GladUninitialized : public ApplicationUninitialized {};

class GlfwUninitialized : public ApplicationUninitialized {};

class GlfwWindowNotCreated : public ApplicationUninitialized {};

#endif  // FIVE_IN_A_ROW_GAME_APPLICATION_H
