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

using BoardCoordinateContainer = std::list<BoardCoordinate>;

class Player {
 public:
  Player();
  Player(const int identity, const char * const name,
         const StoneType stone_type_in_use);
  Player(const Player & player);
  Player(const Player && player);
  virtual ~Player();

  const ::Move Move(GameBoard & board) const;

  int id() const;
  void set_id(const int id);
  const char * name() const;
  void set_name(const char * const name);
  StoneType stone_type() const;
  void set_stone_type(const StoneType st);

 protected:
  virtual const BoardCoordinateContainer Think(
      const GameBoard & board) const = 0;

  void PlaceAStone(GameBoard & board, const BoardCoordinate & bc) const;

  int id_ = 0;
  std::string name_{"default_name"};
  StoneType stone_type_ = StoneType::kStoneTypeEmpty;
};

}  // namespace five_in_a_row_game

#endif  // FIVE_IN_A_ROW_GAME_PLAYER_H
