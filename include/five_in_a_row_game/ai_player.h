//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_AI_PLAYER_H
#define FIVE_IN_A_ROW_GAME_AI_PLAYER_H

#include <cstddef>
#include <unordered_map>

#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/stone_type.h"

using ScoreMap = std::map<BoardCoordinate, float>;

class AIPlayer : public Player {
 public:
  AIPlayer() = default;
  AIPlayer(const AIPlayer & other) = delete;
  AIPlayer(const AIPlayer && other) = delete;
  virtual ~AIPlayer() override;

  virtual const BoardCoordinateContainer Think(
      const GameBoard & board) const override;

  virtual const ScoreMap CalculateScores(const GameBoard & board) const = 0;

 private:
  const BoardCoordinateContainer SelectMaxScoreCoordinatesFrom(
      const ScoreMap & score_map) const;
};

#endif  // FIVE_IN_A_ROW_GAME_AI_PLAYER_H
