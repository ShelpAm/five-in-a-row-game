//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/board_coordinate.h"

#include "five_in_a_row_game/board.h"

BoardCoordinate::BoardCoordinate() : vec2i_() {}

BoardCoordinate::BoardCoordinate(const Vector2D<int> & vec2i) : vec2i_(vec2i) {}

BoardCoordinate::BoardCoordinate(int column, int row) : vec2i_(column, row) {}

bool CoordinateIsInRangeOfBoard(const BoardCoordinate & c,
                                const Board & board) {
  return c.Row() < board.BoardSize() && c.Row() >= 0 &&
         c.Column() < board.BoardSize() && c.Column() >= 0;
}
