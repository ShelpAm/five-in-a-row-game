//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/player.h"

#include <cassert>
#include <iostream>
#include <random>

#include "five_in_a_row_game/board_fwd.h"
#include "five_in_a_row_game/move.h"
#include "five_in_a_row_game/stone_type.h"

inline namespace five_in_a_row_game {

Player::Player() {}

Player::Player(int identity, const char * const name, const StoneType st_in_use)
    : id_(identity), name_(name), stone_type_(st_in_use) {}

Player::~Player() {}

const ::Move Player::Move(GameBoard & board) const {
  auto container{Think(board)};
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<int> dist(
      0, static_cast<int>(container.size()) - 1);
  std::vector<BoardCoordinate> board_coordinate_vector(container.begin(),
                                                       container.end());
  const auto & target_board_coordinate = board_coordinate_vector.at(dist(gen));
  PlaceAStone(board, target_board_coordinate);
  return ::Move(target_board_coordinate, stone_type_);
}

void Player::PlaceAStone(GameBoard & board,
                         const BoardCoordinate & coordinate) const {
  if (board.stone_type_by_coordinate(coordinate) !=
      StoneType::kStoneTypeEmpty) {
    assert(false);
  }
  board.PlaceAStone(coordinate, stone_type_);
}

}  // namespace five_in_a_row_game
int Player::id() const { return id_; }
void Player::set_id(const int id) { id_ = id; }
const char * Player::name() const { return name_.c_str(); }
void Player::set_name(const char * const name) { name_ = name; }
StoneType Player::stone_type() const { return stone_type_; }
void Player::set_stone_type(const StoneType st) { stone_type_ = st; }
