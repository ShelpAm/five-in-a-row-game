//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_GAME_BOARD_H
#define FIVE_IN_A_ROW_GAME_GAME_BOARD_H

#include <cstddef>
#include <list>
#include <ostream>
#include <vector>

#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/move.h"
#include "five_in_a_row_game/stone_type.h"

enum class BoardState : std::size_t {
  kBoardStateStarted,
  kBoardStateWinning,
  kBoardStateDrawing
};

class GameBoard {
  friend std::ostream & operator<<(std::ostream & os, const GameBoard & board);

 public:
  explicit GameBoard(const std::size_t board_size);

  /// @brief Places a stone at the specified coordinate.
  void PlaceAStone(const BoardCoordinate & c, const StoneType stone_type);

  StoneType GetStoneTypeInCoordinate(const BoardCoordinate & c) const;

  std::size_t board_size() const { return board_size_; }
  std::size_t num_of_moves() const { return history_moves_.size(); }
  BoardState board_state() const;
  BoardCoordinate center() const;

 private:
  bool is_winning() const;
  bool is_drawing() const;
  std::list<BoardCoordinate> & coordinates_of_color(const StoneType stone_type);

  std::size_t board_size_;
  std::list<Move> history_moves_{};
  // TODO: remove this.
  std::vector<std::vector<StoneType>> stone_type_map_{};
  std::list<BoardCoordinate> black_piece_coordinates_;
  std::list<BoardCoordinate> white_piece_coordinates_;
};

std::ostream & operator<<(std::ostream & os, const GameBoard & board);

#endif  // FIVE_IN_A_ROW_GAME_GAME_BOARD_H
