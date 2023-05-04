//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_APPLICATION_H_
#define FIVE_IN_A_ROW_GAME_APPLICATION_H_

#include <cstddef>
#include <vector>

#include "five_in_a_row_game/five_in_a_row_game.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/state.h"

class Application {
 public:
  Application();
  ~Application();
  void Run();

 private:
  friend class ApplicationState;
  void ProcessInput();
  void Update(const std::size_t delta_tick);
  void Render() const;
  void ParseCommand();

 private:
  bool should_terminate_{false};
  std::size_t previous_frame_clock_{0}, current_frame_clock_{0};
  std::size_t frame_per_second_{0};
  std::vector<FiveInARowGame *> history_games_{};
  FiveInARowGame * game_{nullptr};
  std::vector<Player *> players_{};
};

#endif  // FIVE_IN_A_ROW_GAME_APPLICATION_H_
