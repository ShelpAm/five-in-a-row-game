//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_BOARD_H
#define FIVE_IN_A_ROW_GAME_SRC_BOARD_H

#include <vector>
#include "board_coordinate.h"

enum class StoneType : int {
  kStoneTypeEmpty,
  kStoneTypeBlack,
  kStoneTypeWhite,
};

class Board {
 public:
  explicit Board(int board_size);

  void PlaceAStone(const BoardCoordinate &board_position,
                   StoneType stone_type);

 public:
  const StoneType StoneTypeInCoordinate(
      const BoardCoordinate &board_coordinate) const;

  int BoardSize() const;

  const std::vector<std::vector<StoneType>> &BoardMap() const;

 private:
  int board_size_;
  std::vector<std::vector<StoneType>> board_map_;
};


#endif //FIVE_IN_A_ROW_GAME_SRC_BOARD_H
