//
// Created by small-sheep on 11/11/22.
//

#include <five_in_a_row_game/application.h>
#include <five_in_a_row_game/easy_ai_player_factory.h>
#include <five_in_a_row_game/five_in_a_row_game.h>
#include <five_in_a_row_game/human_player_factory.h>
#include <five_in_a_row_game/player.h>

#include <iostream>

Application::Application() {}

void Application::MainLoop() {
  while (ApplicationIsOn()) {
    ParseCommand();
  }
}

void Application::ParseCommand() {
  static std::string command;
  std::cout << "Please input some commands:\n";
  std::cin >> command;
  if (command == "exit") {
    SetApplicationIsOn(false);
  } else if (command == "start_a_game") {
    FiveInARowGame five_in_a_row_game;
    HumanPlayerFactory human_player_factory;
    EasyAIPlayerFactory easy_ai_factory;
    std::unique_ptr<Player> human_player(human_player_factory.MakePlayer());
    std::unique_ptr<Player> ai_player(easy_ai_factory.MakePlayer());

    five_in_a_row_game.Start(human_player.get(), ai_player.get());
  }
}

bool Application::ApplicationIsOn() const { return application_is_on_; }

void Application::SetApplicationIsOn(bool application_is_on) {
  application_is_on_ = application_is_on;
}
