//
// Created by small-sheep on 11/11/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_BOARD_H
#define FIVE_IN_A_ROW_GAME_SRC_BOARD_H

#include <cstddef>
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

class Board {
  friend std::ostream & operator<<(std::ostream & os, const Board & board);

 public:
  explicit Board(const std::size_t board_size);

  void PlaceAStone(const BoardCoordinate & c, const StoneType stone_type);

  StoneType GetStoneTypeInCoordinate(const BoardCoordinate & c) const;

  std::size_t board_size() const { return board_size_; }
  const std::vector<std::vector<StoneType>> & stone_type_map() const {
    return stone_type_map_;
  }
  std::size_t num_moves() const { return history_moves_.size(); }

  BoardState GetBoardState() const;

 private:
  bool IsWinning() const;
  bool IsDrawing() const;

  std::size_t board_size_;
  std::vector<std::vector<StoneType>> stone_type_map_{};
  std::vector<Move> history_moves_{};
};

std::ostream & operator<<(std::ostream & os, const Board & board);

#endif  // FIVE_IN_A_ROW_GAME_SRC_BOARD_H
