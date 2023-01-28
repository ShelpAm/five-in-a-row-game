//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/board.h"

#include <exception>
#include <iostream>

#include "five_in_a_row_game/board_coordinate.h"

Board::Board(int board_size)
    : board_size_(board_size),
      stone_type_map_(board_size, std::vector<StoneType>(
                                      board_size, StoneType::kStoneTypeEmpty)) {
}

void Board::PlaceAStone(const BoardCoordinate &c, const StoneType stone_type) {
  if (!CoordinateIsInRangeOfBoard(c, this)) {
    throw CoordinateOutOfRange{};
  }
  stone_type_map_[c.Column()][c.Row()] = stone_type;
}

StoneType Board::StoneTypeInCoordinate(const BoardCoordinate &c) const {
  if (!CoordinateIsInRangeOfBoard(c, this)) {
    throw CoordinateOutOfRange{};
  }
  return StoneTypeMap()[c.Column()][c.Row()];
}
