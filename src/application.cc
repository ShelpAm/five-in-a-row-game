//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/application.h"

#include <algorithm>
#include <iostream>

#include "five_in_a_row_game/easy_ai_player.h"
#include "five_in_a_row_game/easy_ai_player_factory.h"
#include "five_in_a_row_game/five_in_a_row_game.h"
#include "five_in_a_row_game/human_player_factory.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/state.h"

Application::Application() {}

Application::~Application() {
  std::for_each(players_.begin(), players_.end(),
                [](const auto & i) { delete i; });
}

void Application::MainLoop() {
  state_ = State::kStateStarted;
  while (state_ == State::kStateStarted) {
    ProcessInput();
    Update();
    Render();
  }
}

void Application::ProcessInput() { ParseCommand(); }

void Application::Update() {
  last_frame_ = current_frame_;
  current_frame_ = static_cast<int>(clock());
  frame_per_second_ = current_frame_ - last_frame_;

  game_.Update();
}

void Application::Render() const {
  switch (state_) {
    case State::kStateNotStarted:
      break;
    case State::kStateStarted:
      break;
    case State::kStateStoped:
      break;
    case State::kStateEnded:
      break;
  }
  game_.Render();
}
void Application::ParseCommand() {
  std::string command;
  std::cout << "Please input a command:\n";
  std::cin >> command;
  if (command == "quit") {
    state_ = State::kStateStoped;
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

    // TODO(small_sheep_ 1178550325@qq.com): This will make every first element
    // of history_games_ an empty game.
    history_games_.push_back(game_);
    game_ = FiveInARowGame();
    // game_.Start(*human_player, *ai_player1);
    game_.Start(*ai_player1, *ai_player2);
  } else if (command == "c" || command == "continue") {
    // do nothing
  }
}
