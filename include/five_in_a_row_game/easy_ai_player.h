//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_EASY_AI_PLAYER_H
#define FIVE_IN_A_ROW_GAME_EASY_AI_PLAYER_H

#include <math.h>

#include <cstddef>
#include <vector>

#include "ai_player.h"
#include "easy_ai_player_fwd.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/board_fwd.h"
#include "five_in_a_row_game/game_board.h"
#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/vector2d.h"

struct CalculationResult {
  CalculationResult operator+(const CalculationResult & other) const;
  CalculationResult & operator+=(const CalculationResult & other);

  float score = 0.0;
  int count_of_all_my_pieces = 0;
  int count_of_all_empty_pieces = 0;
  int count_of_all_enemy_pieces = 0;
};

class EasyAIPlayer : public AIPlayer {
 public:
  EasyAIPlayer() = default;
  EasyAIPlayer(const int id, const char * name);
  virtual ~EasyAIPlayer() override;

  virtual const ScoreMap CalculateScoreMap(
      const GameBoard & board) const override;

  CalculationResult CalculateScoreInDirection(
      const GameBoard & board, const Vector2D<int> & curr_coord,
      const Vector2D<int> & curr_direction) const;
};

#endif  // FIVE_IN_A_ROW_GAME_EASY_AI_PLAYER_H
