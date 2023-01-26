//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/five_in_a_row_game.h"

#include <iostream>
#include <sstream>
#include <string>

#include "five_in_a_row_game/board.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/move.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/stone_type.h"

FiveInARowGame::FiveInARowGame()
    : board_pointer_(std::make_unique<Board>(15)) {}

void FiveInARowGame::Start(Player *first_hand_player_ptr,
                           Player *second_hand_player_ptr) {
  players_[0] = first_hand_player_ptr;
  players_[1] = second_hand_player_ptr;

  moving_player_ = players_[0];
  unmoving_player_ = players_[1];

  players_[0]->SetUsedStoneType(StoneType::kStoneTypeBlack);
  players_[1]->SetUsedStoneType(StoneType::kStoneTypeWhite);

  std::cout << "Game STARTS.\n";
  SetStarted(true);

  Render();
}

void FiveInARowGame::Tick() {
  Update();
  Render();
}

void FiveInARowGame::Update() {
  CurrentPlayerMove();
  CheckStatus();
  std::swap(moving_player_, unmoving_player_);
}

void FiveInARowGame::Render() const {
  // Do some cleaning.
  std::ostringstream buf;
  std::string line(board_pointer_->BoardSize(), '-');
  buf << line << "Map" << line << "\n";
  for (const auto &i : board_pointer_->BoardMap()) {
    buf << "| ";
    for (const auto &j : i) {
      buf << static_cast<int>(j) << " ";
    }
    buf << "|\n";
  }
  buf << line << line << "---\n";
  std::cout << buf.str();
}

void FiveInARowGame::CheckStatus() {
  auto IsRowWon = [](const Board *const board, const Move &move) -> bool {
    bool is_won = true;  // Go to IsColumnWon to understand why it is set true.
    for (int i = -4; i != 1; ++i) {
      if (move.board_coordinate.X() + i < 0 ||
          move.board_coordinate.X() + i + 4 > board->BoardSize() - 1) {
        continue;
      }
      for (int j = 0; j != 5; ++j) {
        if (move.stone_type != board->StoneTypeInCoordinate(BoardCoordinate(
                                   move.board_coordinate.X() + i + j,
                                   move.board_coordinate.Y()))) {
          is_won = false;
          break;
        }
      }
      if (is_won) {
        return true;
      }
    }
    return false;
  };

  auto IsColumnWon = [](const Board *const board, const Move &move) -> bool {
    bool is_won = true;  // First, pretend is_won is true, later we will verify
                         // its correctness.
    // 左右都有可能连成五子
    for (int i = -4; i != 1; ++i) {
      if (move.board_coordinate.Y() + i < 0 ||
          move.board_coordinate.Y() + i + 4 > board->BoardSize() - 1) {
        continue;
      }
      for (int j = 0; j != 5; ++j) {
        if (move.stone_type != board->StoneTypeInCoordinate(BoardCoordinate(
                                   move.board_coordinate.X(),
                                   move.board_coordinate.Y() + i + j))) {
          is_won = false;
          break;
        }
      }
      if (is_won) {
        return true;
      }
    }
    return false;
  };

  auto IsInclinationWon = [](const Board *const board,
                             const Move &move) -> bool {
    bool is_won = true;  // Go to IsColumnWon to understand why it is set true.
    for (int i = -4; i != 1; ++i) {
      if (move.board_coordinate.X() + i < 0 ||
          move.board_coordinate.Y() + i < 0 ||
          move.board_coordinate.X() + i + 4 > board->BoardSize() - 1 ||
          move.board_coordinate.Y() + i + 4 > board->BoardSize() - 1) {
        continue;
      }
      for (int j = 0; j != 5; ++j) {
        if (move.stone_type != board->StoneTypeInCoordinate(BoardCoordinate(
                                   move.board_coordinate.X() + i + j,
                                   move.board_coordinate.Y() + i + j))) {
          is_won = false;
          break;
        }
      }
      if (is_won) {
        return true;
      }
    }
    return false;
  };

  // We only need to check the recent move.
  const Move &last_move = history_moves_.top();
  if (IsRowWon(board_pointer_.get(), last_move) ||
      IsColumnWon(board_pointer_.get(), last_move) ||
      IsInclinationWon(board_pointer_.get(), last_move)) {
    winner_ = moving_player_;
    SetStarted(false);
    SetOver(true);
  }

  // BoardCoordinate iterator = last_move.board_coordinate;
  // Row
}

void FiveInARowGame::CurrentPlayerMove() {
  history_moves_.push(moving_player_->Move(board_pointer_.get()));
}
