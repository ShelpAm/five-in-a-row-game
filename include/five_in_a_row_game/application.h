//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_APPLICATION_H
#define FIVE_IN_A_ROW_GAME_APPLICATION_H

#include <GLFW/glfw3.h>
#include <five_in_a_row_game/camera.h>
#include <five_in_a_row_game/five_in_a_row_game.h>
#include <five_in_a_row_game/game_object.h>
#include <five_in_a_row_game/game_object_selector.h>
#include <five_in_a_row_game/player.h>
#include <five_in_a_row_game/shader_program.h>
#include <five_in_a_row_game/state.h>
#include <five_in_a_row_game/texture2d.h>
#include <five_in_a_row_game/vector2d.h>
#include <five_in_a_row_game/window.h>

#include <array>
#include <cstddef>
#include <exception>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <utility>
#include <vector>

#include "glm/fwd.hpp"
#include "glm/glm.hpp"

class PlayerList {
 public:
  PlayerList() = default;
  PlayerList(const PlayerList & other) = default;
  PlayerList(PlayerList && other) = default;
  PlayerList & operator=(const PlayerList & other) = default;
  PlayerList & operator=(PlayerList && other) = default;
  ~PlayerList() = default;

  std::shared_ptr<Player> & GetById(const int id) { return players_[id]; }

  void Insert(std::shared_ptr<Player> && player) {
    players_.insert(std::make_pair(player->id(), player));
  }

  /// @brief Ensures the id won't appear in the list.
  void Remove(const int id) { players_.erase(id); }

  template <typename Function>
  void ForEach(const Function & function) {
    for (auto & player : players_) {
      function(player.second);
    }
  }

 private:
  std::map<int, std::shared_ptr<Player>> players_;
};

class Application {
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
  static void Initialize();
  static void Terminate();

  void Update(const float delta_time);
  void Render() const;
  static void CheckErrors();
  friend class Window;
  void CursorPosCallback(double x_pos, double y_pos);
  void MouseButtonCallback(int button, int action, int mods);
  void KeyCallback(int key, int scancode, int action, int mods);
  void ScrollCallback(double x_offset, double y_offset);

  void PrintCursorPosition() const;

 private:
  static inline bool initialized_ = false;
  static unsigned & num_of_objects();
  // Window must be initialized first. So it is placed here the first.
  Window window_;
  Vector2D<float> cursor_pos_{0, 0};
  Vector2D<float> delta_cursor_pos_{0, 0};
  std::array<bool, 64> buttons_{false};  // TODO: to be added to `Window` class
  std::array<bool, 512> keys_{false};    // TODO: to be added to `Window` class
  Camera camera_;
  ShaderProgram shader_{VertexShader(0, "shader/vertex.vert"),
                        FragmentShader(0, "shader/fragment.frag")};
  ShaderProgram simple_shader_{VertexShader(0, "shader/simple.vert"),
                               FragmentShader(0, "shader/simple.frag")};
  double previous_frame_time_ = 0, current_frame_time_ = 0;
  int frame_per_second_ = 0;
  std::list<FiveInARowGame> history_games_;
  PlayerList player_list_;
  std::list<GameObject *> game_objects_{};
  GameObjectSelector game_object_selector_;
  Texture2D texture_{"awesome_face.png"};
};

class ApplicationUninitialized {};

class GladUninitialized : public ApplicationUninitialized {};

class GlfwUninitialized : public ApplicationUninitialized {};

class GlfwWindowNotCreated : public ApplicationUninitialized {};

#endif  // FIVE_IN_A_ROW_GAME_APPLICATION_H
