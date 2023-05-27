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

  int & operator[](const int index) { return vector2i_[index]; }
  const int & operator[](const int index) const { return vector2i_[index]; }

  int column() const { return vector2i_.x(); }
  void set_column(const int column) { vector2i_.set_x(column); }
  void add_column(const int delta) { vector2i_.add_x(delta); }
  int row() const { return vector2i_.y(); }
  void set_row(const int row) { vector2i_.set_y(row); }
  void add_row(const int delta) { vector2i_.add_y(delta); }
  int x() const { return vector2i_.x(); }
  void set_x(const int x) { vector2i_.set_x(x); }
  void add_x(const int delta) { vector2i_.add_x(delta); }
  int y() const { return vector2i_.y(); }
  void set_y(const int y) { vector2i_.set_y(y); }
  void add_y(const int delta) { vector2i_.add_y(delta); }

 private:
  Vector2D<int> vector2i_;  // first column and then row
};

bool operator==(const BoardCoordinate & lhs, const BoardCoordinate & rhs);

class CoordinateOutOfRange {};

/// @brief Judges if the board_coordinate is valid in certain board.
///         (if board_coordinate.X() < board.size, so as y)
bool IsCoordinateInRangeOfBoard(const BoardCoordinate & coordinate,
                                const Board & board);

#endif  // FIVE_IN_A_ROW_GAME_BOARD_COORDINATE_H
