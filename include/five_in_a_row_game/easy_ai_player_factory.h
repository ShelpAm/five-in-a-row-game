//
// Created by small-sheep on 11/10/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_FACTORY_H
#define FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_FACTORY_H

#include "ai_player_factory.h"
#include "ai_player_fwd.h"

class EasyAIPlayerFactory : public AIPlayerFactory {
 public:
  EasyAIPlayerFactory();

  virtual ~EasyAIPlayerFactory() override;

  virtual Player *MakePlayer() const override;

  virtual Player *MakePlayer(const StoneType stone_type) const override;
};

#endif  // FIVE_IN_A_ROW_GAME_SRC_EASY_AI_PLAYER_FACTORY_H
