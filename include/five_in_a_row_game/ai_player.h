//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_AI_PLAYER_H
#define FIVE_IN_A_ROW_GAME_SRC_AI_PLAYER_H

#include <cstddef>

#include "five_in_a_row_game/player.h"
#include "five_in_a_row_game/stone_type.h"

using ScoreMapType = std::vector<std::vector<float>>;

class AIPlayer : public Player {
 public:
  AIPlayer();
  explicit AIPlayer(const Player & player);
  AIPlayer(const AIPlayer & other);
  AIPlayer(const AIPlayer && other);
  virtual ~AIPlayer() override;

  virtual const ScoreMapType CalculateScore(const GameBoard & board) const = 0;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_AI_PLAYER_H
