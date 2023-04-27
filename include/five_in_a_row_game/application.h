//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_APPLICATION_H_
#define FIVE_IN_A_ROW_GAME_APPLICATION_H_

#include <cstddef>
#include <type_traits>
#include <vector>

#include "five_in_a_row_game/five_in_a_row_game.h"
#include "five_in_a_row_game/player.h"

enum class ApplicationState : std::size_t {
  kApplicationStateStarted,
  kApplicationStateStoped
};

class Application {
 public:
  Application();

  void MainLoop();

  void ParseCommand();

  void ProcessGameOver();

  ApplicationState state() const { return state_; }
  void set_state(ApplicationState state) { state_ = state; }
  int frame_per_second() const { return frame_per_second_; }

 private:
  void Update();

  int frame_per_second_{0};
  int last_frame_ = 0, current_frame_{0};
  ApplicationState state_{ApplicationState::kApplicationStateStoped};

  std::vector<FiveInARowGame> history_games_;
  FiveInARowGame game_{};
};

#endif  // FIVE_IN_A_ROW_GAME_APPLICATION_H_
