//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/board.h"

#include <cstddef>
#include <exception>
#include <iostream>
#include <sstream>

#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/move.h"

Board::Board(const std::size_t board_size)
    : board_size_(board_size),
      stone_type_map_(board_size, std::vector<StoneType>(
                                      board_size, StoneType::kStoneTypeEmpty)) {
}

void Board::PlaceAStone(const BoardCoordinate & c, const StoneType stone_type) {
  if (!IsCoordinateInRangeOfBoard(c, *this)) {
    throw CoordinateOutOfRange{};
  }
  stone_type_map_[c.column()][c.row()] = stone_type;
  history_moves_.push_back(Move(c, stone_type));
}

StoneType Board::GetStoneTypeInCoordinate(const BoardCoordinate & c) const {
  if (!IsCoordinateInRangeOfBoard(c, *this)) {
    throw CoordinateOutOfRange{};
  }
  return stone_type_map()[c.column()][c.row()];
}

BoardState Board::GetBoardState() const {
  if (IsWinning()) {
    return BoardState::kBoardStateWinning;
  } else if (IsDrawing()) {
    return BoardState::kBoardStateDrawing;
  } else {
    return BoardState::kBoardStateStarted;
  }
}

bool Board::IsWinning() const {
  // This fucntion needs only to check the latest move.
  const Move & last_move{history_moves_.back()};
  for (int vertical = 0; vertical != 2; ++vertical) {
    for (int horizontal = -1; horizontal != 2; ++horizontal) {
      // filter directions
      // all directions that should be checked:
      //   - - -
      //   - - +
      //   + + +
      if (vertical == 0 && horizontal != 1) {
        continue;
      }
      // for every group of five stones
      for (int offset = -4; offset != 1; ++offset) {
        int i = 0;
        // for every stone in the group
        for (; i != 5; ++i) {
          const auto & last_move_coordinate = last_move.board_coordinate;
          BoardCoordinate coord{
              last_move_coordinate.column() + horizontal * (offset + i),
              last_move_coordinate.row() + vertical * (offset + i)};
          if (!IsCoordinateInRangeOfBoard(coord, *this) ||
              GetStoneTypeInCoordinate(coord) != last_move.stone_type) {
            break;
          }
        }
        if (i == 5) {
          return true;
        }
      }
    }
  }
  return false;
}

bool Board::IsDrawing() const {
  return history_moves_.size() == board_size_ * board_size_;
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
      char stone_code;
      if (!board.history_moves_.empty() &&
          BoardCoordinate{column, row} ==
              board.history_moves_.back().board_coordinate) {
        stone_code = 'L';
      } else {
        stone_code = stone_code_map().at(
            board.GetStoneTypeInCoordinate(BoardCoordinate(column, row)));
      }
      buf << stone_code << " ";
    }
    buf << "| " << row << "\n";
  }
  PrintLine2();
  PrintLine1();
  os << buf.str();
  return os;
}
