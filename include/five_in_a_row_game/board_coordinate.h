//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_BOARD_COORDINATE_H
#define FIVE_IN_A_ROW_GAME_BOARD_COORDINATE_H

#include "five_in_a_row_game/board_fwd.h"
#include "five_in_a_row_game/vector2d.h"

class BoardCoordinate : public Vector2D<int> {
 public:
  BoardCoordinate();

  BoardCoordinate(const Vector2D<int> &vec2i);

  BoardCoordinate(int column, int row);

  int Column() const { return X(); }
  void SetColumn(int column) { SetX(column); }
  int Row() const { return Y(); }
  void SetRow(int row) { SetY(row); }
};

/// @brief return if the board_coordinate is valid in certain board.
///         (if board_coordinate.X() < board.size, so as y)
bool IsInRangeOf(const BoardCoordinate &board_coordinate,
                 const Board *const board_ptr);

#endif  // FIVE_IN_A_ROW_GAME_BOARD_COORDINATE_H
