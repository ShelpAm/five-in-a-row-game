//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/game_board.h"

#include <algorithm>
#include <cstddef>
#include <exception>
#include <iostream>
#include <sstream>

#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/move.h"

GameBoard::GameBoard(const std::size_t board_size)
    : board_size_(board_size),
      stone_type_map_(board_size, std::vector<StoneType>(
                                      board_size, StoneType::kStoneTypeEmpty)) {
}

void GameBoard::PlaceAStone(const BoardCoordinate & c,
                            const StoneType stone_type) {
  if (!IsCoordinateInRangeOfBoard(c, *this)) {
    throw CoordinateOutOfRange{};
  }
  stone_type_map_[c.column()][c.row()] = stone_type;
  // FIXME: this should be commented out.
  coordinates_of_color(stone_type).push_back(c);
  history_moves_.push_back(Move(c, stone_type));
}

StoneType GameBoard::GetStoneTypeInCoordinate(const BoardCoordinate & c) const {
  // TODO: replace this with coordinates lists.
  if (!IsCoordinateInRangeOfBoard(c, *this)) {
    throw CoordinateOutOfRange();
  }
  return stone_type_map_.at(c.column()).at(c.row());
}

BoardState GameBoard::board_state() const {
  if (is_winning()) {
    return BoardState::kBoardStateWinning;
  } else if (is_drawing()) {
    return BoardState::kBoardStateDrawing;
  } else {
    return BoardState::kBoardStateStarted;
  }
}

bool GameBoard::is_winning() const {
  // This function needs only to check the latest move.
  const Move & last_move{history_moves_.back()};
  const auto & last_move_coordinate = last_move.coordinate;
  int directions[4][2] = {{1, 0}, {-1, 1}, {0, 1}, {1, 1}};
  for (auto direction : directions) {
    int horizontal = direction[0];
    int vertical = direction[1];
    for (int offset = -4; offset != 1; ++offset) {
      int i = 0;
      // for every stone in the group
      for (; i != 5; ++i) {
        BoardCoordinate coord{
            last_move_coordinate.column() + horizontal * (offset + i),
            last_move_coordinate.row() + vertical * (offset + i)};
        if (!IsCoordinateInRangeOfBoard(coord, *this)) {
          break;
        }
        if (GetStoneTypeInCoordinate(coord) != last_move.stone_type) {
          break;
        }
      }
      if (i == 5) {
        return true;
      }
    }
  }
  return false;
}

bool GameBoard::is_drawing() const {
  return history_moves_.size() == board_size_ * board_size_;
}

std::ostream & operator<<(std::ostream & os, const GameBoard & board) {
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
              board.history_moves_.back().coordinate) {
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

std::list<BoardCoordinate> & GameBoard::coordinates_of_color(
    const StoneType stone_type) {
  static const std::map<StoneType, std::list<BoardCoordinate> &>
      stone_type_coordinates_map = {
          {StoneType::kStoneTypeBlack, black_piece_coordinates_},
          {StoneType::kStoneTypeWhite, white_piece_coordinates_}};
  return stone_type_coordinates_map.at(stone_type);
}
BoardCoordinate GameBoard::center() const {
  return BoardCoordinate((board_size_ + 1) / 2, (board_size_ + 1) / 2);
}
