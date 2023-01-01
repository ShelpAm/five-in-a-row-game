//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_PROGRAM_H
#define FIVE_IN_A_ROW_GAME_SRC_PROGRAM_H

#include "five_in_a_row_game.h"

class Application {
 public:
  Application();

  void MainLoop();
  void ParseCommand();

  bool ApplicationIsOn() const;
  void SetApplicationIsOn(bool application_is_on);

 private:
  bool application_is_on_;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_PROGRAM_H
