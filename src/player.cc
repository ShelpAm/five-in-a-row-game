//
// Created by small-sheep on 11/10/22.
//

#include "five_in_a_row_game/player.h"

#include <random>

#include "five_in_a_row_game/board_fwd.h"
#include "five_in_a_row_game/move.h"

inline namespace five_in_a_row_game {

Player::Player() {}

Player::Player(int identity, const char * const name, const StoneType st_in_use)
    : id_(identity), name_(name), stone_type_(st_in_use) {}

Player::Player(const Player & player)
    : id_(player.id_), name_(player.name_), stone_type_(player.stone_type_) {}

Player::~Player() {}

const ::Move Player::Move(Board & board) const {
  auto container{Think(board)};
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<int> dist(
      0, static_cast<int>(container.size()) - 1);
  const auto & target_board_coordinate{container.at(dist(gen))};
  PlaceAStone(board, target_board_coordinate);
  // constructor
  return ::Move{target_board_coordinate, stone_type_};
}

void Player::PlaceAStone(Board & board,
                         const BoardCoordinate & coordinate) const {
  board.PlaceAStone(coordinate, stone_type_);
}

}  // namespace five_in_a_row_game
