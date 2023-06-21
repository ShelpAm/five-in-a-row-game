//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_GAME_BOARD_H
#define FIVE_IN_A_ROW_GAME_GAME_BOARD_H

#include <cstddef>
#include <list>
#include <ostream>
#include <string>
#include <vector>

#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/move.h"
#include "five_in_a_row_game/stone_type.h"
#include "five_in_a_row_game/vector2d.h"

enum class BoardState : int {
  kBoardStateStarted,
  kBoardStateWinning,
  kBoardStateDrawing
};

const std::string & string_by_board_state(const BoardState board_state);

class GameBoard {
  friend std::ostream & operator<<(std::ostream & os, const GameBoard & board);

 public:
  explicit GameBoard(const int board_size);

  /// @brief Places a stone at the specified coordinate.
  void PlaceAStone(const BoardCoordinate & coordinate,
                   const StoneType stone_type);

  StoneType stone_type_by_coordinate(const BoardCoordinate & c) const;
  int board_size() const;
  const std::list<::Move> & history_moves() const;
  BoardState board_state() const;
  BoardCoordinate center() const;
  // bool contains(const BoardCoordinate & board_coordinate) const;
  bool contains(const Vector2D<int> & board_coordinate) const;

 private:
  bool is_winning() const;
  bool is_drawing() const;

  int board_size_;
  std::list<::Move> history_moves_;
  // TODO: to be added.
  // std::list<::BoardCoordinate> unmoved_coordinates_;
  std::map<BoardCoordinate, StoneType> stone_type_by_coordinate_;
};

std::ostream & operator<<(std::ostream & os, const GameBoard & board);

#endif  // FIVE_IN_A_ROW_GAME_GAME_BOARD_H
