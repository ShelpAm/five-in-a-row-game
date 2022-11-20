//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_H
#define FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_H

#include "easy_ai_player_fwd.h"
#include "ai_player.h"

class EasyAIPlayer : public AIPlayer {
 public:
  EasyAIPlayer();

  explicit EasyAIPlayer(StoneType stone_type);

  ~EasyAIPlayer() override;

  const BoardCoordinate Think(const Board &board) const override;
};


#endif //FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_H
