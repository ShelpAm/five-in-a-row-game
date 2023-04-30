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
#include "five_in_a_row_game/state.h"

class Application {
 public:
  Application();
  ~Application();

  void MainLoop();

 private:
  void ProcessInput();

  void Update();

  void Render() const;

  void ParseCommand();

  std::size_t frame_per_second_{0};
  std::size_t last_frame_{0}, current_frame_{0};
  State state_;
  std::vector<FiveInARowGame> history_games_;
  FiveInARowGame game_{};
  std::vector<Player *> players_{};
};

#endif  // FIVE_IN_A_ROW_GAME_APPLICATION_H_
