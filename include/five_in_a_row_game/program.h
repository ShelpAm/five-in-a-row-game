//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_PROGRAM_H
#define FIVE_IN_A_ROW_GAME_SRC_PROGRAM_H

#include "five_in_a_row_game.h"

class Program {
 public:
  Program();

  void Run();
  void ParseCommand();

  bool ProgramIsOn() const;
  void SetProgramIsOn(bool program_is_on);

 private:
  bool program_is_on_;
};


#endif //FIVE_IN_A_ROW_GAME_SRC_PROGRAM_H
