//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_PLAYER_H
#define FIVE_IN_A_ROW_GAME_SRC_PLAYER_H

#include <string>
#include <vector>

#include "five_in_a_row_game/board.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/move.h"

class Player {
 public:
  Player();
  explicit Player(StoneType used_stone_type);
  virtual ~Player();

  const Move Move(Board *board);

  virtual const std::vector<BoardCoordinate> Think(
      const Board *const board) const = 0;

  void PlaceAStone(Board *board, const BoardCoordinate &board_coordinate) const;

  int Identity() const { return identity_; }
  void SetIdentity(const int identity) { identity_ = identity; }
  const char *Name() const { return name_.c_str(); }
  void SetName(const char *const name) { name_ = name; }
  StoneType UsedStoneType() const { return used_stone_type_; }
  void SetUsedStoneType(const StoneType st) { used_stone_type_ = st; }

 private:
  int identity_;
  std::string name_;
  StoneType used_stone_type_;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_PLAYER_H
