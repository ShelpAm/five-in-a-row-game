//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_APPLICATION_H
#define FIVE_IN_A_ROW_GAME_APPLICATION_H

#include <cstddef>
#include <exception>
#include <list>
#include <map>
#include <memory>
#include <vector>

#include "GLFW/glfw3.h"
#include "five_in_a_row_game/camera.h"
#include "five_in_a_row_game/five_in_a_row_game.h"
#include "five_in_a_row_game/game_object.h"
#include "five_in_a_row_game/game_object_selector.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/shader_program.h"
#include "five_in_a_row_game/state.h"
#include "five_in_a_row_game/vector2d.h"
#include "five_in_a_row_game/window.h"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "texture2d.h"

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

  const Window & window() const { return window_; }

 private:
  void Update(const float delta_time);
  void Render() const;
  static void CheckErrors();
  friend class Window;
  void CursorPosCallback(double x_pos, double y_pos);
  void MouseButtonCallback(int button, int action, int mods);
  void KeyCallback(int key, int scancode, int action, int mods);
  void ScrollCallback(double x_offset, double y_offset);

  void DumpCursorPosition() const;

 private:
  static bool initialized_;
  // Window must be initialized first. So it is placed here the first.
  Window window_;
  Vector2D<float> cursor_pos_;
  Vector2D<float> delta_cursor_pos_;
  bool buttons_[64]{false};  // TODO: to be added to `Window` class
  bool keys_[256]{false};    // TODO: to be added to `Window` class
  Camera camera_;
  ShaderProgram shader_;
  ShaderProgram simple_shader_;
  double previous_frame_time_ = 0, current_frame_time_ = 0;
  std::size_t frame_per_second_ = 0;
  std::vector<FiveInARowGame *> history_games_;
  FiveInARowGame * game_ = nullptr;
  std::vector<std::shared_ptr<Player>> players_;
  std::list<GameObject *> game_objects_;
  GameObjectSelector game_object_selector_;
  Texture2D texture_{"awesome_face.png"};
};

class ApplicationUninitialized : public std::exception {};

class GladUninitialized : public ApplicationUninitialized {};

class GlfwUninitialized : public ApplicationUninitialized {};

class GlfwWindowNotCreated : public ApplicationUninitialized {};

#endif  // FIVE_IN_A_ROW_GAME_APPLICATION_H
