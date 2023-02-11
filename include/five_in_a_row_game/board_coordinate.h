//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_BOARD_COORDINATE_H
#define FIVE_IN_A_ROW_GAME_BOARD_COORDINATE_H

#include <cstddef>

#include "five_in_a_row_game/board_fwd.h"
#include "five_in_a_row_game/vector2d.h"

class BoardCoordinate {
 public:
  BoardCoordinate();
  BoardCoordinate(const Vector2D<int> & vec2i);
  BoardCoordinate(const int column, const int row);
  BoardCoordinate(const std::size_t column, const std::size_t row);

  int & operator[](const int index) { return vec2i_[index]; }
  const int & operator[](const int index) const { return vec2i_[index]; }

  int Column() const { return vec2i_.X(); }
  void SetColumn(const int column) { vec2i_.SetX(column); }
  void AddColumn(const int delta) { vec2i_.AddX(delta); }
  int Row() const { return vec2i_.Y(); }
  void SetRow(const int row) { vec2i_.SetY(row); }
  void AddRow(const int delta) { vec2i_.AddY(delta); }
  int X() const { return vec2i_.X(); }
  void SetX(const int x) { vec2i_.SetX(x); }
  void AddX(const int delta) { vec2i_.AddX(delta); }
  int Y() const { return vec2i_.Y(); }
  void SetY(const int y) { vec2i_.SetY(y); }
  void AddY(const int delta) { vec2i_.AddY(delta); }

 private:
  Vector2D<int> vec2i_;  // first column and then row
};

bool operator==(const BoardCoordinate & lhs, const BoardCoordinate & rhs);

class CoordinateOutOfRange {};

/// @brief Judges if the board_coordinate is valid in certain board.
///         (if board_coordinate.X() < board.size, so as y)
bool CoordinateIsInRangeOfBoard(const BoardCoordinate & coordinate,
                                const Board & board);

#endif  // FIVE_IN_A_ROW_GAME_BOARD_COORDINATE_H
