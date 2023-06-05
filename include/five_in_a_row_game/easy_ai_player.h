//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_H
#define FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_H

#include <cstddef>
#include <vector>

#include "ai_player.h"
#include "easy_ai_player_fwd.h"
#include "five_in_a_row_game/board_coordinate.h"
#include "five_in_a_row_game/board_fwd.h"
#include "five_in_a_row_game/vector2d.h"

class EasyAIPlayer : public AIPlayer {
 public:
  EasyAIPlayer();

  explicit EasyAIPlayer(const AIPlayer * const ai_player);

  ~EasyAIPlayer() override;

  const std::vector<BoardCoordinate> Think(
      const GameBoard & board) const override;

  virtual const ScoreMapType CalculateScore(
      const GameBoard & board) const override;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_H
