//
// Created by small-sheep on 11/11/22.
//

#include "program.h"
#include <iostream>
#include "five_in_a_row_game.h"
#include "player.h"
#include "human_player.h"
#include "ai_player.h"
#include "easy_ai_player.h"
#include "ai_player_factory.h"
#include "easy_ai_player_factory.h"
#include "human_player_factory.h"

Program::Program() {
}

void Program::Run() {
  SetProgramIsOn(true);
  while (ProgramIsOn()) {
    ParseCommand();
  }
}

void Program::ParseCommand() {
  static std::string command;
  std::cout << "Please input some commands:\n";
  std::cin >> command;
  if (command == "exit") {
    SetProgramIsOn(false);
  } else if (command == "start_a_game") {
    FiveInARowGame five_in_a_row_game;
    HumanPlayerFactory human_player_factory;
    EasyAIPlayerFactory easy_ai_factory;
    std::unique_ptr<Player> human_player(human_player_factory.MakePlayer());
    std::unique_ptr<Player> ai_player(easy_ai_factory.MakePlayer());

    five_in_a_row_game.Start(human_player.get(), ai_player.get());
  }
}

bool Program::ProgramIsOn() const {
  return program_is_on_;
}

void Program::SetProgramIsOn(bool program_is_on) {
  program_is_on_ = program_is_on;
}