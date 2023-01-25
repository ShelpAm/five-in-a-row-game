//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_BOARD_COORDINATE_H
#define FIVE_IN_A_ROW_GAME_BOARD_COORDINATE_H

#include "five_in_a_row_game/board_fwd.h"
#include "five_in_a_row_game/vector2d.h"

class BoardCoordinate {
 public:
  BoardCoordinate();
  BoardCoordinate(const Vector2D<int> &vec2i);
  BoardCoordinate(int column, int row);

  int &operator[](int index) { return vec2i_[index]; }
  const int &operator[](int index) const { return vec2i_[index]; }

  int Column() const { return vec2i_.X(); }
  void SetColumn(int column) { vec2i_.SetX(column); }
  int Row() const { return vec2i_.Y(); }
  void SetRow(int row) { vec2i_.SetY(row); }
  int X() const { return vec2i_.X(); }
  void SetX(int x) { vec2i_.SetX(x); }
  int Y() const { return vec2i_.Y(); }
  void SetY(int y) { vec2i_.SetY(y); }

 private:
  Vector2D<int> vec2i_;
};

/// @brief Judges if the board_coordinate is valid in certain board.
///         (if board_coordinate.X() < board.size, so as y)
bool IsInRangeOf(const BoardCoordinate &board_coordinate,
                 const Board *const board_ptr);

#endif  // FIVE_IN_A_ROW_GAME_BOARD_COORDINATE_H
