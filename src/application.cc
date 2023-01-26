//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/application.h"

#include <iostream>

#include "five_in_a_row_game/easy_ai_player_factory.h"
#include "five_in_a_row_game/five_in_a_row_game.h"
#include "five_in_a_row_game/human_player_factory.h"
#include "five_in_a_row_game/player.h"

Application::Application() {}

void Application::MainLoop() {
  while (ApplicationIsOn()) {
    last_frame_ = current_frame_;
    current_frame_ = static_cast<int>(clock());
    SetFramePerSecond(current_frame_ - last_frame_);

    if (game_.Started()) {
      game_.Tick();
      continue;
    }
    if (game_.Over()) {
      std::cout << "Game over!\n";
    }
    ParseCommand();
  }
}

void Application::ParseCommand() {
  static std::string command;
  std::cout << "Please input some commands:\n";
  std::cin >> command;
  if (command == "exit") {
    SetApplicationIsOn(false);
  } else if (command == "start-a-local-game" || command == "game") {
    HumanPlayerFactory human_player_factory;
    EasyAIPlayerFactory easy_ai_player_factory;
    // TODO(small_sheep_ 1178550325@qq.com): The memory has not been
    //  freed(deleted).
    Player *human_player = human_player_factory.MakePlayer(),
           *ai_player = easy_ai_player_factory.MakePlayer();

    game_.Start(human_player, ai_player);
  }
}
