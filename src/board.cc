//
// Created by small-sheep on 11/11/22.
//

#include "board.h"
#include <exception>

Board::Board(int board_size)
    : board_size_(board_size),
      board_map_(board_size,
                 std::vector<StoneType>(board_size,
                                        StoneType::kStoneTypeEmpty)) {
}

void Board::PlaceAStone(const BoardCoordinate &board_position,
                        const StoneType stone_type) {
  if (board_position.row > board_size_ || board_position.column > board_size_) {
    throw std::exception();
  }
  board_map_[board_position.row][board_position.column] = stone_type;
}

const StoneType Board::StoneTypeInCoordinate(
    const BoardCoordinate &board_coordinate) const {
  return board_map_[board_coordinate.row][board_coordinate.column];
}

int Board::BoardSize() const {
  return board_size_;
}

const std::vector<std::vector<StoneType>> &Board::BoardMap() const {
  return board_map_;
}
