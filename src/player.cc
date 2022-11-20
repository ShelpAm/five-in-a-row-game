//
// Created by small-sheep on 11/10/22.
//

#include "player.h"

Player::Player(StoneType used_stone_type) : used_stone_type_(used_stone_type) {
}

Player::~Player() = default;

void Player::PlaceAStone(Board &board,
                         const BoardCoordinate &board_coordinate) const {
  board.PlaceAStone(board_coordinate, used_stone_type_);
}

void Player::ThinkAndPlaceAStone(Board &board) const {
  //Thinking here.
  BoardCoordinate target_board_coordinate(Think(board));
  PlaceAStone(board, target_board_coordinate);
}

StoneType Player::UsedStoneType() const {
  return used_stone_type_;
}

void Player::SetUsedStoneType(StoneType used_stone_type) {
  used_stone_type_ = used_stone_type;
}

Player::Player() {

}
