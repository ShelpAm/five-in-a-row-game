//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_H
#define FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_H

#include "ai_player.h"
#include "easy_ai_player_fwd.h"
#include "five_in_a_row_game/board_coordinate.h"

class EasyAIPlayer : public AIPlayer {
 public:
  EasyAIPlayer();

  explicit EasyAIPlayer(StoneType stone_type);

  ~EasyAIPlayer() override;

  const BoardCoordinate Think(const Board *board_ptr) const override;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_H
