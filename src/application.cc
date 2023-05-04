//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/application.h"

#include <algorithm>
#include <cstddef>
#include <ctime>
#include <fstream>
#include <iostream>

#include "five_in_a_row_game/easy_ai_player.h"
#include "five_in_a_row_game/easy_ai_player_factory.h"
#include "five_in_a_row_game/human_player_factory.h"
#include "five_in_a_row_game/main.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/state.h"

Application::Application() {}

Application::~Application() {
  std::for_each(players_.begin(), players_.end(),
                [](const auto & player) { delete player; });
}

void Application::Run() {
  std::clock_t initial_clock = std::clock();
  while (!should_terminate_) {
    previous_frame_clock_ = current_frame_clock_;
    current_frame_clock_ = std::clock() - initial_clock;
    auto delta_clock = current_frame_clock_ - previous_frame_clock_;
    frame_per_second_ = static_cast<float>(CLOCKS_PER_SEC) / delta_clock;

    ProcessInput();
    Update(delta_clock);
    Render();
  }
}

void Application::ProcessInput() { ParseCommand(); }

void Application::Update(const std::size_t delta_tick) {
  if (game_) {
    game_->Update();
  }
}

void Application::Render() const {
  ClearScreen();
  if (game_) {
    game_->Render();
  }
}

void Application::ParseCommand() {
  std::string command;
  std::cout << "Input a command (selected from `quit`, "
               "`start-a-local-game`/`game`, `continue`/`c` and `debug`): ";
  while (true) {
    std::cin >> command;
    if (command == "quit" || command == "q") {
      should_terminate_ = true;
      break;
    } else if (command == "start-a-local-game" || command == "game") {
      HumanPlayerFactory human_player_factory;
      EasyAIPlayerFactory easy_ai_player_factory;
      Player * human_player = human_player_factory.MakePlayer();
      Player * ai_player1 = easy_ai_player_factory.MakePlayer();
      Player * ai_player2 = easy_ai_player_factory.MakePlayer();
      players_.push_back(human_player);
      players_.push_back(ai_player1);
      players_.push_back(ai_player2);
      human_player->set_name("test_user1");
      ai_player1->set_name("easy_ai_player1");
      ai_player2->set_name("easy_ai_player2");

      // TODO(small_sheep_ 1178550325@qq.com): This will make every first
      // element of history_games_ an empty game(nullptr).
      history_games_.push_back(game_);
      game_ = new FiveInARowGame(ai_player1, ai_player2);
      game_->Start();
      break;
    } else if (command == "c" || command == "continue") {
      // do nothing
      break;
    } else if (command == "debug" && game_) {
      std::cout << *game_;
    } else {
      std::cout << "There's no such a command like `" << command
                << "`.\nPlease input another: ";
    }
  }
}
