//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_FACTORY_H
#define FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_FACTORY_H

#include "five_in_a_row_game/easy_ai_player_fwd.h"

class EasyAIPlayerFactory {
 public:
  EasyAIPlayerFactory();

  ~EasyAIPlayerFactory();

  EasyAIPlayer * MakePlayer() const;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_FACTORY_H
