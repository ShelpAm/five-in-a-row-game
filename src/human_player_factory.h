//
// Created by small-sheep on 11/20/22.
//

#ifndef FIVE_IN_A_ROW_GAME_SRC_HUMAN_PLAYER_FACTORY_H
#define FIVE_IN_A_ROW_GAME_SRC_HUMAN_PLAYER_FACTORY_H

#include "player_factory.h"

class HumanPlayerFactory : public PlayerFactory{
 public:
  HumanPlayerFactory();

  ~HumanPlayerFactory() override;

  virtual Player *MakePlayer() const override;
  virtual Player *MakePlayer(const StoneType stone_type) const override;
};


#endif //FIVE_IN_A_ROW_GAME_SRC_HUMAN_PLAYER_FACTORY_H
