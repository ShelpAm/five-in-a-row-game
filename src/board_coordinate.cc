//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/board_coordinate.h"

#include "five_in_a_row_game/board.h"

BoardCoordinate::BoardCoordinate() : vec2i_() {}

BoardCoordinate::BoardCoordinate(const Vector2D<int> &vec2i) : vec2i_(vec2i) {}

BoardCoordinate::BoardCoordinate(int column, int row) : vec2i_(column, row) {}

bool IsInRangeOf(const BoardCoordinate &board_coordinate,
                 const Board *const board_ptr) {
  return board_coordinate.Row() < board_ptr->BoardSize() &&
         board_coordinate.Row() >= 0 &&
         board_coordinate.Column() < board_ptr->BoardSize() &&
         board_coordinate.Column() >= 0;
}
