//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/board_coordinate.h"

#include "five_in_a_row_game/board.h"
#include "five_in_a_row_game/vector2d.h"

BoardCoordinate::BoardCoordinate() : Vector2D<int>() {}

BoardCoordinate::BoardCoordinate(const Vector2D<int> &vec2i)
    : Vector2D<int>(vec2i.X(), vec2i.Y()) {}

BoardCoordinate::BoardCoordinate(int column, int row)
    : Vector2D<int>(column, row) {}

bool IsInRangeOf(const BoardCoordinate &board_coordinate,
                 const Board *const board_ptr) {
  return board_coordinate.Y() < board_ptr->BoardSize() &&
         board_coordinate.Y() >= 0 &&
         board_coordinate.X() < board_ptr->BoardSize() &&
         board_coordinate.X() >= 0;
}
