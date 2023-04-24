//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/application.h"

#include <iostream>

#include "five_in_a_row_game/easy_ai_player.h"
#include "five_in_a_row_game/easy_ai_player_factory.h"
#include "five_in_a_row_game/five_in_a_row_game.h"
#include "five_in_a_row_game/human_player_factory.h"
#include "five_in_a_row_game/player.h"

Application::Application() {}

void Application::MainLoop() {
  auto ProcessGameOver = [this]() -> void {
    std::cout << "Game over!\n";
    if (game_.winner()) {
      std::cout << "The winner is " << game_.winner()->name() << '\n';
    } else {
      std::cout << "The game drew! No one wins!\n";
    }
    // game_.CleanUp();
    game_ = FiveInARowGame();
    ParseCommand();
  };

  SetApplicationIsOn(true);
  while (ApplicationIsOn()) {
    last_frame_ = current_frame_;
    current_frame_ = static_cast<int>(clock());
    frame_per_second_ = current_frame_ - last_frame_;

    switch (game_.game_state()) {
      case GameState::kGameStateNotStarted:
        ParseCommand();
        break;
      case GameState::kGameStateStarted:
        game_.Tick();
        continue;
      case GameState::kGameStateOver:
        ProcessGameOver();
        break;
    }
  }
}

void Application::ParseCommand() {
  std::string command;
  std::cout << "Please input a command:\n";
  std::cin >> command;
  if (command == "quit") {
    this->SetApplicationIsOn(false);
  } else if (command == "start-a-local-game" || command == "game") {
    HumanPlayerFactory human_player_factory;
    EasyAIPlayerFactory easy_ai_player_factory;
    // TODO(small_sheep_ 1178550325@qq.com): The memory has not been
    //  freed(deleted).
    Player * human_player = human_player_factory.MakePlayer();
    Player * ai_player1 = easy_ai_player_factory.MakePlayer();
    Player * ai_player2 = easy_ai_player_factory.MakePlayer();
    human_player->set_name("small_sheep_");
    ai_player1->set_name("easy_ai_player1");
    ai_player2->set_name("easy_ai_player2");

    // game_.Start(human_player, ai_player);
    game_.Start(*ai_player1, *ai_player2);
  }
}
