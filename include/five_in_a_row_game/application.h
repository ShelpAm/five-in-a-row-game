//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_APPLICATION_H_
#define FIVE_IN_A_ROW_GAME_APPLICATION_H_

#include <vector>

#include "five_in_a_row_game/five_in_a_row_game.h"
#include "five_in_a_row_game/player.h"

class Application {
 public:
  Application();

  void MainLoop();
  void ParseCommand();

  bool ApplicationIsOn() const { return application_is_on_; }
  void SetApplicationIsOn(bool is_on) { application_is_on_ = is_on; }
  int FramePerSecond() const { return frame_per_second_; }

 private:
  int frame_per_second_{0};
  int last_frame_ = 0, current_frame_{0};
  bool application_is_on_{false};

  std::vector<FiveInARowGame> game_histories_;
  FiveInARowGame game_{};
};

#endif  // FIVE_IN_A_ROW_GAME_APPLICATION_H_
