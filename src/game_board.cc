//
// Created by small-sheep on 11/11/22.
//

#include "five_in_a_row_game/game_board.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <exception>
#include <iostream>
#include <sstream>

#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/move.h"
#include "five_in_a_row_game/stone_type.h"
#include "five_in_a_row_game/vector2d.h"

GameBoard::GameBoard(const int board_size) : board_size_(board_size) {}

void GameBoard::PlaceAStone(const BoardCoordinate & coordinate,
                            const StoneType stone_type) {
  if (!this->contains(coordinate)) {
    assert(false);
    throw CoordinateOutOfRange();
  }
  stone_type_by_coordinate_[coordinate] = stone_type;
  const ::Move result_move(coordinate, stone_type);
  history_moves_.push_back(result_move);
}

StoneType GameBoard::stone_type_by_coordinate(const BoardCoordinate & c) const {
  if (!this->contains(c)) {
    throw CoordinateOutOfRange();
  }
  if (stone_type_by_coordinate_.contains(c)) {
    return stone_type_by_coordinate_.at(c);
  } else {
    return StoneType::kStoneTypeEmpty;
  }
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
  Vector2D<int> directions[4] = {{1, 0}, {-1, 1}, {0, 1}, {1, 1}};
  for (const auto & direction : directions) {
    for (int start_point_offset = -4; start_point_offset != 1;
         ++start_point_offset) {
      int i = 0;
      // for every stone in the group
      for (; i != 5; ++i) {
        BoardCoordinate coord(last_move.coordinate.column() +
                                  direction.x() * (start_point_offset + i),
                              last_move.coordinate.row() +
                                  direction.y() * (start_point_offset + i));
        if (!this->contains(coord)) {
          break;
        }
        if (this->stone_type_by_coordinate(coord) != last_move.stone_type) {
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
  return static_cast<int>(history_moves_.size()) == board_size_ * board_size_;
}

std::ostream & operator<<(std::ostream & os, const GameBoard & board) {
  std::stringstream buf;
  auto PrintLine1 = [board, &buf]() -> void {
    buf << "+  " << ' ';
    for (int i = 0; i != board.board_size(); ++i) {
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
  for (auto row = 0; row != board.board_size(); ++row) {
    buf << row << " | ";
    for (auto column = 0; column != board.board_size(); ++column) {
      char stone_code;
      if (!board.history_moves_.empty() &&
          BoardCoordinate{column, row} ==
              board.history_moves_.back().coordinate) {
        stone_code = 'L';
      } else {
        stone_code = stone_code_map().at(
            board.stone_type_by_coordinate(BoardCoordinate(column, row)));
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
BoardCoordinate GameBoard::center() const {
  return BoardCoordinate((board_size_ + 1) / 2, (board_size_ + 1) / 2);
}
int GameBoard::board_size() const { return board_size_; }
const std::list<::Move> & GameBoard::history_moves() const {
  return history_moves_;
}
/*bool GameBoard::contains(const BoardCoordinate & board_coordinate) const {
  return board_coordinate.x() >= 0 && board_coordinate.y() >= 0 &&
         board_coordinate.x() < board_size_ &&
         board_coordinate.y() < board_size_;
}*/
const std::string & string_by_board_state(const BoardState board_state) {
  static const std::map<BoardState, std::string> string_by_board_state{
      {BoardState::kBoardStateStarted, "kBoardStateStared"},
      {BoardState::kBoardStateWinning, "kBoardStateWinning"},
      {BoardState::kBoardStateDrawing, "kBoardStateDrawing"}};
  return string_by_board_state.at(board_state);
}
bool GameBoard::contains(const Vector2D<int> & board_coordinate) const {
  return board_coordinate.x() >= 0 && board_coordinate.y() >= 0 &&
         board_coordinate.x() < board_size_ &&
         board_coordinate.y() < board_size_;
}
