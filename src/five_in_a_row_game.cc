//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/five_in_a_row_game.h"
#include <iostream>
#include <sstream>
#include <string>
#include "five_in_a_row_game/player.h"

FiveInARowGame::FiveInARowGame() : board_pointer_(std::make_unique<Board>(5)) {
}

void FiveInARowGame::Start(Player *first_hand_player_ptr,
                           Player *second_hand_player_ptr) {
  first_hand_player_ptr_ = first_hand_player_ptr;
  second_hand_player_ptr_ = second_hand_player_ptr;
  first_hand_player_ptr_->SetUsedStoneType(StoneType::kStoneTypeBlack);
  second_hand_player_ptr_->SetUsedStoneType(StoneType::kStoneTypeWhite);
  SetGameIsOn(true);
  std::cout << "Game START.\n";
  while (GameIsOn()) {
    Tick();
  }
}

void FiveInARowGame::Tick() {
  ProcessInput();
  Update();
  Render();
}

void FiveInARowGame::ProcessInput() {
//  static std::string command;
//  std::cout << "Please input your command:\n";
//  std::cin >> command;
//  ParseCommand(command);
}

void FiveInARowGame::Update() {
  last_frame_time_ = current_frame_time_;
  current_frame_time_ = clock();
  SetFramePerSecond(current_frame_time_ - last_frame_time_);

  first_hand_player_ptr_->ThinkAndPlaceAStone(board_pointer_.get());
  second_hand_player_ptr_->ThinkAndPlaceAStone(board_pointer_.get());
}

void FiveInARowGame::Render() const {
  // Do some cleaning.
//  std::cout << std::string(50, '\n');
  std::ostringstream ss;
  ss << FramePerSecond() << "\n";
  ss << "---- Map ----\n";
  for (const auto &i: board_pointer_->BoardMap()) {
    for (const auto &j: i) {
      ss << static_cast<int>(j) << " ";
    }
    ss << "\n";
  }
  std::cout << ss.str();
}

void FiveInARowGame::ParseCommand(const std::string &command) {
  if (command == "exit") {
    SetGameIsOn(false);
  }
}

bool FiveInARowGame::GameIsOn() const {
  return game_is_on_;
}

void FiveInARowGame::SetGameIsOn(const bool game_is_on) {
  game_is_on_ = game_is_on;
}

int FiveInARowGame::FramePerSecond() const {
  return frame_per_second_;
}

void FiveInARowGame::SetFramePerSecond(const int frame_per_second) {
  frame_per_second_ = frame_per_second;
}
