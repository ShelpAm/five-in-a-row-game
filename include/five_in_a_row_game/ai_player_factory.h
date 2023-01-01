//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_AI_PLAYER_FACTORY_H
#define FIVE_IN_A_ROW_GAME_SRC_AI_PLAYER_FACTORY_H

#include <five_in_a_row_game/ai_player.h>
#include <five_in_a_row_game/player_factory.h>

class AIPlayerFactory : public PlayerFactory {
 public:
  AIPlayerFactory();

  ~AIPlayerFactory() override;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_AI_PLAYER_FACTORY_H
