//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/board.h"

#include <exception>
#include <iostream>

#include "five_in_a_row_game/board_coordinate.h"

Board::Board(int board_size)
    : board_size_(board_size),
      board_map_(board_size, std::vector<StoneType>(
                                 board_size, StoneType::kStoneTypeEmpty)) {}

void Board::PlaceAStone(const BoardCoordinate &board_coordinate,
                        const StoneType stone_type) {
  if (!IsInRangeOf(board_coordinate, this)) {
    throw 2;
  }
  board_map_[board_coordinate.Row()][board_coordinate.Column()] = stone_type;
}

StoneType Board::StoneTypeInCoordinate(
    const BoardCoordinate &board_coordinate) const {
  if (!IsInRangeOf(board_coordinate, this)) {
    throw std::exception();
  }
  return board_map_[board_coordinate.Row()][board_coordinate.Column()];
}

int Board::BoardSize() const { return board_size_; }

const std::vector<std::vector<StoneType>> &Board::BoardMap() const {
  return board_map_;
}
