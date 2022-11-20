//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_AI_PLAYER_FACTORY_H
#define FIVE_IN_A_ROW_GAME_SRC_AI_PLAYER_FACTORY_H

#include "ai_player_fwd.h"
#include "ai_player.h"
#include "player_factory.h"

class AIPlayerFactory : public PlayerFactory {
 public:
  AIPlayerFactory();

  virtual ~AIPlayerFactory() = 0;
};


#endif //FIVE_IN_A_ROW_GAME_SRC_AI_PLAYER_FACTORY_H
