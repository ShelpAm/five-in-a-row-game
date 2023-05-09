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
#include "five_in_a_row_game/five_in_a_row_game.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/shader.h"
#include "five_in_a_row_game/state.h"
#include "glm/glm.hpp"

class Application {
 public:
  static void Initialize();
  static void Terminate();

 public:
  Application(const std::size_t window_width, const std::size_t window_height,
              const char * window_title);
  ~Application();
  void Run();

 private:
  friend class ApplicationState;
  friend void cursor_pos_callback(GLFWwindow * window, double pos_x,
                                  double pos_y);
  void ProcessInput();
  void ProcessCursor();
  void ProcessKeyBoard();
  void Update(const std::size_t delta_tick);
  void Render() const;

 private:
  // TODO: to be refactored
  float yaw{-90}, pitch{0};
  glm::vec3 cameraPos{0.0f, 0.0f, 15.0f}, cameraFront{0.0f, 0.0f, -1.0f},
      cameraUp{0.0f, 1.0f, 0.0f};

  static std::map<const GLFWwindow *, Application *> window_application_map_;
  GLFWwindow * window_{};
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

void AttachApplication(const GLFWwindow * window, Application * application);

#endif  // FIVE_IN_A_ROW_GAME_APPLICATION_H_
