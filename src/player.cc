//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/player.h"

#include "five_in_a_row_game/board_fwd.h"
#include "five_in_a_row_game/move.h"

inline namespace five_in_a_row_game {

Player::Player() {}

Player::Player(int identity, const char * const name, const StoneType st_in_use)
    : identity_(identity), name_(name), stone_type_in_use_(st_in_use) {}

Player::Player(const Player & player)
    : identity_(player.identity_),
      name_(player.name_),
      stone_type_in_use_(player.stone_type_in_use_) {}

Player::~Player() {}

const ::Move Player::Move(Board & board) const {
  BoardCoordinate target_board_coordinate{Think(board).front()};
  PlaceAStone(board, target_board_coordinate);
  // constructor
  return ::Move{target_board_coordinate, stone_type_in_use_};
}

void Player::PlaceAStone(Board & board,
                         const BoardCoordinate & coordinate) const {
  board.PlaceAStone(coordinate, stone_type_in_use_);
}

}  // namespace five_in_a_row_game
