//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_AI_PLAYER_H
#define FIVE_IN_A_ROW_GAME_SRC_AI_PLAYER_H

#include "ai_player_fwd.h"
#include "player.h"

class AIPlayer : public Player {
 public:
  AIPlayer();

  explicit AIPlayer(StoneType stone_type);

  ~AIPlayer() override;
};


#endif //FIVE_IN_A_ROW_GAME_SRC_AI_PLAYER_H
