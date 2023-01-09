//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/player.h"

#include "five_in_a_row_game/board_fwd.h"
#include "five_in_a_row_game/move.h"

Player::Player() {}

Player::Player(StoneType used_stone_type) : used_stone_type_(used_stone_type) {}

Player::~Player() {}

const Move Player::Move(Board *board) {
  BoardCoordinate target_board_coordinate(Think(board));
  PlaceAStone(board, target_board_coordinate);
  // constructor
  return ::Move{target_board_coordinate, used_stone_type_};
}

void Player::PlaceAStone(Board *board_ptr,
                         const BoardCoordinate &board_coordinate) const {
  board_ptr->PlaceAStone(board_coordinate, used_stone_type_);
}

void Player::ThinkAndPlaceAStone(Board *board_ptr) const {
  // Thinking here.
  BoardCoordinate target_board_coordinate(Think(board_ptr));
  PlaceAStone(board_ptr, target_board_coordinate);
}
