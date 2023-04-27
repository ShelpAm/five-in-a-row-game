//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/board.h"

#include <exception>
#include <iostream>
#include <sstream>

#include "five_in_a_row_game/board_coordinate.h"

Board::Board(int board_size)
    : board_size_(board_size),
      stone_type_map_(board_size, std::vector<StoneType>(
                                      board_size, StoneType::kStoneTypeEmpty)) {
}

void Board::PlaceAStone(const BoardCoordinate & c, const StoneType stone_type) {
  if (!IsCoordinateInRangeOfBoard(c, *this)) {
    throw CoordinateOutOfRange{};
  }
  stone_type_map_[c.column()][c.row()] = stone_type;
}

StoneType Board::GetStoneTypeInCoordinate(const BoardCoordinate & c) const {
  if (!IsCoordinateInRangeOfBoard(c, *this)) {
    throw CoordinateOutOfRange{};
  }
  return stone_type_map()[c.column()][c.row()];
}

std::ostream & operator<<(std::ostream & os, const Board & board) {
  std::stringstream buf;
  auto PrintLine1 = [board, &buf]() -> void {
    buf << "+  " << ' ';
    for (std::size_t i = 0; i != board.board_size(); ++i) {
      buf << i << ' ';
    }
    buf << "  +";
    buf << '\n';
  };
  auto PrintLine2 = [board, &buf]() -> void {
    buf << "   " << std::string(board.board_size() * 2 + 1, '-') << '\n';
  };
  PrintLine1();
  PrintLine2();
  for (std::size_t row = 0; row != board.board_size(); ++row) {
    buf << row << " | ";
    for (std::size_t column = 0; column != board.board_size(); ++column) {
      char stone_code = stone_code_map().at(
          board.GetStoneTypeInCoordinate(BoardCoordinate(column, row)));
      buf << stone_code << " ";
    }
    buf << "| " << row << "\n";
  }
  PrintLine2();
  PrintLine1();
  os << buf.str();
  return os;
}
