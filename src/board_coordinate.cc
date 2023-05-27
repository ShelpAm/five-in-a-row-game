//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/board_coordinate.h"

#include "five_in_a_row_game/board.h"

BoardCoordinate::BoardCoordinate() : vector2i_() {}

BoardCoordinate::BoardCoordinate(const Vector2D<int> & vec2i)
    : vector2i_(vec2i) {}

BoardCoordinate::BoardCoordinate(int column, int row)
    : vector2i_(column, row) {}

BoardCoordinate::BoardCoordinate(const std::size_t column,
                                 const std::size_t row)
    : vector2i_(static_cast<int>(column), static_cast<int>(row)) {}

bool operator==(const BoardCoordinate & lhs, const BoardCoordinate & rhs) {
  return lhs.column() == rhs.column() && lhs.row() == rhs.row();
}

bool IsCoordinateInRangeOfBoard(const BoardCoordinate & c,
                                const Board & board) {
  return c.row() < static_cast<int>(board.board_size()) && c.row() >= 0 &&
         c.column() < static_cast<int>(board.board_size()) && c.column() >= 0;
}
