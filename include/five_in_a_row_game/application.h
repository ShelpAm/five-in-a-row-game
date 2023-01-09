//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_PROGRAM_H
#define FIVE_IN_A_ROW_GAME_SRC_PROGRAM_H

#include "five_in_a_row_game/five_in_a_row_game.h"

class Application {
 public:
  Application();

  void MainLoop();
  void ParseCommand();

  bool ApplicationIsOn() const { return application_is_on_; }
  void SetApplicationIsOn(bool application_is_on) {
    application_is_on_ = application_is_on;
  }

 public:
  int FramePerSecond() const { return frame_per_second_; }
  void SetFramePerSecond(int frame_per_second) {
    frame_per_second_ = frame_per_second;
  }

 private:
  int frame_per_second_ = 0;
  int last_frame_time_ = 0, current_frame_time_ = 0;
  bool application_is_on_;

  FiveInARowGame game_;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_PROGRAM_H
