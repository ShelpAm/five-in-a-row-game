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

  void PlaceAStone(const BoardCoordinate &board_coordinate,
                   StoneType stone_type);

  StoneType StoneTypeInCoordinate(const BoardCoordinate &) const;

  int BoardSize() const;

  const std::vector<std::vector<StoneType>> &BoardMap() const;

 private:
  int board_size_;
  std::vector<std::vector<StoneType>> board_map_;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_BOARD_H
