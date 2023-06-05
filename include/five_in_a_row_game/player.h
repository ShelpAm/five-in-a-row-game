//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_PLAYER_H
#define FIVE_IN_A_ROW_GAME_PLAYER_H

#include <string>
#include <vector>

#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/game_board.h"
#include "five_in_a_row_game/move.h"
#include "five_in_a_row_game/stone_type.h"

inline namespace five_in_a_row_game {

class Player {
 public:
  Player();
  Player(const int identity, const char * const name,
         const StoneType stone_type_in_use);
  Player(const Player & player);
  Player(const Player && player);
  virtual ~Player();

  const ::Move Move(GameBoard & board) const;

 public:
  int id() const { return id_; }
  void set_id(const int id) { id_ = id; }
  const char * name() const { return name_.c_str(); }
  void set_name(const char * const name) { name_ = name; }
  StoneType stone_type() const { return stone_type_; }
  void set_stone_type(const StoneType st) { stone_type_ = st; }

 protected:
  virtual const std::vector<BoardCoordinate> Think(
      const GameBoard & board) const = 0;

  void PlaceAStone(GameBoard & board, const BoardCoordinate & bc) const;

  int id_{0};
  std::string name_{"default_name"};
  StoneType stone_type_{StoneType::kStoneTypeEmpty};
};

}  // namespace five_in_a_row_game

#endif  // FIVE_IN_A_ROW_GAME_PLAYER_H
