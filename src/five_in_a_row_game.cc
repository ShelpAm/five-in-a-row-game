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

void FiveInARowGame::Start(Player *first_hand_player,
                           Player *second_hand_player) {
  players_[0] = first_hand_player;
  players_[1] = second_hand_player;

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
  UpdateStatus();
  std::swap(moving_player_, unmoving_player_);
}

void FiveInARowGame::Render() const {
  // Do some cleaning.
  std::ostringstream buf;
  std::string line(board_pointer_->BoardSize(), '-');
  buf << line << "Map" << line << "\n";
  const int end = board_pointer_->BoardSize();
  for (int row = 0; row != end; ++row) {
    buf << "| ";
    for (int column = 0; column != end; ++column) {
      buf << static_cast<int>(board_pointer_->StoneTypeInCoordinate(
                 BoardCoordinate{column, row}))
          << " ";
    }
    buf << "|\n";
  }
  buf << line << line << "---\n";
  std::cout << buf.str();
}

void FiveInARowGame::UpdateStatus() {
  auto Winning = [](const Board *board, const Move &last_move) -> bool {
    // This only need to check the latest move.
    // Directions: - - -
    //             - - +
    //             + + +
    for (int vertical = 0; vertical != 2; ++vertical) {
      for (int horizontal = -1; horizontal != 2; ++horizontal) {
        if (vertical == 0 && horizontal != 1) {
          continue;
        }
        // for every five stones
        for (int distance = -4; distance != 1; ++distance) {
          // for every stone
          for (int i = 0; i != 5; ++i) {
            const BoardCoordinate &last_move_coordinate =
                last_move.board_coordinate;
            BoardCoordinate c{
                last_move_coordinate.Column() + horizontal * (distance + i),
                last_move_coordinate.Row() + vertical * (distance + i)};
            if (!CoordinateIsInRangeOfBoard(c, board) ||
                board->StoneTypeInCoordinate(c) != last_move.stone_type) {
              break;
            }
            if (i == 4) {
              return true;
            }
          }
        }
      }
    }
    return false;
  };

  const Board *const board = board_pointer_.get();
  const Move &last_move = history_moves_.top();
  if (Winning(board, last_move)) {
    winner_ = moving_player_;
    SetStarted(false);
    SetOver(true);
  }
}

void FiveInARowGame::CurrentPlayerMove() {
  const Move move{moving_player_->Move(board_pointer_.get())};
  history_moves_.push(move);
}
