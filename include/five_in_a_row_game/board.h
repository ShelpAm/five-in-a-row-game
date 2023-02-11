//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_BOARD_H
#define FIVE_IN_A_ROW_GAME_SRC_BOARD_H

#include <vector>

#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/stone_type.h"

class Board {
 public:
  explicit Board(int board_size);

  void PlaceAStone(const BoardCoordinate & c, const StoneType stone_type);

  StoneType StoneTypeInCoordinate(const BoardCoordinate & c) const;

  int BoardSize() const { return board_size_; }
  const std::vector<std::vector<StoneType>> & GetStoneTypeMap() const {
    return stone_type_map_;
  }

 private:
  int board_size_;
  std::vector<std::vector<StoneType>> stone_type_map_;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_BOARD_H
